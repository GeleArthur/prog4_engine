﻿#pragma once
#include <array>
#include <vec2.hpp>
#include <Component/Component.h>
#include <SDL3/SDL_render.h>

namespace GridSettings
{
    constexpr static glm::ivec2 grid_tile_count{ 15, 10 };
    constexpr static glm::ivec2 grid_offset{ 16, 64 };
    constexpr static glm::ivec2 grid_tile_pixel_size{ 57, 52 };
} // namespace GridSettings

class DirtGrid final : public stump::Component
{
public:
    explicit DirtGrid(stump::GameObject& attached_game_object, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer) override;
    void update() override;

    void delete_on_texture(const SDL_Rect& rect) const;
    bool get_wall_between(const glm::ivec2& from, const glm::ivec2& to) const;
    void clear_wall_between(const glm::ivec2& from, const glm::ivec2& to);

private:
    SDL_Texture* m_texture{};

    std::array<std::array<bool, GridSettings::grid_tile_count.y + 1>, GridSettings::grid_tile_count.x> m_horizonal_walls{};
    std::array<std::array<bool, GridSettings::grid_tile_count.y>, GridSettings::grid_tile_count.x + 1> m_vertical_walls{};
};
