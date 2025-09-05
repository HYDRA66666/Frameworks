#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "Foundation/PrintCenter.h"
#include "Foundation/Log.h"
#include "Foundation/Progress.h"

using namespace HYDRA15::Foundation::secretary;



int main() {
    PrintCenter& pc = PrintCenter::get_instance();
    auto id = pc.new_bottom(1234);
    
    for(unsigned int i = 0; i <= 1000; i += 10) {
        if (i % 10 == 0)
            pc.update_bottom(id, 1234, Progress::simple_bar("Progress", i / 1000.0f, 30, '#'));
        pc << Log::log("Main", "Current progress: " + std::to_string(i / 10) + "%").withoutColor;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for(unsigned int i = 0; i < std::numeric_limits<unsigned int>::max(); ++i) {
    }
}