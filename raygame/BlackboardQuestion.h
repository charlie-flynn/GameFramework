#pragma once
#include "DynamicArray.h"

class Actor;

class BlackboardQuestion
{
private:
	Actor* m_asker;
	DynamicArray<Actor*> m_answers;
	const unsigned int m_answersNeeded;

public:
	BlackboardQuestion(Actor* asker, unsigned int answersNeeded = 1);

	Actor* getAsker() { return m_asker; }
	void addAnswer(Actor* answer) { m_answers.Add(answer); }

	Actor* evaluateAnswers();

private:
	virtual int evaluateAnswer(Actor* answer) = 0;
};