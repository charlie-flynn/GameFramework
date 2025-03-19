#include "BlackboardData.h"

BlackboardData::BlackboardData() : dataType(DATA_UNKNOWN)
{
}

BlackboardData::BlackboardData(int data) : dataType(DATA_INT), intData(data)
{
}

BlackboardData::BlackboardData(MathLibrary::Vector2 data) : dataType(DATA_VECTOR2), vector2Data(data)
{
}

BlackboardData::BlackboardData(float vector2DataX, float vector2DataY) : dataType(DATA_VECTOR2), vector2Data(MathLibrary::Vector2(vector2DataX, vector2DataY))
{
}
