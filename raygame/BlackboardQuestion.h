#pragma once
#include "DynamicArray.h"
#include "BlackboardAnswer.h"
#include "BlackboardItem.h"

class Actor;

template <typename T>
class BlackboardQuestion : public BlackboardItem
{
private:
	Actor* m_asker;
	DynamicArray<BlackboardAnswer<T>*> m_answers;

public:
	BlackboardQuestion(Actor* asker);

	Actor* getAsker() { return m_asker; }
	void addAnswer(BlackboardAnswer<T>* answer) { m_answers.Add(answer); }

	Actor* evaluateAnswers();

private:
	virtual bool evaluateAnswer(Actor* answer, Actor* bestAnswer) = 0;
};

template<typename T>
inline BlackboardQuestion<T>::BlackboardQuestion(Actor* asker) : m_asker(asker), BlackboardItem(QUESTION) {}

template<typename T>
inline Actor* BlackboardQuestion<T>::evaluateAnswers()
{
	Actor* bestExpert = nullptr;
	T bestAnswer = T();

	for (BlackboardAnswer<T> answer : m_answers)
	{
		if (evaluateAnswer(answer, bestAnswer))
		{
			bestExpert = answer.owner;
			bestAnswer = answer.value;
		}
	}

	if (bestExpert && bestAnswer)
	{
		return bestExpert;
	}

	return nullptr;
}
