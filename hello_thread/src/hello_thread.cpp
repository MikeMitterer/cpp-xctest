#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>

// Verhindert dass die Ausgabe durcheinander gewürffelt wird!
std::mutex mtx;

int main() {

    // vector container stores threads
    std::vector<std::thread> workers;

    for (int i = 0; i < 5; i++) {
        workers.push_back(std::thread([] () {
            mtx.lock();
                std::cout << "thread function\n";
            mtx.unlock();
        }));
    }

    mtx.lock();
    std::cout << "main thread\n";
    mtx.unlock();

    // Looping every thread via for_each
    // The 3rd argument assigns a task
    // It tells the compiler we're using lambda ([])
    // The lambda function takes its argument as a reference to a thread, t
    // Then, joins one by one, and this works like barrier
    std::for_each(workers.begin(), workers.end(), []( std::thread &t) {
        t.join();
    });

    return 0;
}