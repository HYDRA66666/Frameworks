#include <iostream>
#include "Foundation/Entry.h"
using namespace HYDRA15::Foundation::Archivist;

void testEntryInterfaces() {
    // 构造第二层容器 Entry

    Entry ae{ 1,4,5,Entry(3.14),Entry("hello") }; // int, int, int, double, string

    Entry intMapEntry(Entry::Type::intMap);
    intMapEntry[1] = Entry(42); // int
    intMapEntry[2] = Entry(std::string("intMapStr")); // string
    intMapEntry[3] = Entry(Entry::DequeList{ Entry(100), Entry(200) }); // list
    intMapEntry[4] = Entry(Entry::Queue()); // queue

    Entry stringMapEntry(Entry::Type::stringMap);
    stringMapEntry["a"] = Entry(3.14); // double
    stringMapEntry["b"] = Entry(std::string("stringMapStr")); // string
    stringMapEntry["c"] = Entry(Entry::DequeList{ Entry(1), Entry(2) }); // list
    stringMapEntry["d"] = Entry(Entry::Queue()); // queue

    Entry listEntry(Entry::Type::dequeList);
    listEntry.push(Entry(7)); // int
    listEntry.push(Entry(std::string("listStr"))); // string
    listEntry.push(Entry(Entry::IntMap{ {5, Entry(55)} })); // intMap
    listEntry.push(Entry(Entry::Queue())); // queue

    Entry queueEntry(Entry::Type::queue);
    // 注意：queue接口只支持push/pop/front/back，不能直接赋值
    queueEntry.push(Entry(8)); // int
    queueEntry.push(Entry(std::string("queueStr"))); // string
    queueEntry.push(Entry(Entry::StringMap{ {"x", Entry(99)} })); // stringMap
    queueEntry.push(Entry(Entry::DequeList{ Entry(11), Entry(22) })); // list

    // 构造顶层 Entry，类型为列表
    Entry topListEntry{ intMapEntry, stringMapEntry, listEntry, queueEntry };

    // 逐一测试接口
    std::cout << "topListEntry.size(): " << topListEntry.size() << std::endl;
    std::cout << "topListEntry.empty(): " << std::boolalpha << topListEntry.empty() << std::endl;
    std::cout << "topListEntry.front().size(): " << topListEntry.front().size() << std::endl;
    std::cout << "topListEntry.back().size(): " << topListEntry.back().size() << std::endl;

    // 测试 operator[]
    std::cout << "intMapEntry[1] as int: " << intMapEntry[1].operator int() << std::endl;
    std::cout << "intMapEntry[2] as string: " << intMapEntry[2].operator std::string() << std::endl;
    std::cout << "stringMapEntry[\"a\"] as double: " << stringMapEntry["a"].operator double() << std::endl;
    std::cout << "listEntry[0] as int: " << listEntry[0].operator int() << std::endl;
    std::cout << "queueEntry.front() as int: " << queueEntry.front().operator int() << std::endl;

    // 测试 push/pop/resize/clear
    listEntry.push(Entry(999));
    std::cout << "listEntry.size() after push: " << listEntry.size() << std::endl;
    listEntry.resize(2);
    std::cout << "listEntry.size() after resize: " << listEntry.size() << std::endl;
    listEntry.clear();
    std::cout << "listEntry.size() after clear: " << listEntry.size() << std::endl;

    // 测试异常处理
    try {
        Entry endpointEntry(123);
        endpointEntry.push(Entry(456)); // 应抛异常
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught as expected: " << e.what() << std::endl;
    }
}

int main() {
    testEntryInterfaces();
    return 0;
}