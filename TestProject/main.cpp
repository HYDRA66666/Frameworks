#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "Foundation/PrintCenter.h"
#include <Windows.h>

using namespace HYDRA15::Foundation::Secretary;

void rolling_writer(PrintCenter& pc, int thread_id) {
    for (int i = 0; i < 100; ++i) {
        pc.rolling("Thread " + std::to_string(thread_id) + " rolling msg #" + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void bottom_progress_writer(PrintCenter& pc, int token, std::atomic<bool>& running) {
    PrintCenter::ID id = pc.new_bottom(token);
    int progress = 0;
    while (progress <= 100 && running) {
        std::string msg = "Progress " + std::to_string(token) + ": " + std::to_string(progress) + "%";
        pc.update_bottom(id, token, msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++progress;
    }
    pc.remove_bottom(id, token);
}

int main() {
    PrintCenter& pc = PrintCenter::get_instance();

    // 启动20个滚动消息线程
    std::vector<std::thread> rolling_threads;
    for (int i = 0; i < 2; ++i) {
        rolling_threads.emplace_back(rolling_writer, std::ref(pc), i);
    }

    // 启动3个底部消息线程
    std::vector<std::thread> bottom_threads;
    std::vector<std::atomic<bool>> running_flags(3);
    for (int i = 0; i < 1; ++i) {
        running_flags[i] = true;
        bottom_threads.emplace_back(bottom_progress_writer, std::ref(pc), 15 + i, std::ref(running_flags[i]));
    }

    

    // 等待滚动消息线程结束
    for (auto& t : rolling_threads) {
        t.detach();
    }
    for (auto& t : bottom_threads) {
        t.detach();
    }

    Sleep(100000);
    std::cout << "All threads finished." << std::endl;
    return 0;
}