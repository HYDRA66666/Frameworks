#pragma once
#include "framework.h"
#include "pch.h"

#include "SecretaryException.h"
#include "Registry.h"
#include "iMutexies.h"
#include "Background.h"
#include "SharedContainerBase.h"

namespace HYDRA15::Foundation::Secretary
{
    // 统一输出接口
    // 提供滚动消息、底部消息和写入文件三种输出方式
    class PrintCenter :Labourer::Background
    {
        /***************************** 公有单例 *****************************/
    private:
        // 禁止外部构造
        PrintCenter();
        PrintCenter(const PrintCenter&) = delete;

        // 唯一实例
        static PrintCenter instance;

        // 获取接口
    public:
        PrintCenter& get_instance();

    public:
        ~PrintCenter();

        /***************************** 公 用 *****************************/
        // 类型
    private:
        using TimePiont = std::chrono::time_point<std::chrono::steady_clock>;

        // 全局配置
    private:
        static struct Config
        {

        }cfg;

        // 工作
    private:
        virtual void work(Background::ThreadInfo& info) override;

        /***************************** 底部消息相关 *****************************/
        // 类型定义
    private:
        struct BottomControlBlock
        {
            TimePiont lastUpdate;
            const int token;
            std::string content;
        };
        using BottomMsgMap = Archivist::RegistryInt<BottomControlBlock, std::mutex>;
    public:
        using Id = BottomMsgMap::UintIndex;

        // 数据
    private:
        BottomMsgMap botMsgTab;

        // 接口
    public:
        Id new_bottom(int token);
        bool update_bottom(Id id, int token, const std::string& content);
        bool check_bottom(Id id);
        bool remove_bottom(Id id, int token);


        /***************************** 滚动消息相关 *****************************/
        // 类型定义
    private:
        using RollingMsgQueue = std::queue<std::string>;

        // 数据
    private:
        RollingMsgQueue* pRollMsgQueFront;
        RollingMsgQueue* pRollMsgQueBack;
        std::mutex rollMsgLock;
        size_t rollMsgCount;

        // 接口
    public:
        size_t rolling(const std::string& content);


        /***************************** 写入文件相关 *****************************/
        // 类型定义
    private:
        using FileMsgList = std::list<std::string>;

        // 数据
    private:
        StaticString fileNameFormat = ".\\Log_{0}.log";
        FileMsgList* pFMsgLstFront;
        FileMsgList* pFMsgLstBack;
        std::mutex fileMsgLock;
        std::ofstream file;
        TimePiont lastRefresh;
        size_t fileMsgCount;

        // 接口
        size_t file(const std::string& content);
    };
}
