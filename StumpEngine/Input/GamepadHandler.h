﻿#pragma once
#include <memory>
#include <SDL3/SDL_gamepad.h>

#include "GamePadEnums.h"
#include <Command.h>

namespace stump
{
    class GamepadHandler final
    {
    public:
        explicit GamepadHandler();
        ~GamepadHandler();

        GamepadHandler(const GamepadHandler& other) = delete;
        GamepadHandler(GamepadHandler&& other) = delete;
        GamepadHandler& operator=(const GamepadHandler& other) = delete;
        GamepadHandler& operator=(GamepadHandler&& other) = delete;

        void poll_gamepad() const;
        void bind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type, std::unique_ptr<Command>&& command) const;
        void unbind_gamepad_button(SDL_GamepadButton gamepad_button, input_pressed_type input_type) const;

    private:
        class GamepadHandlerImpl;
        std::unique_ptr<GamepadHandlerImpl> m_handler_imlp;
    };
} // namespace stump
