#include "pch.h"
#include "framework.h"

#include "Foundation/iExceptionBase.h"
#include "Foundation/Infomation.h"

namespace HYDRA15::Frameworks::Judge
{
    // 完整的 iException 类，相比基类额外记录了处理流程中所需要的信息
    class iException : public HYDRA15::Frameworks::Foundation::iExceptionBase
    {
        Foundation::Infomation procInfo;
        const std::exception innerExpt;

    public:
        // 构造和析构
        iException() noexcept = delete;
        iException(
            const std::string& desp, 
            const Foundation::Infomation& info = {},
            const std::exception& inner = std::exception()
        ) noexcept;
        virtual ~iException() noexcept = default;

        // 获取和写入处理信息
        Foundation::Infomation& getProcInfo() const noexcept;
        std::exception& getInnerExpt() const noexcept;
    };
}