#include<bits/stdc++.h>

using namespace std;

int main() {
    unsigned long od_sum=0, ev_sum=0;
    int max_num = 1e5;
    auto lamd_e = [&](){
        for (int i=0; i<max_num; i+=2) {
            ev_sum += i;
        }
    };

    thread worker1([&](){
        for (int i=1; i<max_num; i+=2) {
            od_sum += i;
        }
    });
    thread worker2(lamd_e);
    worker1.join();
    worker2.join();
    cout << ev_sum << "|" << od_sum;
    return 0;
}