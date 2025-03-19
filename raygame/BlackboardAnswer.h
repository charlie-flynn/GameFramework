#pragma once

class Actor;

template <typename T>
struct BlackboardAnswer
{
public:
	Actor* owner;
	T value;

	[[deprecated("couldnt make questions work, blackboard only stores questions right now")]]
	BlackboardAnswer(Actor* owner, T value);
};

template<typename T>
inline BlackboardAnswer<T>::BlackboardAnswer(Actor* owner, T value) : owner(owner), value(value) {}
