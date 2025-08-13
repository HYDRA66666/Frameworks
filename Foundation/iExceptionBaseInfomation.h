#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Foundation
{
    // 集中管理的库代码
    static struct iExceptionLibID
    {
        iExceptionCode unknown = 0x00;

        iExceptionCode typical = 0xA0;
        iExceptionCode system = 0xA1;

        // 内部子系统库代码
        iExceptionCode lib = 0xA00;

        iExceptionCode Foundation = 0xA01;      // 基础库
        iExceptionCode StaffUnion = 0xA02;      // 多线程相关
        iExceptionCode Archivist = 0xA03;       // 注册机


        iExceptionCode Judge = 0xB01;           // 错误处理服务器
        iExceptionCode Postman = 0xB02;         // 消息服务器
        iExceptionCode Clerk = 0xB03;           // 日志服务器

        iExceptionCode Translator = 0xC01;      // 文件解析器
        iExceptionCode Sentry = 0xC02;          // 守护线程
        iExceptionCode Librarian = 0xC03;       // 数据库
    }iExptLibID;
}