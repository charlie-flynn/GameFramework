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

BlackboardAnswer<int>* BlackboardQuestion::evaluateIntAnswers()
{
	BlackboardAnswer<int>* bestAnswer = nullptr;

	for (int i = 0; i < m_intAnswers.Length(); i++)
	{
		// compare all the answers and set bestAnswer to the best of them
		bestAnswer = compareIntAnswers(m_intAnswers[i], bestAnswer) ? m_intAnswers[i] : bestAnswer;
	}

	// if there was a bestAnswer, call the answerer's onAnswerSuccess function
	if (bestAnswer)
		bestAnswer->owner->onAnswerSuccess(m_asker);
	
	return bestAnswer;
}

BlackboardAnswer<MathLibrary::Vector2>* BlackboardQuestion::evaluateVector2Answers()
{
	BlackboardAnswer<MathLibrary::Vector2>* bestAnswer = nullptr;

	for (int i = 0; i < m_vector2Answers.Length(); i++)
	{
		// compare all the answers and set bestAnswer to the best of them
		bestAnswer = compareVector2Answers(m_vector2Answers[i], bestAnswer) ? m_vector2Answers[i] : bestAnswer;
	}

	// if there was a bestAnswer, call the answerer's onAnswerSuccess function
	if (bestAnswer)
		bestAnswer->owner->onAnswerSuccess(m_asker);

	return bestAnswer;
}


/*
switch (m_type)
{
case UNKNOWN:
	return nullptr;
	break;
case INT:
	for (int i = 0; i < m_intAnswers.Length(); i++)
	{
		bestAnswer = evaluateIntAnswer(m_intAnswers[i], bestAnswer) ? m_intAnswers[i] : bestAnswer;
	}
	break;
case VECTOR2:
	for (int i = 0; i < m_vector2Answers.Length(); i++)
	{
		bestAnswer = evaluateIntAnswer(m_vector2Answers[i], bestAnswer) ? m_vector2Answers[i] : bestAnswer;
	}
	break;
default:
	return nullptr;
	break;
}
	*/
