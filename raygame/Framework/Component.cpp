#include "Component.h"

Component::Component()
{
	m_owner = nullptr;
	m_name = nullptr;
}

Component::Component(Actor* owner)
{
	m_owner = owner;
	m_name = nullptr;
}
