#pragma once
#include "pch.h"
#include "framework.h"

#include "Foundation/iExceptionBase.h"
#include "Foundation/LibID.h"
#include "iExceptionInfomation.h"

namespace HYDRA15::Frameworks::Archivist::iExceptions
{
    class Registry : public Foundation::iExceptionBase
    {
        static struct Visualize
        {
            StaticString regExpt = "Registry Exception";

            StaticString regTabInvalidMaxSize = "Registry: Invalid maximum size for registry table";
            StaticString regTabFull = "Registry: Registry table is full"; 

            StaticString regKeyExists = "Registry: Key already exists";
            StaticString regKeyNotFound = "Registry: Key not found";
            StaticString regKeyOverflow = "Registry: Key overflow, cannot register more items";
        }visualize;

    public:
        Registry(
            const std::string& desp = Visualize::regExpt.data(),
            const unsigned int& code = iExptCodes.registry
        ) noexcept;
        Registry() = delete;
        virtual ~Registry() noexcept = default;

        // 快速创建异常
        static Registry make_exception(unsigned int exptCode) noexcept;

        static Registry TabletInvalidMaxSize() noexcept;
        static Registry TabletFull() noexcept;

        static Registry KeyExists() noexcept;
        static Registry KeyNotFound() noexcept;
        static Registry KeyOverflow() noexcept;
    };
}