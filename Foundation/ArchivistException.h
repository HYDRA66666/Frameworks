#pragma once
#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    static struct iExceptionCodes
    {
        StaticUInt archivist = 0x0000;

        // 索引
        StaticUInt index = 0xA00;


        // 条目
        StaticUInt entry = 0xB00;
        StaticUInt entryEmpty = 0xB01;
        StaticUInt entryNotEndpoint = 0xB02;
        StaticUInt entryNotContainer = 0xB03;
        StaticUInt entryDataTypeMismatch = 0xB04;
        StaticUInt entryInvalidContainerOperation = 0xB05
;
    }iExptCodes;

    static struct Visualize
    {
        StaticString archivist = "Archivist Exception";

        // 索引
        StaticString index = "Index Exception";

        // 条目
        StaticString entry = "Entry Exception";
    }visualize;


    class Archivist :public Referee::iExceptionBase
    {
    public:
        Archivist(
            const std::string& desp = visualize.archivist.data(),
            const Referee::iExceptionCode& code = Exceptions::iExptCodes.archivist
        ) noexcept;
        Archivist() = delete;
        virtual ~Archivist() noexcept = default;

        // 快速创建异常
        static Archivist make_exception(const Referee::iExceptionCode& exptCode = iExptCodes.archivist) noexcept;

        // 索引
        // 条目
        static Archivist EntryUnknownExpt();
        static Archivist EntryEmpty();
        static Archivist EntryNotEndpoint();
        static Archivist EntryNotContainer();
        static Archivist EntryDataTypeMismatch();
        static Archivist EntryInvalidContainerOperation();
    };


}