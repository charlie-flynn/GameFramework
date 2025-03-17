#include "BlackboardQuestion.h"

BlackboardQuestion::BlackboardQuestion(Actor* asker, unsigned int answersNeeded) : m_asker(asker), m_answersNeeded(answersNeeded)
{
}

Actor* BlackboardQuestion::evaluateAnswers()
{
    return nullptr;
}
