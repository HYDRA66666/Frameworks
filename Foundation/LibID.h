#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Foundation::LibInfo
{
    // 集中管理的库代码
    static struct LibID
    {
        StaticUInt unknown = 0x00;

        StaticUInt typical = 0xA0;
        StaticUInt system = 0xA1;

        // 内部子系统库代码
        StaticUInt lib = 0xA00;

        StaticUInt Foundation = 0xA10;
        StaticUInt Referee = 0xA11;
        StaticUInt Labourer = 0xA12;
        StaticUInt Archivist = 0xA13;
        StaticUInt Expressman = 0xA14;
        StaticUInt Secretary = 0xA15;



    }libID;
}