/**
 * @file std_try_lock.cpp
 * @author (you@domain.com)
 * @brief Code to demonstrate the working of std::try_lock. Two variables are parallely incremented once every second. 
 * std::try_lock is used to sum the values of both the variables after each increment.
 * @version 0.1
 * @date 2023-06-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<thread>
#include<iostream>
#include<mutex>
#include<chrono>

int X = 0, Y = 0, X_plus_Y = 0;
std::mutex mtx_X, mtx_Y;

void pause_execution_for_t_seconds(int t) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
}

void increment_XorY(int &XorY, std::mutex &mtx, char const *var_name) {
    for (int i=0; i<5; i++) {
        mtx.lock();
        XorY++;
        std::cout << *var_name << " = " << XorY << " | ";
        mtx.unlock();
        pause_execution_for_t_seconds(1);
    }
}

void reset_X_and_Y(int &X, int &Y, std::mutex &mtx_X, std::mutex &mtx_Y) {
    /**
     * @brief std::try_lock returns -1 upon acquiring locks for all the mutexes passed.
     * Upon failing to acquire lock for at least 1 mutex, it returns the 0-indexed index of the failed mutex.
     * 
     * Here, std::try_lock succeeds in locking both the mutexes once after the critical sections of both 
     * the threads are executed. This is repeated 5 times.
     */
    int lock_result;
    int num_increments = 5;
    while(1) {
        lock_result = std::try_lock(mtx_X, mtx_Y);
        if (lock_result == -1) {
            if (X!=0 && Y!=0) {
                X_plus_Y += X+Y;
                X = 0;
                Y = 0;
                std::cout << "X+Y: " << X_plus_Y << std::endl;
            }
            mtx_X.unlock();
            mtx_Y.unlock();
        }
        if (X_plus_Y == 2*num_increments) break;
    }
}

int main() {
    std::thread X_incrementor(increment_XorY, std::ref(X), std::ref(mtx_X), "X");
    std::thread Y_incrementor(increment_XorY, std::ref(Y), std::ref(mtx_Y), "Y");
    std::thread XY_add_reset(reset_X_and_Y, std::ref(X), std::ref(Y), std::ref(mtx_X), std::ref(mtx_Y));

    X_incrementor.join();
    Y_incrementor.join();
    XY_add_reset.join();
    return 0;
}