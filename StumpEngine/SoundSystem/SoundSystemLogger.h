﻿#pragma once
#include <memory>
#include "SoundSystem.h"

namespace stump
{
    class SoundSystemLogger final : public SoundSystem
    {
    public:
        explicit SoundSystemLogger(std::unique_ptr<SoundSystem> wrapper);
        void play(const std::string& song_path, float volume) override;

    private:
        std::unique_ptr<SoundSystem> m_wrapper_around;
    };
} // namespace stump
