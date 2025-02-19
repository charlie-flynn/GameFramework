#include "Behavior.h"

Behavior::Behavior() : Component(), m_weight(0)
{
}

Behavior::Behavior(float weight)
{
	setWeight(weight);
}

void Behavior::setWeight(float value)
{
	if (value > 1)
		m_weight = 1;
	else if (value < 0)
		m_weight = 0;
	else
		m_weight = value;
}
