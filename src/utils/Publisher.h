#ifndef sergomor_Publisher_h
#define sergomor_Publisher_h

#include "Stateable.h"

namespace sergomor
{

class Subscriber;

class Publisher : public Stateable
{
public:
	virtual void stateSet(state_t s);
	void subscriberAdd(Subscriber *s);
	~Publisher() { delete next; }

private:
	Subscriber *subscriber = nullptr;
	Publisher *next = nullptr;
};
}; // namespace sergomor
#endif