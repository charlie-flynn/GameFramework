#pragma once
#include "DynamicArray.h"
#include "BlackboardAnswer.h"
#include "BlackboardItem.h"
#include "Vector2.h"

#include <iostream>

class Actor;

enum EAnswerTypes
{
	ANSWER_UNKNOWN = 0,
	INT,
	VECTOR2
};

class BlackboardQuestion
{
private:
	Actor* m_asker;
	EAnswerTypes m_type;
	union
	{
		DynamicArray<BlackboardAnswer<int>*> m_intAnswers;
		DynamicArray<BlackboardAnswer<MathLibrary::Vector2>*> m_vector2Answers;
	};

public:
	BlackboardQuestion(Actor* asker, EAnswerTypes type);

	Actor* getAsker() { return m_asker; }
	EAnswerTypes getType() { return m_type; }

	// returns false if type does not match up with stored type
	bool addAnswer(BlackboardAnswer<int>* answer) { return m_type == INT ? m_intAnswers.Add(answer), true : false; }
	bool addAnswer(BlackboardAnswer<MathLibrary::Vector2>* answer) { return m_type == VECTOR2 ? m_vector2Answers.Add(answer), true : false; }

	// this solution objectively sucks but it's the least hard-codey hard-coding i can do
	// makes it kinda easy to call the function anyways
	template <typename T>
	BlackboardAnswer<T>* evaluateAnswers();
	template <>
	BlackboardAnswer<int>* evaluateAnswers();
	BlackboardAnswer<MathLibrary::Vector2>* evaluateAnswers();


private:
	virtual bool compareIntAnswers(BlackboardAnswer<int>* answer, BlackboardAnswer<int>* bestAnswer) { return false; };
	virtual bool compareVector2Answers(BlackboardAnswer<MathLibrary::Vector2>* answer, BlackboardAnswer<MathLibrary::Vector2>* bestAnswer) { return false; };
};

template<typename T>
inline BlackboardAnswer<T>* BlackboardQuestion::evaluateAnswers()
{
	return nullptr;
}

template<>
inline BlackboardAnswer<int>* BlackboardQuestion::evaluateAnswers()
{
	BlackboardAnswer<int>* bestAnswer;

	for (int i = 0; i < m_intAnswers.Length(); i++)
	{
		bestAnswer = compareIntAnswers(m_intAnswers[i], bestAnswer) ? m_intAnswers[i] : bestAnswer;
	}

	if (bestAnswer)
		bestAnswer->owner->onAnswerSuccess(m_asker);

	return bestAnswer;
}

inline BlackboardAnswer<MathLibrary::Vector2>* BlackboardQuestion::evaluateAnswers()
{
	BlackboardAnswer<MathLibrary::Vector2>* bestAnswer;

	for (int i = 0; i < m_vector2Answers.Length(); i++)
	{
		bestAnswer = compareVector2Answers(m_vector2Answers[i], bestAnswer) ? m_vector2Answers[i] : bestAnswer;
	}

	if (bestAnswer)
		bestAnswer->owner->onAnswerSuccess(m_asker);

	return bestAnswer;
}
