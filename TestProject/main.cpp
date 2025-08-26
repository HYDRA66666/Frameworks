#include <iostream>
#include <any>
#include <format>
#include <string>
#include <unordered_map>

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
        return std::format("[datas(a: {}, b: {})]", d.a, d.b);
    }

}


#include "Foundation/Tablet.h"
#include "Foundation/Registry.h"

using namespace HYDRA15::Foundation::Archivist;



int main() {
    Entry e = 41;
    Entry e2 = 3.14;
    Entry e3 = std::string("Hello, World!");
    Entry e4 = datas(7, "example");

    std::cout << e.info() << std::endl;
    std::cout << e2.info() << std::endl;
    std::cout << e3.info() << std::endl;
    std::cout << e4.info() << std::endl;
}