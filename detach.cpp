/**
 * @file detach.cpp
 * @author (https://github.com/sparsh-b)
 * @brief Demonstrate & explain the working of detach
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<thread>
#include<iostream>
#include<vector>
#include<mutex>

std::mutex mt;
std::vector<int> vec;

void append_numbers(int min_num, int max_num) {
    for (int i=min_num; i<max_num; i++) {
        vec.push_back(i);
    }
}

int main() {
    std::thread t1();
}