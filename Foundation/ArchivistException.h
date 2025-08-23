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
            

            // 条目
            StaticUInt entry = 0xB00;

            // 表
            StaticUInt tablet = 0xC00;
        }iExptCodes;

        static struct Visualize
        {
            StaticString archivist = "Archivist Exception";

            // 索引
            StaticString index = "Index Exception";
            
            // 条目
            StaticString entry = "Entry Exception";
            
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

        // 索引
        static Archivist IndexUnknownExpt();
        

        // 条目
        static Archivist EntryUnknownExpt() noexcept;
        
        // 表
        static Archivist TabletUnknownExpt() noexcept;
        
    };


}