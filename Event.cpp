#include "Event.h"

/*
   The "Null Event": used to determine when no event has occured.
*/
const Event Event::NULL_EVT(-1, -1, -1, -1);

bool operator<(const Event & firstEvent, const Event & secondEvent)
{
	//Check to see if the primary sort is ineffective. If
	//it is, use the event number as the secondary sort.
	if (firstEvent.time == secondEvent.time) {
		return firstEvent.eventNum < secondEvent.eventNum;
	}
	else return firstEvent.time < secondEvent.time;
}

int Event::getEventNum() const
{
	return eventNum;
}

int Event::getEventValue() const
{
	return eventValue;
}

int Event::getTime() const
{
	return time;
}

int Event::getWireNum() const
{
	return wireNum;
}

void Event::setEventNum(int eventNumVal)
{
	eventNum = eventNumVal;
}

void Event::setEventValue(int eventVal)
{
	eventValue = eventVal;
}

void Event::setTime(int timeVal)
{
	time = timeVal;
}

void Event::setWireNum(int wireNumVal)
{
	wireNum = wireNumVal;
}


