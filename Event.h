#ifndef EVENT_H
#define EVENT_H

using namespace std;

/*
    Event class

    The Event class tracks a specific event for pushing into the priority
    queue.

    Modifications:
      - Added the static "Null event" property - DTF

   Note:
      - No need for setters in this class

    Author: Logan O'Brien
    Date:   4/11/17
*/
class Event {
private:
   int eventNum;
   int eventValue;
   int time;
   int wireNum;

   // Keeps track of the total number of events in existence
   static int numOfEvents;

public:

   //Constructors
   Event(int eventVal, int timeVal, int wireNumVal);

   //Less-than operator so that the priority que can proplerly sort Even objects:
   friend bool operator<(const Event& firstEvent, const Event& secondEvent);

   //Getter functions
   int getEventNum() const;
   int getEventValue() const;
   int getTime() const;
   int getWireNum() const;

};

#endif // !EVENT_H
