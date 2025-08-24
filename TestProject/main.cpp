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


#include "Foundation/Entry.h"
#include "Foundation/Index.h"
using namespace HYDRA15::Foundation::Archivist;



int main() {
    std::unordered_map<Index, Entry> map;
    map[42] = 3.14;
    map[3.2] = 1;

    for(auto i :map)
        std::cout << i.first.info() << " -> " << i.second.info() << std::endl;
}