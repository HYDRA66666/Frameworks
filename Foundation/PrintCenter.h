#pragma once
#include "framework.h"
#include "pch.h"

#include "SecretaryException.h"
#include "Registry.h"
#include "iMutexies.h"
#include "Background.h"
#include "DateTime.h"
#include "SharedContainerBase.h"

namespace HYDRA15::Foundation::Secretary
{
    // 统一输出接口
    // 提供滚动消息、底部消息和写入文件三种输出方式
    // 提交消息之后，调用 notify() 方法通知后台线程处理，这在连续提交消息时可以解约开销
    class PrintCenter :Labourer::Background
    {
        /***************************** 公有单例 *****************************/
    private:
        // 禁止外部构造
        PrintCenter();
        PrintCenter(const PrintCenter&) = delete;

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
            Milliseconds refreshInterval = Milliseconds(300); // 最短刷新间隔

            Milliseconds btmMsgDispTimeout = Milliseconds(1000);        // 超过此时间则不展示
            Milliseconds btmMsgExistTimeout = Milliseconds(30000);      // 超过此时间则删除
            static const size_t maxBtmChars = 100;                   // 最大底部消息字符数
            StaticString otherBtmMsgFormat = "  ... and {0} more";

            StaticString fileNameFormat = ".\\Log_{0}.log";
            Milliseconds fileRefreshTime = Milliseconds(5000);
            
        }cfg;

        // 辅助寒素
    private:
        std::string clear_bottom_msg();    // 清除底部消息
        std::string print_rolling_msg(); // 输出滚动消息
        std::string print_bottom_msg();  // 输出底部消息
        std::string print_file_msg();    // 输出文件消息

        // 工作
    private:
        std::condition_variable sleepcv;
        std::mutex sleeplock;
        bool working = true;
        bool onPause = false;
        TimePiont lastRefresh = TimePiont::clock::now();
        virtual void work(Background::ThreadInfo&) override;

        // 接口
    public:
        void notify();  // 刷新
        PrintCenter& operator<<(const std::string& content);    // 快速输出，滚动消息+文件+刷新
        void pause();   // 暂停输出，所有内容都将暂存
        void unpause(); // 允许输出，调用之后需要调用 notify() 方法刷新


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
            int token;
            TimePiont lastUpdate;
            bool neverExpire = false;
            std::string content;
            BottomControlBlock& operator=(const BottomControlBlock&);
        };

        using BtmMsgTab = Archivist::IntRegistry<BottomControlBlock>;
        BtmMsgTab btmMsgTab;
        std::mutex btmMsgTabLock;
    public:
        using ID = BtmMsgTab::UintIndex;

        // 接口
    public:
        ID new_bottom(int token, bool nvrExpr = false);
        void update_bottom(ID id, int token, const std::string& content);
        bool check_bottom(ID id);
        bool remove_bottom(ID id, int token);


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
