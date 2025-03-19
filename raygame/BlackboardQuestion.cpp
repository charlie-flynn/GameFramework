#include "BlackboardQuestion.h"
#include "Actor.h"

BlackboardQuestion::BlackboardQuestion(Actor* asker, EAnswerTypes type) : m_asker(asker), m_type(type)
{
	switch (m_type)
	{
	case UNKNOWN:
		break;
	case INT:
		m_intAnswers = DynamicArray<BlackboardAnswer<int>*>();
		break;
	case VECTOR2:
		m_vector2Answers = DynamicArray<BlackboardAnswer<MathLibrary::Vector2>*>();
		break;
	default:
		break;
	}
}
