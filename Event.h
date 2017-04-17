#ifndef EVENT_H
#define EVENT_H

using namespace std;

/*
    Event class
    
    The Event class tracks a specific event for pushing into the priority
    queue.
    
    Modifications:
      - Added the static "Null event" property - DTF

    Author: Logan O'Brien
    Date:   4/11/17
*/
class Event {
private: 
	int eventNum;
	int eventValue;
	int time;
	int wireNum;
public:

   /*
      "Null Event" property to use when no event is generated from the processing of an event.
   */
   static const Event NULL_EVT;

	//Constructors
	Event(int eventNumVal, int eventVal, int timeVal, int wireNumVal) :
		eventNum(eventNumVal), eventValue(eventVal), time(timeVal), wireNum(wireNumVal) {}

	//Less-than operator so that the priority que can proplerly sort Even objects:
	friend bool operator<(const Event& firstEvent, const Event& secondEvent);

	//Getter functions
	int getEventNum() const;
	int getEventValue() const;
	int getTime() const;
	int getWireNum() const;

	//Setter functions, do we need these?
	void setEventNum(int eventNumVal);
	void setEventValue(int eventVal);
	void setTime(int timeVal);
	void setWireNum(int wireNumVal);
};

#endif // !EVENT_H
