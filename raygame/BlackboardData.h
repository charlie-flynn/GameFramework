#pragma once
#include "Vector2.h"

enum EBlackboardDataTypes
{
	UNKNOWN = 0,
	INT,
	VECTOR2,
};

struct BlackboardData
{
public:
	EBlackboardDataTypes dataType;
	union
	{
		int intData;
		MathLibrary::Vector2 vector2Data;
	};

	BlackboardData();
	BlackboardData(int data);
	BlackboardData(MathLibrary::Vector2 data);
	BlackboardData(float vector2DataX, float vector2DataY);
};