#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Foundation::LibInfomation
{
    // 集中管理的库代码
    static struct LibID
    {
        StaticUInt unknown = 0x00;

        StaticUInt typical = 0xA0;
        StaticUInt system = 0xA1;

        // 内部子系统库代码
        StaticUInt lib = 0xA00;

        StaticUInt Foundation = 0xA01;      // 基础库
        StaticUInt StaffUnion = 0xA02;      // 多线程相关
        StaticUInt Archivist = 0xA03;       // 注册机


        StaticUInt Judge = 0xB01;           // 错误处理服务器
        StaticUInt Postman = 0xB02;         // 消息服务器
        StaticUInt Clerk = 0xB03;           // 日志服务器

        StaticUInt Translator = 0xC01;      // 文件解析器
        StaticUInt Sentry = 0xC02;          // 守护线程
        StaticUInt Librarian = 0xC03;       // 数据库

    }libID;
}