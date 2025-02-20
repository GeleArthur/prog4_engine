#include "GameObject.h"

#include "Texture2D.h"

GameObject::GameObject(Minigin& engine):
	m_engine(engine),
	m_transform(add_component<Transform>(glm::vec2{0.0f, 0.0f}))
{
}

void GameObject::mark_for_deletion()
{
	m_marked_for_deletion = true;
}

void GameObject::fixed_update() const
{
	for (const auto& component : m_components)
	{
		component->fixed_update();
	}
}

Transform& GameObject::get_transform() const
{
	return m_transform;
}

void GameObject::removed_marked_components()
{
	std::erase_if(m_components, [](auto& comp) { return comp->is_marked_for_delection(); });
}

Minigin& GameObject::get_engine() const
{
	return m_engine;
}

bool GameObject::is_marked_for_deletion() const
{
	return m_marked_for_deletion;
}

void GameObject::update() const
{
	for (const auto& component : m_components)
	{
		component->update();
	}
}

void GameObject::render() const
{
	for (const auto& component : m_components)
	{
		component->render();
	}
}
