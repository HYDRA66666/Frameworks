#pragma once
#include "framework.h"
#include "pch.h"

namespace HYDRA15::Foundation::Secretary
{
    // 格式化进度条
    // 返回格式化后的字符串，用户需要自行处理输出
    class Progress
    {
        // 禁止构造
    private:
        Progress() = delete;
        Progress(const Progress&) = delete;
        ~Progress() = delete;

        // 公有数据
    private:
        static struct Visualize
        {
            StaticString digitalProgressFormat = "{0}... {1:02d}%";
            StaticString simpleBarFormat = "{0}[{1}] {2:02d}%";
        }visualize;

        // 接口
    public:
        static std::string digital(std::string title, float progress);
        static std::string simpleBar(std::string title, float progress, unsigned int barWidth = 10, char barChar = '=');
    };

}