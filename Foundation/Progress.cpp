#include "pch.h"
#include "Progress.h"

namespace HYDRA15::Foundation::secretary
{
    std::string Progress::digital(std::string title, float progress)
    {
        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;
        return std::format(
            vslz.digitalProgressFormat.data(),
            title,
            static_cast<int>(progress * 100)
        );
    }

    std::string Progress::simple_bar(std::string title, float progress, unsigned int barWidth, char barChar)
    {
        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;

        size_t bar = static_cast<size_t>(barWidth * progress);
        size_t space = barWidth - bar;

        return std::format(
            vslz.simpleBarFormat.data(),
            title,
            std::string(bar, barChar) + std::string(space, ' '),
            static_cast<int>(progress * 100)
        );
    }
}
