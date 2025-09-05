#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "libID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class archivist :public referee::iException_base
    {
    public:
        static struct iException_codes
        {
            static_uint archivist = 0x0000;


            // 条目
            static_uint entry = 0xA00;
            static_uint entryEmpty = 0xA01;
            static_uint entryTypeMismatch = 0xA02;

            // 索引
            static_uint index = 0xB00;
            static_uint indexEmpty = 0xB01;
            static_uint indexTypeMismatch = 0xB02;

            // 表
            static_uint tablet = 0xC00;
            static_uint tabletInvalidContainerOperation = 0xC01;
            static_uint tabletContainerEmpty = 0xC02;
            static_uint tabletContainerFull = 0xC03;
            static_uint tabletListRangeExceed = 0xC04;
            static_uint tabletListBadSize = 0xC05;

            // 注册机
            static_uint registry = 0xD00;
            static_uint registryTabletInvalidMaxSize = 0xD01;
            static_uint registryTabletFull = 0xD02;
            static_uint registryKeyExists = 0xD03;
            static_uint registryKeyNotFound = 0xD04;
        }iExptCodes;

    private:
        static struct vslz
        {
            static_string archivist = "Unknown Archivist Exception";

            // 条目
            static_string entry = "Unknown Entry Exception";
            static_string entryEmpty = "Entry: This Entry is empty";
            static_string entryTypeMismatch = "Entry: Entry data type mismatch";

            // 索引
            static_string index = "Unknown Index Exception";
            static_string indexEmpty = "Index: This Index is empty";
            static_string indexTypeMismatch = "Index: Index data type mismatch";
            
            // 表
            static_string tablet = "Unknown Tablet Exception";
            static_string tabletInvalidContainerOperation = "Tablet: Invalid operation for current Tablet type";
            static_string tabletContainerEmpty = "Tablet: Tablet is empty";
            static_string tabletContainerFull = "Tablet: Tablet is full";
            static_string tabletListRangeExceed = "Tablet: List index out of range";
            static_string tabletListBadSize = "Tablet: Invalid list size";

            // 注册机
            static_string registry = "Unknown Registry Exception";
            static_string registryTabletInvalidMaxSize = "Registry: Invalid max size for Registry";
            static_string registryTabletFull = "Registry: Registry is full";
            static_string registryKeyExists = "Registry: Key already exists in Registry";
            static_string registryKeyNotFound = "Registry: Key not found in Registry";

        }vslz;
    public:
        archivist(
            const std::string& desp = vslz.archivist.data(),
            const referee::iException_code& code = iExptCodes.archivist
        ) noexcept;
        archivist() = delete;
        virtual ~archivist() noexcept = default;

        // 快速创建异常
        static archivist make_exception(const referee::iException_code& exptCode = iExptCodes.archivist) noexcept;

        // 条目
        static archivist EntryUnknownExpt() noexcept;
        static archivist EntryEmpty() noexcept;
        static archivist EntryTypeMismatch() noexcept;

        // 索引
        static archivist IndexUnknownExpt() noexcept;
        static archivist IndexEmpty() noexcept;
        static archivist IndexTypeMismatch() noexcept;
        
        // 表
        static archivist TabletUnknownExpt() noexcept;
        static archivist TabletInvalidContainerOperation() noexcept;
        static archivist TabletContainerEmpty() noexcept;
        static archivist TabletContainerFull() noexcept;
        static archivist TabletListRangeExceed() noexcept;
        static archivist TabletListBadSize() noexcept;

        // 注册机
        static archivist RegistryUnknownExpt() noexcept;
        static archivist RegistryTabletInvalidMaxSize() noexcept;
        static archivist RegistryTabletFull() noexcept;
        static archivist RegistryKeyExists() noexcept;
        static archivist RegistryKeyNotFound() noexcept;
        
    };


}