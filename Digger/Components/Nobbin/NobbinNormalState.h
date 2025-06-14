﻿#pragma once
#include "INobbinState.h"

#include <EngineTime.h>
#include <vec2.hpp>

class NobbinNormalState final : public INobbinState
{
public:
    explicit NobbinNormalState(Nobbin& nobbin);
    std::unique_ptr<INobbinState> update() override;
    bool                          can_mine() override;

private:
    float      m_move_delay{};
    float      m_time_before_transform{ stump::EngineTime::instance().get_current_time() + 10 };
    Nobbin*    m_nobbin;
    glm::ivec2 m_last_move_direction{};
};
