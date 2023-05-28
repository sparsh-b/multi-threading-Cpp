
### lock_guard
- It is not a good practice to call the member functions `std::mutex::lock()` and `std::mutex::unlock()` directly.
    - Because this means that we have to remember to call `unlock()` on every code path out of a function, including those due to exceptions.
- Instead, the Standard C++ Library provides the `std::lock_guard` class template which locks the supplied mutex on construction and unlocks it on destruction, thus ensuring a locked mutex is always correctly unlocked.
- Code example of `std::lock_guard` is presented [here](./lock_guard.cpp).

References
- https://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11B.php