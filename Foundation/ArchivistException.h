#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class Archivist :public Referee::iExceptionBase
    {
        static struct iExceptionCodes
        {
            StaticUInt archivist = 0x0000;


            // 条目
            StaticUInt entry = 0xA00;
            StaticUInt entryEmpty = 0xA01;
            StaticUInt entryTypeMismatch = 0xA02;

            // 索引
            StaticUInt index = 0xB00;
            StaticUInt indexEmpty = 0xB01;
            StaticUInt indexTypeMismatch = 0xB02;

            // 表
            StaticUInt tablet = 0xC00;
            StaticUInt tabletInvalidContainerOperation = 0xC01;
            StaticUInt tabletContainerEmpty = 0xC02;
            StaticUInt tabletContainerFull = 0xC03;
            StaticUInt tabletListRangeExceed = 0xC04;
            StaticUInt tabletListBadSize = 0xC05;
        }iExptCodes;

        static struct Visualize
        {
            StaticString archivist = "Unknown Archivist Exception";

            // 条目
            StaticString entry = "Unknown Entry Exception";
            StaticString entryEmpty = "Entry: This Entry is empty";
            StaticString entryTypeMismatch = "Entry: Entry data type mismatch";

            // 索引
            StaticString index = "Unknown Index Exception";
            StaticString indexEmpty = "Index: This Index is empty";
            StaticString indexTypeMismatch = "Index: Index data type mismatch";
            
            // 表

        }visualize;
    public:
        Archivist(
            const std::string& desp = visualize.archivist.data(),
            const Referee::iExceptionCode& code = iExptCodes.archivist
        ) noexcept;
        Archivist() = delete;
        virtual ~Archivist() noexcept = default;

        // 快速创建异常
        static Archivist make_exception(const Referee::iExceptionCode& exptCode = iExptCodes.archivist) noexcept;

        // 条目
        static Archivist EntryUnknownExpt() noexcept;
        static Archivist EntryEmpty() noexcept;
        static Archivist EntryTypeMismatch() noexcept;

        // 索引
        static Archivist IndexUnknownExpt() noexcept;
        static Archivist IndexEmpty() noexcept;
        static Archivist IndexTypeMismatch() noexcept;
        
        // 表
        static Archivist TabletUnknownExpt() noexcept;
        static Archivist TabletInvalidContainerOperation() noexcept;
        static Archivist TabletContainerEmpty() noexcept;
        static Archivist TabletContainerFull() noexcept;
        static Archivist TabletListRangeExceed() noexcept;
        static Archivist TabletListBadSize() noexcept;
        
    };


}