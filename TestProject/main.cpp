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
    Index idx1 = 42;

    std::cout << static_cast<int>(idx1) << std::endl;
}