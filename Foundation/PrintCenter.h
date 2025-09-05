#pragma once
#include "framework.h"
#include "pch.h"

#include "secretary_exception.h"
#include "Registry.h"
#include "iMutexies.h"
#include "Background.h"
#include "DateTime.h"

namespace HYDRA15::Foundation::secretary
{
    // 统一输出接口
    // 提供滚动消息、底部消息和写入文件三种输出方式
    // 提交消息之后，调用 notify() 方法通知后台线程处理，这在连续提交消息时可以解约开销
    class PrintCenter :labourer::background
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
        using time_point = std::chrono::steady_clock::time_point;
        using milliseconds = std::chrono::milliseconds;

        // 全局配置
    private:
        struct Config
        {
            milliseconds refreshInterval = milliseconds(300); // 最短刷新间隔

            milliseconds btmMsgDispTimeout = milliseconds(1000);        // 超过此时间则不展示
            milliseconds btmMsgExistTimeout = milliseconds(30000);      // 超过此时间则删除
            static const size_t maxBtmChars = 100;                   // 最大底部消息字符数
            static_string otherBtmMsgFormat = "  ... and {0} more";

            static_string fileNameFormat = ".\\Log_{0}.log";
            milliseconds fileRefreshTime = milliseconds(5000);
            
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
        time_point lastRefresh = time_point::clock::now();
        virtual void work(background::thread_info&) override;

        // 接口
    public:
        void notify();  // 刷新
        PrintCenter& operator<<(const std::string& content);    // 快速输出，滚动消息+文件+刷新
        void pause();   // 暂停输出，所有内容都将暂存
        void unpause(); // 允许输出，调用之后需要调用 notify() 方法刷新


        /***************************** 滚动消息相关 *****************************/
        // 类型定义
    private:
        using rollmsg_list = std::list<std::string>;

        // 数据
    private:
        rollmsg_list* pRollMsgLstFront = new rollmsg_list();
        rollmsg_list* pRollMsgLstBack = new rollmsg_list();
        std::mutex rollMsgLock;
        size_t rollMsgCount = 0;

        // 接口
    public:
        size_t rolling(const std::string& content);


        /***************************** 底部消息相关 *****************************/
       // 类型定义
    private:
        struct bottom_ctrlblk
        {
            int token;
            time_point lastUpdate;
            bool neverExpire = false;
            std::string content;
            bottom_ctrlblk& operator=(const bottom_ctrlblk&);
        };
        using btmmsg_tab = archivist::int_registry<bottom_ctrlblk>;
    public:
        using ID = btmmsg_tab::uint_index;

        // 数据
    private:
        btmmsg_tab btmMsgTab;
        std::mutex btmMsgTabLock;


        // 接口
    public:
        ID new_bottom(int token, bool nvrExpr = false);
        void update_bottom(ID id, int token, const std::string& content);
        bool check_bottom(ID id);
        bool remove_bottom(ID id, int token);


        /***************************** 写入文件相关 *****************************/
        // 类型定义
    private:
        using filemsg_list = std::list<std::string>;

        // 数据
    private:
        filemsg_list* pFMsgLstFront = new filemsg_list();
        filemsg_list* pFMsgLstBack = new filemsg_list();
        std::mutex fileMsgLock;
        std::ofstream logFile;
        time_point lastFileRefresh = time_point::clock::now();
        size_t fileMsgCount = 0;

        // 接口
    public:
        size_t file(const std::string& content);
    };
}
