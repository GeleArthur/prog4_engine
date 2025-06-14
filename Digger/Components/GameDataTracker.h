﻿#pragma once
#include "DirtGrid.h"
#include "GetHit.h"
#include "GridTransform.h"

#include <Event.h>
#include <EventListener.h>
#include <GameObject.h>
#include <vector>
#include <Component/Component.h>

struct Cell
{
    float      cost;
    glm::ivec2 direction;
};

class Digger;
class GameDataTracker : public stump::Component
{
public:
    explicit GameDataTracker(stump::GameObject& attached, DirtGrid& grid);
    void add_player(GridTransform& digger)
    {
        m_players.push_back(&digger);

        m_death_event.push_back(stump::EventListener<>{ [this]() { player_dead(); } });
        digger.get_game_object().get_component<GetHit>()->get_death_event().add_listener(&m_death_event[m_death_event.size() - 1]);
    }
    void remove_player(const GridTransform& digger)
    {
        m_players.erase(std::find(m_players.begin(), m_players.end(), &digger));
    }

    void add_score(stump::Event<int>& score)
    {
        m_add_score.push_back(stump::EventListener<int>{ [this](int score) { score_added(score); } });
        score.add_listener(&m_add_score[m_add_score.size() - 1]);
    }

    using FlowField = std::array<Cell, GridSettings::grid_tile_count.y * GridSettings::grid_tile_count.x>;

    const FlowField& get_flow_field() const
    {
        return m_flow_field;
    }

    void update() override;
    void update_flow_field();

    void write_to_json();

private:
    void player_dead();
    void score_added(int amount);

    FlowField                   m_flow_field{};
    std::vector<GridTransform*> m_players;
    DirtGrid*                   m_grid;

    std::vector<stump::EventListener<>>    m_death_event;
    std::vector<stump::EventListener<int>> m_add_score;

    int m_score{};
};
