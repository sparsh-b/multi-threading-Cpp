/**
 * @file lock_guard.cpp
 * @author Sparsh Bhogavilli
 * @brief Source code to append two pairs of sequential numbers using two threads 
 * while ensuring mutual exclusion through std::lock_guard
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<vector>
#include<iostream>
#include<mutex>
#include<thread>

std::vector<int> vec;
std::mutex mtx;

void append_to_vector(int min_num, int max_num) {
    /**
     * @brief The access to this function is mutually exclusive b/w threads.
     * 
     */
    std::lock_guard<std::mutex> l_guard(mtx);
    // The critical section is guarded from the point lock_guard is constructed.
    for (int i=min_num; i<max_num; i++) {
        vec.push_back(i);
    }
    // The guard is removed after the lock_guard is destructed.
}

int main() {
    std::thread t1(append_to_vector, 1, 11);
    std::thread t2(append_to_vector, 11, 21);

    t1.join();
    t2.join();

    for (int &element : vec) {
        std::cout << element << ',';
    }
    std::cout << '\n';
    return 0;
}