#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int numThreads) : m_threads(numThreads), stop(false) {
    for (int i = 0; i < m_threads; i++) {
        threads.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this] {
                        return !tasks.empty() || stop;
                        });
                    if (stop && tasks.empty()) {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                    //std::cout << "size of queue : " << tasks.size() << std::endl;
                }
                task();
            }
            });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    for (auto& th : threads) {
        th.join();
    }
}

