#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    static struct iExceptionCodes
    {
        StaticUInt unknown = 0x0000;

        // 条目
        StaticUInt entry = 0xA00;
        StaticUInt entryEmpty = 0xA01;
        StaticUInt entryDataTypeMismatch = 0xA02;
        StaticUInt entryNotContainer = 0xA03;
        StaticUInt entryInvalidContainerOperation = 0xA04;
        StaticUInt entryKeyTypeMismatch = 0xA05;
        StaticUInt entryContainerIsEmpty = 0xA06;
        StaticUInt entryBadKey = 0xA07;
    }iExptCodes;

    static struct Visualize
    {
        // 条目
        StaticString entryExpt = "Entry Exception";
        StaticString entryEmpty = "Entry: Empty Entry, there is no data here";
        StaticString entryDataTypeMismatch = "Entry: Data type mismatch, this Entry does not have the expected data type";
        StaticString entryNotContainer = "Entry: Not container, this Entry is not a container";
        StaticString entryInvalidContainerOperation = "Entry: Container operation is invalid, this Entry does not support such container operation";
        StaticString entryKeyTypeMismatch = "Entry: Key type mismatch, the key type does not work with current container";
        StaticString entryContainerIsEmpty = "Entry: Container is empty";
        StaticString entryBadKey = "Entry: Bad key, the specific key is not exist";
    }visualize;

    class Archivist :public Referee::iExceptionBase
    {
    public:
        Archivist(
            const std::string& desp = visualize.entryExpt.data(),
            const Referee::iExceptionCode& code = Exceptions::iExptCodes.entry
        ) noexcept;
        Archivist() = delete;
        virtual ~Archivist() noexcept = default;

        // 快速创建异常
        static Archivist make_exception(const Referee::iExceptionCode& exptCode = iExptCodes.unknown) noexcept;

        static Archivist EntryEmpty() noexcept;
        static Archivist EntryDataTypeMismatch() noexcept;
        static Archivist EntryNotContainer() noexcept;
        static Archivist EntryInvalidContainerOperation() noexcept;
        static Archivist EntryKeyTypeMismatch() noexcept;
        static Archivist EntryContainerIsEmpty() noexcept;
        static Archivist EntryBadKey() noexcept;
    };
}