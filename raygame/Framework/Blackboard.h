#pragma once
#include "DynamicArray.h"
#include "BlackboardData.h"
#include <map>

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
	// rip questions ): ): ): ): ): ): ):
	//DynamicArray<BlackboardQuestion> m_questions;

	//DynamicArray<BlackboardData*> m_data;
	std::map<unsigned int, BlackboardData*> m_data;
	
public:
	Blackboard();
	Blackboard(Actor* owner);
	Blackboard(Scene* owner);

	void addData(char* key, BlackboardData* value);
	bool removeData(char* key);
	BlackboardData* getData(char* key);
};