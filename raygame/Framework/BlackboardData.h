#pragma once
#include "Vector2.h"

class Actor;

enum EBlackboardDataTypes
{
	DATA_UNKNOWN = 0,
	DATA_INT,
	DATA_VECTOR2,
	DATA_ACTORPOINTER
};

struct BlackboardData
{
public:
	EBlackboardDataTypes dataType;
	union
	{
		int intData;
		MathLibrary::Vector2 vector2Data;
		Actor* actorData;
	};

	BlackboardData();
	BlackboardData(int data);
	BlackboardData(MathLibrary::Vector2 data);
	BlackboardData(float vector2DataX, float vector2DataY);
	BlackboardData(Actor* data);
};