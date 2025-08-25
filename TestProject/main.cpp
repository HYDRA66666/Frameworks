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
    Registry<std::mutex> r(10);
    r.regist(42, Entry(datas(1, "Hello")));
    r.regist(100, Entry(std::string("World")));

    std::cout << r.find(42).info() << std::endl;
    std::cout << r.find(100).info() << std::endl;
}