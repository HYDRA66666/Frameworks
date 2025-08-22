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

            // 索引
            StaticUInt index = 0xA00;
            StaticUInt indexTypeMismatch = 0xA01;

            // 条目
            StaticUInt entry = 0xB00;
            StaticUInt entryEmpty = 0xB01;
            StaticUInt entryNotEndpoint = 0xB02;
            StaticUInt entryNotContainer = 0xB03;
            StaticUInt entryDataTypeMismatch = 0xB04;
            StaticUInt entryInvalidContainerOperation = 0xB05;
            StaticUInt EntryElementNotFound = 0xB06;
            StaticUInt EntryContainerEmpty = 0xB07;
            StaticUInt EntryContainerFull = 0xB08;
            StaticUInt EntryInvalidContainerSize = 0xB09;
        }iExptCodes;

        static struct Visualize
        {
            StaticString archivist = "Archivist Exception";

            // 索引
            StaticString index = "Index Exception";
            StaticString indexTypeMismatch = "Index: Index type mismatch";

            // 条目
            StaticString entry = "Entry Exception";
            StaticString entryEmpty = "Entry: Entry is empty";
            StaticString entryNotEndpoint = "Entry: Entry is not an endpoint";
            StaticString entryNotContainer = "Entry: Entry is not a container";
            StaticString entryDataTypeMismatch = "Entry: Entry data type mismatch";
            StaticString entryInvalidContainerOperation = "Entry: Invalid container operation";
            StaticString EntryElementNotFound = "Entry: Element not found in container";
            StaticString EntryContainerEmpty = "Entry: Container is empty";
            StaticString EntryContainerFull = "Entry: Container is full";
            StaticString EntryInvalidContainerSize = "Entry: Invalid container size";

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

        // 索引
        static Archivist IndexUnknownExpt();
        static Archivist IndexTypeMismatch();

        // 条目
        static Archivist EntryUnknownExpt() noexcept;
        static Archivist EntryEmpty() noexcept;
        static Archivist EntryNotEndpoint() noexcept;
        static Archivist EntryNotContainer() noexcept;
        static Archivist EntryDataTypeMismatch() noexcept;
        static Archivist EntryInvalidContainerOperation() noexcept;
        static Archivist EntryElementNotFound() noexcept;
        static Archivist EntryContainerEmpty() noexcept;
        static Archivist EntryContainerFull() noexcept;
        static Archivist EntryInvalidContainerSize() noexcept;

        
    };


}