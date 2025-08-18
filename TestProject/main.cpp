#include "Foundation/Entry.h"

using namespace HYDRA15::Foundation::Archivist;

int main() {
    // 创建一个整数映射的Entry
    Entry intMap = { {1, 2}, {2, "Entry()"} };
    // 创建一个字符串映射的Entry
    Entry stringMap = { {"key1", 3.3}, {"key2", "Entry()"} };
    // 创建一个双端队列的Entry
    Entry dequeList{ "Entry()", 2 };

    Entry multipalList = {
        {
            "intMap",{
                {1,2},
                {2,"Entry"},
                {3,"Entry"}
            }
        },
        {
            "stringMap",{
                {"key1",3.3},
                {"key2","Entry()"},
                {"key3","Entry()"}
            }
        },
        {
            "dequeList",{
                "Entry()",
                2,
                3.14
            }
        }
    };
    
    return 0;
}