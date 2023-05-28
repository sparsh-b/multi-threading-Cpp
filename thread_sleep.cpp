#include<bits/stdc++.h>

using namespace std;

class Functor {
    public:
        void operator()(int num_repeat){
            for (int i=0; i<num_repeat; i++) {
                cout << i << " - inside thread\n";
                if (i==4) {
                    cout << "Waiting for 2 seconds.\n";
                    this_thread::sleep_for(chrono::seconds(2));
                }
            }
        }
};

int main() {
    thread worker1(Functor(), 10);
    
    if (worker1.joinable()) {
        worker1.join();
        cout << "Worker1 is joinable.\n";
    } else {
        cout << "Worker1 is NOT joinable.";
    }

    if (worker1.joinable()) {
        cout << "Worker1 is joinable.";
        worker1.join();
    } else {
        cout << "Worker1 is NOT joinable.\n";
    }
    return 0;
}