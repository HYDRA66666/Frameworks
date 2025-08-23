#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Archivist::iExceptions
{
    // 异常代码
    static struct iExceptionCodes
    {
        // 注册机
        StaticUInt registry = 0xA00; 
        // 库
        StaticUInt regiestTabInvalidMaxSize = 0xA01;
        StaticUInt registryTabFull = 0xA02;
        // 键
        StaticUInt registryKeyExists = 0xA11;
        StaticUInt registryKeyNotFound = 0xA12;
        StaticUInt registryKeyOverflow = 0xA13;

    } iExptCodes;
}

