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

        // 唯一实例
        static Progress instance;

        // 获取接口
    public:
        Progress& get_instance();

    public:
        ~Progress();

        /***************************** 公 用 *****************************/
        // 类型
        using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

        // 配置
        struct Config
        {

        }cfg;

        // 后台
        virtual void work(Background::ThreadInfo& info) override;


        /***************************** 进度相关 *****************************/
        // 类型定义
    private:
        struct ProgressControlBlock
        {
            int token;
            TimePoint lastUpdate;
            float progress;
        };
        using ProgMap = Archivist::RegistryInt<ProgressControlBlock, std::mutex>;
        using Id = ProgMap::UintIndex;

        // 数据
        ProgMap progTab;
        TimePoint lastRefresh;

        // 接口
    public:
        Id create_progress(int token);
        bool update_progress(Id id, int token, float progress);
        bool remove_progress(Id id, int token);
        bool check_progress(Id id, int token);
    };
}
