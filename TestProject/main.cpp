#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "Foundation/PrintCenter.h"
#include "Foundation/log.h"
#include "Foundation/registry.h"
#include "Foundation/utility.h"

using namespace HYDRA15::Foundation::secretary;
using namespace HYDRA15::Foundation::assistant;
using namespace HYDRA15::Foundation::archivist;



int main() {
    registry reg[20];
    PrintCenter::print(hex_heap((unsigned char*)&reg, sizeof(registry) * 30));
}