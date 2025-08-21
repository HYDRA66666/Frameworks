#include <iostream>
#include <any>

#include "Foundation/Index.h"
using namespace HYDRA15::Foundation::Archivist;

int main() {
    std::any a = 6.6;

    Index index(42);
    Index index2 = 2.6;
    Index index3 = 42;

    IndexBase* idx = &index;
    IndexBase* idx2 = &index2;
    IndexBase* idx3 = &index3;

    std::cout << (index == (*idx2)) << std::endl;
    std::cout << (index == (*idx3)) << std::endl;

    return 0;
}