#ifndef sergomor_Subscriber_h
#define sergomor_Subscriber_h

#include "Publisher.h"

namespace sergomor
{

class Subscriber
{
public:
	void subscribe(Publisher *p) { p->subscriberAdd(this); }
	virtual void onState(Publisher *) = 0;
};
}; // namespace sergomor
#endif