#include "Blackboard.h"
#include <string>



// Hashes the given character pointer using ELF hash.
unsigned int Hash(unsigned char* value)
{
    int length = ((std::string)(char*)value).length();
    unsigned int hash = 0, x = 0;
    for (int i = 0; i < length; i++)
    {
        hash = (hash << 4) + value[i];
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return (hash & 0x7FFFFFFF);
}

Blackboard::Blackboard()
{
}

Blackboard::Blackboard(Actor* owner)
{
}

Blackboard::Blackboard(Scene* owner)
{
}

void Blackboard::addData(char* key, BlackboardData* value)
{
    unsigned int hash = Hash((unsigned char*)key);
    m_data.insert(std::pair<unsigned int, BlackboardData*>(hash, value));
}

bool Blackboard::removeData(char* key)
{
    unsigned int hash = Hash((unsigned char*)key);
    return m_data.erase(hash);
}

BlackboardData* Blackboard::getData(char* key)
{
    unsigned int hash = Hash((unsigned char*)key);
    return m_data[hash];
}
