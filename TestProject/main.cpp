#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "Foundation/PrintCenter.h"
#include "Foundation/Log.h"
#include "Foundation/Progress.h"

using namespace HYDRA15::Foundation::secretary;

void pg(int sleep)
{
    PrintCenter& pc = PrintCenter::get_instance();
    auto id = pc.new_bottom(1234);

    for (unsigned int i = 0; i <= 1000; i += 10) {
        if (i % 10 == 0)
            pc.update_bottom(id, 1234, Progress::simple_bar("Progress", i / 1000.0f, 30, '#'));
        pc << Log::log("Main", "Current progress: " + std::to_string(i / 10) + "%").withoutColor;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
}

int main() {
    std::thread t1(pg, 100);
    std::thread t2(pg, 120);
    std::thread t3(pg, 130);
    std::thread t4(pg, 190);
    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();

    std::this_thread::sleep_for(std::chrono::seconds(30));
}