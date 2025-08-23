#include <iostream>
#include <any>
#include <format>
#include <string>

class datas
{
public:
    int a;
    std::string b;
    datas(int a, const std::string& b) : a(a), b(b) {}
};

namespace std
{
    std::string to_string(const datas& d)
    {
        return std::format("datas(a: {}, b: {})", d.a, d.b);
    }
}


#include "Foundation/Entry.h"
using namespace HYDRA15::Foundation::Archivist;



int main() {
    Entry e1 = 42;
    Entry e2 = std::string("Hello, World!");
    Entry e3; // Empty entry
    //Entry e4 = datas(10, "Sample");

    std::cout << "e1: " << e1.info() << std::endl;
    std::cout << "e2: " << e2.info() << std::endl;
    std::cout << "e3: " << e3.info() << std::endl;
    //std::cout << "e4: " << e4.info() << std::endl;

    Entry e11 = e1;
    Entry e22 = std::move(e2);
    //Entry e44 = e4;
    //static_cast<datas&>(e44).a = 20;

    std::cout << "e11: " << e11.info() << std::endl;
    std::cout << "e22: " << e22.info() << std::endl;
    std::cout << "e2 after move: " << e2.info() << std::endl;
    //std::cout << "e4 after modify: " << e4.info() << std::endl;
    //std::cout << "e44: " << e4.info() << std::endl;
}