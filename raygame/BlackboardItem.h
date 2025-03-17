#pragma once


enum BlackboardType
{
	UNKNOWN = 0,
	QUESTION,
	DATA
};

class BlackboardItem
{
private:
	BlackboardType m_blackboardType;

	BlackboardItem(BlackboardType type) : m_blackboardType(type) {};
};