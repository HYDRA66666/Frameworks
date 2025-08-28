#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "Foundation/PrintCenter.h"
#include "Foundation/Log.h"
#include <Windows.h>

using namespace HYDRA15::Foundation::Secretary;



int main() {
    Log::log("Test", "This is a log message.");
    Log::warning("Test", "This is a warning message.");
    Log::error("Test", "This is an error message.");
    Log::debug("Test", "This is a debug message.");
}