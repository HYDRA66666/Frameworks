#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Judge
{
    // 集中管理的库代码
    static struct iExceptionLibID
    {
        iExceptionCode unknown = 0x00;
        
        iExceptionCode typical = 0xA0;
        iExceptionCode system = 0xA1;

        iExceptionCode lib = 0xA00;
        iExceptionCode Foundation = 0xA01;
        iExceptionCode Judge = 0xA02;
        iExceptionCode StaffUnion = 0xA03;
        iExceptionCode Archivist = 0xA04;
        iExceptionCode Translator = 0xA05;
        iExceptionCode Postman = 0xA06;
        iExceptionCode Clerk = 0xA07;
        iExceptionCode Sentry = 0xA08;
        iExceptionCode Librarian = 0xA09;
    }iExptLibID;
}