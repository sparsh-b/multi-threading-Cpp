/**
 * @file basic.cpp
 * @author (https://github.com/sparsh-b)
 * @brief Count the sum of all even & odd numbers until 100,000 separately in 2 threads 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<bits/stdc++.h>

using namespace std;

int main() {
    unsigned long od_sum=0, ev_sum=0;
    int max_num = 1e5;
    // instantiate 2 threads - one using explicit lambda function and another using implicit lambda function.

    // 1) Declare Explicit lambda function.
    auto lamd_e = [&](){
        for (int i=0; i<max_num; i+=2) {
            ev_sum += i;
        }
    };

    // 2) Instantiate a thread using implicit lambda function
    thread worker1([&](){
        for (int i=1; i<max_num; i+=2) {
            od_sum += i;
        }
    });

    // 1) Instantiate a thread using an explicit lambda function
    thread worker2(lamd_e);

    // `std::thread::join` waits for a thread to complete before executing the next line of code in the parent thread.
    worker1.join();
    worker2.join();
    cout << ev_sum << "|" << od_sum;
    return 0;
}