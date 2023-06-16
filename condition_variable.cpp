/**
 * @file condition_variable.cpp
 * @author your name (you@domain.com)
 * @brief Code to demonstrate the usage of std::condition_variable. A condition variable is used by a thread to notify its status of execution to one/more other thread.
 * In this program, weights are first added to a common balance in a thread, and then this thread notifies another thread (using condition variable) that the weights can be removed.
 * @version 0.1
 * @date 2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<mutex>
#include<iostream>
#include<thread>
#include<condition_variable>

std::condition_variable cv;
std::mutex mtx;
int total_weight = 0;

void add_weight(int weight) {
    std::lock_guard<std::mutex> lg(mtx);
    total_weight += weight;
    std::cout << "Added weight: " << weight << " | Net weight: " << total_weight << std::endl;
    cv.notify_one();
}

void remove_weight(int weight) {
    std::unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, [](){return total_weight<=0 ? false : true;});
    total_weight -= weight;
    std::cout << "Removed weight: " << weight << " | Net weight: " << total_weight << std::endl;
}

int main() {
    std::thread t1(add_weight, 100);
    std::thread t2(remove_weight, 40);
    t1.join();
    t2.join();
    return 0;
}