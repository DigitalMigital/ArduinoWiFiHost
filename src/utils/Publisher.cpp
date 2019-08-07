#include "Publisher.h"
#include "Subscriber.h"

namespace sergomor
{

void Publisher::subscriberAdd(Subscriber *s)
{
	if (subscriber == nullptr)
		subscriber = s;
	else
	{
		next = new Publisher;
		next->subscriberAdd(s);
	}
}

void Publisher::stateSet(state_t s)
{
	Stateable::stateSet(s);
	if (subscriber != nullptr)
		subscriber->onState(this);
	Publisher *p = next;
	while (p != nullptr)
	{
		p->subscriber->onState(this);
		p = p->next;
	}
}

} // namespace sergomor