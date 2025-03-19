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

	// returns false if type does not match up with stored type
	bool addAnswer(BlackboardAnswer<int>* answer) { return m_type == INT ? m_intAnswers.Add(answer), true : false; }
	bool addAnswer(BlackboardAnswer<MathLibrary::Vector2>* answer) { return m_type == VECTOR2 ? m_vector2Answers.Add(answer), true : false; }

	// this solution objectively sucks but it's the least hard-codey hard-coding i can do
	BlackboardAnswer<int>* evaluateIntAnswers();
	BlackboardAnswer<MathLibrary::Vector2>* evaluateVector2Answers();
	

private:
	virtual bool compareIntAnswers(BlackboardAnswer<int>* answer, BlackboardAnswer<int>* bestAnswer) {};
	virtual bool compareVector2Answers(BlackboardAnswer<MathLibrary::Vector2>* answer, BlackboardAnswer<MathLibrary::Vector2>* bestAnswer) {};
};

