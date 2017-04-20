#include "Event.h"

bool operator<(const Event & firstEvent, const Event & secondEvent)
{
   //Check to see if the primary sort is ineffective. If
   //it is, use the event number as the secondary sort.
   // We have to use greater than here to change the behavior of the priority queue.
   if (firstEvent.time == secondEvent.time) {
      return firstEvent.eventNum > secondEvent.eventNum;
   }
   else return firstEvent.time > secondEvent.time;
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


