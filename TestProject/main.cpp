#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "Foundation/PrintCenter.h"
#include "Foundation/log.h"

using namespace HYDRA15::Foundation::secretary;



int main() {
    PrintCenter::print(log::info("Main", "log message").withColor);
    PrintCenter::print(log::warn("Main", "warn message").withColor);
    PrintCenter::print(log::error("Main", "error message").withColor);
    PrintCenter::print(log::fatal("Main", "fatal message").withColor);
    PrintCenter::print(log::debug("Main", "debug message").withColor);
    PrintCenter::print(log::trace("Main", "trace message").withColor);
}