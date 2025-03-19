#pragma once
#include "DynamicArray.h"
#include "BlackboardQuestion.h"

class Actor;
class Scene;

class Blackboard
{
private:
	bool m_ownerIsScene;
	union
	{
		Actor* m_actorOwner;
		Scene* m_sceneOwner;
	};
	DynamicArray<BlackboardQuestion> m_questions;

public:

};