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

// Adds data with the given key and value.
bool Blackboard::addData(char* key, BlackboardData* value)
{
    unsigned int hash = Hash((unsigned char*)key);
    return m_data.insert(std::pair<unsigned int, BlackboardData*>(hash, value)).second;
}

// Removes a single data with the same key.
bool Blackboard::removeData(char* key)
{
    unsigned int hash = Hash((unsigned char*)key);
    return m_data.erase(hash);
}

// Returns the data with the given key, or nullptr if it's not found.
BlackboardData* Blackboard::getData(char* key)
{
    unsigned int hash = Hash((unsigned char*)key);
    if (m_data.find(hash) == m_data.end())
        return nullptr;
    return (*m_data.find(hash)).second;
}

