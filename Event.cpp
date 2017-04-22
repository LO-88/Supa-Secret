#include "Event.h"

/*
   Keeps track of the number of events
*/
int Event::numOfEvents = 0;

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

Event::Event(int eventVal, int timeVal, int wireNumVal) :
   eventNum(numOfEvents), eventValue(eventVal), time(timeVal), wireNum(wireNumVal)
{
   numOfEvents++;
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