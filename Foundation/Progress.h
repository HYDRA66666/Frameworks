#pragma once
#include "framework.h"
#include "pch.h"

#include "SecretaryException.h"
#include "Background.h"
#include "Registry.h"

namespace HYDRA15::Foundation::Secretary
{
    // 统一进度输出接口，接受进程进度报告、格式化成进度条、最后输出至 PrintCenter
    class Progress :Labourer::Background
    {
        /***************************** 公有单例 *****************************/
    private:
        // 禁止外部构造
        Progress();
        Progress(const Progress&) = delete;

        // 获取接口
    public:
        Progress& get_instance();

    public:
        ~Progress();

        /***************************** 公 用 *****************************/
        // 类型
    private:
        using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
        using Milliseconds = std::chrono::milliseconds;

        // 配置
    private:
        static struct Config
        {
            Milliseconds refreshInterval = Milliseconds(150); // 刷新间隔
            Milliseconds displayTimeout = Milliseconds(1000); // 超过此时间未更新则不展示
            Milliseconds existTimeout = Milliseconds(30000);  // 超过此时间未更新则删除
        }cfg;

        // 后台
    private:
        bool working = true;
        virtual void work(Background::ThreadInfo& info) override;


        /***************************** 进度相关 *****************************/
        // 类型定义
    private:
        struct ProgressControlBlock
        {
            int token;
            std::string title;
            std::function<void(int, const std::string&)> timeoutCallback;
            TimePoint lastUpdate;
            std::atomic<float> progress;
        };
        using ProgMap = Archivist::IntRegistry<ProgressControlBlock, std::mutex>;
    public:
        using ID = ProgMap::UintIndex;

        // 数据
        ProgMap progTab;
        TimePoint lastRefresh;

        // 接口
    public:
        static ID create(int token, std::string title);
        static void update(ID id, int token, float progress);
        static float check(ID id, int token);   // 返回 -1 表示未找到
        static bool remove(ID id, int token);
    };
}
