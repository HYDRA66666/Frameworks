#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Foundation::LibInfo
{
    // 集中管理的库代码
    static struct libID
    {
        static_uint unknown = 0x00;

        static_uint typical = 0xA0;
        static_uint system = 0xA1;

        // 内部子系统库代码
        static_uint lib = 0xA00;

        static_uint Foundation = 0xA10;
        static_uint referee = 0xA11;
        static_uint labourer = 0xA12;
        static_uint archivist = 0xA13;
        static_uint expressman = 0xA14;
        static_uint secretary = 0xA15;
        static_uint assistant = 0xA16;



    }libID;
}