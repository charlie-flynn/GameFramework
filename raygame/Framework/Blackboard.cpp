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

Blackboard::Blackboard() : m_ownerIsScene(false), m_sceneOwner(nullptr)
{
}

Blackboard::Blackboard(Actor* owner) : m_ownerIsScene(false), m_actorOwner(owner)
{
}

Blackboard::Blackboard(Scene* owner) : m_ownerIsScene(true), m_sceneOwner(owner)
{
}

int Blackboard::addData(char* key, BlackboardData* value)
{
    unsigned int hash = Hash((unsigned char*)key);
    int offset = 0;

    while (!m_data.insert(std::pair<unsigned int, BlackboardData*>(hash + offset, value)).second)
    {
        offset++;
    }
    
    value->key = hash;

    return offset;
}

bool Blackboard::removeData(char* key, int offset)
{
    unsigned int hash = Hash((unsigned char*)key);
    return m_data.erase(hash + offset);
}

int Blackboard::removeAllData(char* key)
{
    int count = 0;
    unsigned int hash = Hash((unsigned char*)key);

    for (auto iter = m_data.begin(); iter != m_data.end(); iter++)
    {
        if ((*iter).second->key == hash)
        {
            count++;
            m_data.erase(iter);
        }
    }

    return count;
}

BlackboardData* Blackboard::getData(char* key)
{
    unsigned int hash = Hash((unsigned char*)key);

    for (auto iter = m_data.begin(); iter != m_data.end(); iter++)
    {
        if ((*iter).second->key == hash)
        {
            return (*iter).second;
        }
    }

    return nullptr;
}

BlackboardData* Blackboard::getData(char* key, int offset)
{
    unsigned int hash = Hash((unsigned char*)key);
    
    if (m_data.find(hash + offset) == m_data.end())
        return nullptr;

    return (*(m_data.find(hash))).second;
}
