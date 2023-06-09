/**
 * @file std_unique_lock.cpp
 * @author your name (you@domain.com)
 * @brief Demonstration that std::unique_lock(std::mutex&, std::defer_lock) acquires ownership but doesn't lock the mutex.
 * And that, if a 2nd thread tries locking the mutex before std::unique_lock::lock() is called in the 1st thread,
 * the 2nd thread will be successful in locking the mutex.
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<mutex>
#include<iostream>
#include<thread>
#include<chrono>

std::mutex m1;

void thread_executor2() {
    m1.lock();
    std::cout << "Locked mutex in thread2\n";
    m1.unlock();
}

void thread_executor1() {
    std::unique_lock<std::mutex> unq_lock(m1, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // lock mutex here only after it is locked & unlocked in thread_executor2
    unq_lock.lock();
    std::cout << "Locked mutex in thread1\n";
}

int main() {
    std::thread t1(thread_executor1);
    // Give enough sleep duration here so that thread_executor1 creates a std::unique_lock object by the time thread2 starts.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread t2(thread_executor2);

    t1.join();
    t2.join();
    std::cout << "Completed executing both the threads!\n";
    return 0;
}