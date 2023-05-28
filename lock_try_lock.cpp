/**
 * @file lock_try_lock.cpp
 * @author Sparsh Bhogavilli
 * @brief Demonstration of blocking nature of mutex::lock() and non-blocking nature of mutex::try_lock()
 * @version 0.1
 * @date 2023-05-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<bits/stdc++.h>
using namespace std;

int x_lock = 0, x_try_lock = 0;
mutex mtx;

void increment_to_100k_lock() {
    /**
     * @brief mutex::lock() has a blocking nature.
     * So, when threads t1 & t2 execute in parallel, some of the 100k iterations of each thread will be able to
     * lock the mutex & execute the increment operation immediately while the others would be required to wait and
     * get the lock acquired before executing the increment operation. 
     * But all the 100k iterations of both the threads will be able to execute the increment operation for sure in 
     * every run of the code.
     * 
     * Consequently, the value of `x_lock` that gets printed in the `main()` function is 200k in every run.
     * 
     */
    for (int i=0; i<1e5; i++) {
        mtx.lock();
        x_lock++;
        mtx.unlock();
    }
}

void increment_to_100k_try_lock() {
    /**
     * @brief mutex::try_lock() has a non-blocking nature.
     * So, when threads t3 & t4 execute in parallel, some of the 100k iterations of each thread get continue-ed
     * as the iterations of the other thread lock-ed the mutex already.
     * The number of iterations that get continue-ed, varies on each run of the program.
     * Consequently, the value of `x_try_lock` that gets printed in the last line of `main()` varies each run.
     * 
     */
    for (int i=0; i<1e5; i++) {
        if (mtx.try_lock()) {
            x_try_lock++;
            mtx.unlock();
        } else {
            continue;
        }
    }
}

int main() {
    thread t1(increment_to_100k_lock);
    thread t2(increment_to_100k_lock);
    t1.join();
    t2.join();
    cout << "x_lock:" << x_lock << endl;

    thread t3(increment_to_100k_try_lock);
    thread t4(increment_to_100k_try_lock);
    t3.join();
    t4.join();
    cout << "x_try_lock:" << x_try_lock << endl;
    return 0;
}