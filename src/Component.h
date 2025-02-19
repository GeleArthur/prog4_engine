#pragma once

class Minigin;
class GameObject;

class Component
{
public:
	explicit Component(GameObject& attached_game_object);
	virtual ~Component() = default;

	[[nodiscard]] GameObject& get_game_object() const;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void fixed_update();
	virtual void update();
	virtual void render();

private:
	GameObject& m_attached_game_object;
};
