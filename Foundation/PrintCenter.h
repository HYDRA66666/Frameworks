#pragma once
#include "framework.h"
#include "pch.h"

#include "SecretaryException.h"
#include "Registry.h"
#include "iMutexies.h"
#include "Background.h"
#include "to_string.h"
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
        static PrintCenter& get_instance();

    public:
        ~PrintCenter();

        /***************************** 公 用 *****************************/
        // 类型
    private:
        using TimePiont = std::chrono::steady_clock::time_point;
        using Milliseconds = std::chrono::milliseconds;

        // 全局配置
    private:
        struct Config
        {
            Milliseconds btmMsgDispTimeout = Milliseconds(1000);        // 超过此时间则不展示
            Milliseconds btmMsgExistTimeout = Milliseconds(30000);      // 超过此时间则删除
            Milliseconds btmMsgRefreshInterval = Milliseconds(20);   // 底部消息刷新间隔
            static const size_t maxBtmMsgs = 2;                          // 最大底部消息数
            StaticString otherBtmMsgFormat = "  ... and {0} more";

            StaticString fileNameFormat = ".\\Log_{0}.log";
            Milliseconds fileRefreshTime = Milliseconds(5000);
            
        }cfg;

        // 辅助寒素
    private:
        void clear_bottom_msg();    // 清除底部消息
        std::string print_rolling_msg(); // 输出滚动消息
        std::string print_bottom_msg();  // 输出底部消息
        std::string print_file_msg();    // 输出文件消息

        // 工作
    private:
        std::condition_variable sleepcv;
        std::mutex sleeplock;
        bool working = true;
        virtual void work(Background::ThreadInfo&) override;


        /***************************** 滚动消息相关 *****************************/
        // 类型定义
    private:
        using RollingMsgList = std::list<std::string>;

        // 数据
    private:
        RollingMsgList* pRollMsgLstFront = new RollingMsgList;
        RollingMsgList* pRollMsgLstBack = new RollingMsgList;
        std::mutex rollMsgLock;
        size_t rollMsgCount = 0;

        // 接口
    public:
        size_t rolling(const std::string& content);


        /***************************** 底部消息相关 *****************************/
       // 类型定义
    private:
        struct BottomControlBlock
        {
            TimePiont lastUpdate;
            int token;
            std::string content;
            std::mutex lock;
            BottomControlBlock(const TimePiont&, int, const std::string&);
            BottomControlBlock(const BottomControlBlock&);
            BottomControlBlock();
            BottomControlBlock& operator=(const BottomControlBlock&);
        };

        class BtmMsgMap : public Archivist::RegistryInt<BottomControlBlock, std::mutex>
        {
        public:
            using ID = Archivist::RegistryInt<BottomControlBlock, std::mutex>::UintIndex;

            using iterator = RegTab::iterator;
            iterator begin();
            iterator end();
            using Archivist::RegistryInt<BottomControlBlock, std::mutex>::lock;
        }btmMsgTab;

    public:
        using ID = BtmMsgMap::ID;

        // 数据
    private:
        TimePiont lastBtmRefresh = TimePiont::clock::now();

        // 接口
    public:
        ID new_bottom(int token);
        void update_bottom(ID id, int token, const std::string& content);
        bool check_bottom(ID id);
        void remove_bottom(ID id, int token);


        /***************************** 写入文件相关 *****************************/
        // 类型定义
    private:
        using FileMsgList = std::list<std::string>;

        // 数据
    private:
        FileMsgList* pFMsgLstFront = new FileMsgList;
        FileMsgList* pFMsgLstBack = new FileMsgList;
        std::mutex fileMsgLock;
        std::ofstream logFile;
        TimePiont lastFileRefresh = TimePiont::clock::now();
        size_t fileMsgCount = 0;

        // 接口
    public:
        size_t file(const std::string& content);
    };
}
