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

using namespace HYDRA15::Foundation::Archivist;



int main() {
    Tablet tab(Tablet::Type::map);

    tab[0] = Tablet(Tablet::Type::list);
    tab[1] = Tablet(Tablet::Type::queue);
    tab[2] = Tablet(Tablet::Type::map);

    tab[0].get<Tablet&>().push(42);
    tab[0].get<Tablet&>().push(std::string("Hello, World!"));
    tab[0].get<Tablet&>().push(datas(7, "Seven"));

    tab[1].get<Tablet&>().push(3.14);
    tab[1].get<Tablet&>().push(std::string("Queue Item"));

    tab[2].get<Tablet&>()[std::string("Key1")] = std::string("Value1");
    tab[2].get<Tablet&>()[std::string("Key2")] = 100;

    tab[3.14] = 66;
    tab[std::string("AnotherKey")] = datas(1, "One");

    //for(auto& i:tab)
    //    std::cout << i.first.info() << " => " << i.second.info() << std::endl;
    for(auto& i:tab[0].get<Tablet>())
        std::cout << i.first.info() << " => " << i.second.info() << std::endl;
    //for (auto& i : tab[2].get<Tablet>())
    //    std::cout << i.first.info() << " => " << i.second.info() << std::endl;

}