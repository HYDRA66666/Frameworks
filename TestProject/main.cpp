#include <iostream>
#include <any>

#include "Foundation/Index.h"
#include "Foundation/Entry.h"
using namespace HYDRA15::Foundation::Archivist;

int main() {
    Entry top(Entry::Type::list);

    top.push(Entry(Entry::Type::map));
    top.push(Entry(Entry::Type::queue));

    top[0][std::string("int")] = 42;
    top[0][std::string("string")] = std::string("Hello, World!");

    top[1].push(std::string("Queue Entry 1"));
    top[1].push(std::string("Queue Entry 2"));

    std::cout << "Top Entry Size: " << top.size() << std::endl;
    std::cout << "First Map Entry (int): " << top[0][std::string("int")].get_data_type().name() << std::endl;
    std::cout << "First Map Entry (string): " << top[0][std::string("string")].get_data_type().name() << std::endl;
    
    std::cout << "int: " << int(top[0][std::string("int")]) << std::endl;
    std::cout << "string: " << std::string(top[0][std::string("string")]) << std::endl;

    std::cout << "Queue Front: " << std::string(top[1].front()) << std::endl;
    top[1].pop();
    std::cout << "Queue Front after pop: " << std::string(top[1].front()) << std::endl;
}