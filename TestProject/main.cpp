#include <iostream>
#include <any>

#include "Foundation/Index.h"
#include "Foundation/Entry.h"
#include "Foundation/ThreadLake.h"
#include "Foundation/iExceptionBase.h"
using namespace HYDRA15::Foundation::Archivist;

int main() {
    Entry entry(Entry::Type::map);
    entry[std::string("int")] = 42;
    entry[std::string("double")] = 3.14;
    entry[std::string("string")] = std::string("Hello World");
    entry[1] = Entry(Entry::Type::list);
    entry[2] = Entry(Entry::Type::queue);
    entry[3] = Entry(Entry::Type::map);
    entry[0] = std::make_shared<HYDRA15::Foundation::Labourer::ThreadLake>(4);

    for(auto& it : entry) {
        std::cout << "Key: " << it.first.info() << ", Value: " << it.second.info() << std::endl;
    }
}