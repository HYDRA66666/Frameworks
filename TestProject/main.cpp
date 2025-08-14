#include <iostream>
#include <string>
#include <mutex>
#include "../Archivist/Registry.h"

using namespace HYDRA15::Frameworks::Archivist;

void PrintResult(const std::string& testName, const std::string& expected, const std::string& actual) {
    std::cout << "[测试] " << testName << "\n";
    std::cout << "  预期: " << expected << "\n";
    std::cout << "  实际: " << actual << "\n";
    std::cout << "-----------------------------\n";
}

int main() {
    Registry<unsigned int, std::string, std::mutex> reg(100, 10); // 起始键100，最大容量10

    // 主动注册
    try {
        reg.regist(101, "Alice");
        PrintResult("主动注册101", "注册成功", "注册成功");
    }
    catch (const std::exception& e) {
        PrintResult("主动注册101", "注册成功", e.what());
    }

    // 主动注册已存在键
    try {
        reg.regist(101, "Bob");
        PrintResult("主动注册101(重复)", "抛出KeyExists异常", "未抛出异常");
    }
    catch (const std::exception& e) {
        PrintResult("主动注册101(重复)", "抛出KeyExists异常", e.what());
    }

    // 被动注册
    unsigned int key2 = 0;
    try {
        key2 = reg.regist("Charlie");
        PrintResult("被动注册Charlie", "返回新键102", std::to_string(key2));
    }
    catch (const std::exception& e) {
        PrintResult("被动注册Charlie", "返回新键102", e.what());
    }

    // 懒惰注册
    unsigned int key3 = 0;
    try {
        key3 = reg.regist();
        PrintResult("懒惰注册", "返回新键103，值为空字符串", std::to_string(key3));
    }
    catch (const std::exception& e) {
        PrintResult("懒惰注册", "返回新键103", e.what());
    }

    // 查找
    try {
        std::string& val = reg.find(101);
        PrintResult("查找101", "Alice", val);
    }
    catch (const std::exception& e) {
        PrintResult("查找101", "Alice", e.what());
    }

    // 修改
    try {
        reg.find(101) = "AliceUpdated";
        std::string& val = reg.find(101);
        PrintResult("修改101", "AliceUpdated", val);
    }
    catch (const std::exception& e) {
        PrintResult("修改101", "AliceUpdated", e.what());
    }

    // 注销
    bool unregResult = reg.unregist(101);
    PrintResult("注销101", "true", unregResult ? "true" : "false");

    // 查找已注销
    try {
        std::string& val = reg.find(101);
        PrintResult("查找已注销101", "抛出KeyNotFound异常", val);
    }
    catch (const std::exception& e) {
        PrintResult("查找已注销101", "抛出KeyNotFound异常", e.what());
    }

    // 注销不存在的键
    bool unregResult2 = reg.unregist(999);
    PrintResult("注销不存在的999", "false", unregResult2 ? "true" : "false");

    // 填满注册机
    reg.unregist(102);
    reg.unregist(103);
    int fillCount = 0;
    for (int i = 0; i < 10; ++i) {
        try {
            reg.regist("User" + std::to_string(i));
            ++fillCount;
        }
        catch (const std::exception& e) {
            PrintResult("填充注册机", "注册成功", e.what());
        }
    }
    PrintResult("注册机填充数量", "10", std::to_string(fillCount));

    // 超容量注册
    try {
        reg.regist("OverflowUser");
        PrintResult("超容量注册", "抛出TabletFull异常", "未抛出异常");
    }
    catch (const std::exception& e) {
        PrintResult("超容量注册", "抛出TabletFull异常", e.what());
    }

    return 0;
}