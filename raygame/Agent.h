#pragma once
#include "Actor.h"
#include "Vector2.h"
#include <initializer_list>
#include "List.h"

class Agent : public Actor
{
private:
	MathLibrary::Vector2 m_velocity;
	MathLibrary::Vector2 m_heading;


public:
	Agent();
	Agent(Component* behaviors[], int length);


};