#pragma once

class Actor;

template <typename T>
struct BlackboardAnswer
{
public:
	Actor* owner;
	T value;

	BlackboardAnswer(Actor* owner, T value);
};

template<typename T>
inline BlackboardAnswer<T>::BlackboardAnswer(Actor* owner, T value) : owner(owner), value(value) {}
