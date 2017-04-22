#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>

#include "Circuit.h"
#include "Wire.h"
#include "Gate.h"
#include "Event.h"

using namespace std;

/*
    Apparently he's fine with us leaking memory all over the place.
*/
/*
   Dr Shomper told me he wants this done by tomorrow night
*/
void parseCircuit(ifstream& in, Circuit& c)
{
	string inputString;
	int inputNumber;

	//skip first line of circuit file:
	in >> inputString;
	in >> inputString;

   // Do it this way so we know when we're done.
   while (in >> inputString)
   {

	   if (inputString == "INPUT" || inputString == "OUTPUT") {
		   //Skip the letter. We don't need it do we?
         // We do. It's the name of the wire
         string name;
         int    wireNum;

         in >> name;
         in >> wireNum;
	   //} This one isn't necessary unless we differentiate between Input/Output wires
      //  in the circuit class. (Might be a good idea)
	   //else if (inputString == "OUTPUT") {

         c.addWire(new Wire(name, wireNum), wireNum);

	   }
	   //else it is a gate
	   else {
		   //Either use if-else statements to determine which type of gate it is and then convert to enum,
		   //or use a switch statement based off of the first character of the gate. For the case that is 'N', 
		   //then use if-else statements to determine which one of the gates that begin with an "N" it is.

         // First reading in is the gate type, don't read in a new one

         string type(inputString);

         string delayWithNS;
         int    delay, inputA, inputB;
         int    output;

         in >> delayWithNS;
         delay = stoi(delayWithNS);

         in >> inputA;
         in >> inputB;
         in >> output;


         /*
            TODO

            We need to check for NOT gates
         */

         /*
            Check for internal wires

            I don't know if this will work, but I think it might.
         */
         if (c.getWire(inputA) == nullptr)
         {
            c.addWire(new Wire("INT", inputA), inputA);
         }

         if (c.getWire(inputB) == nullptr)
         {
            c.addWire(new Wire("INT", inputB), inputB);
         }

         if (c.getWire(output) == nullptr)
         {
            c.addWire(new Wire("INT", output), output);
         }

         c.addGate(new Gate(c.getWire(inputA), c.getWire(inputB), c.getWire(output), Gate::gateTypeFactory.at(type), delay));

	   }
   }

}

void parseVector(ifstream& in, priority_queue<Event>& eventContainer, const Circuit& c)
{
   // Read in the first two tokens of the file
   string next;

   in >> next;
   in >> next;

   // Begin the file-reading loop
   while (in >> next)
   {
      // Right now next should equal either INPUT or OUTPUT
      // We have read the first token of an Event definition
      // For the initial parsing, the event number will just be the size of the
      // queue (0, 1, 2, etc)
      int eventNumber = eventContainer.size();

      // Get all the data tokens
      string wireName;
      int    time;
      short  value;

      in >> wireName;
      in >> time;
      in >> value;

      // Convert the Name to a number
      Wire* w = c.getWire(wireName);
      int   wireNum;

      // Skip wires that don't exist
      if (w == nullptr)
      {
         continue;
      }
      else
      {
         wireNum = w->getWireNumber();
      }

      // Put the new event on the queue
      eventContainer.push(Event(eventNumber, value, time, wireNum));
   }
}

void runSimulation(Circuit& c, priority_queue <Event> e)
{
	bool isDuplicate = false;
	//while event que isn't empty
	while (!e.empty()) {
		//remove top event and proccess event. Than function returns a vector of events.
		Event current = e.top();
		e.pop();
		vector <Event> newEvents = c.processEvent(current);//								Does this assignment work? We didn't write an assignment
		//																					operator in the Event class. Does it still work?
		//Check if the wire in each event is already scheduled to change before this time.
		for (auto i = newEvents.begin(); i != newEvents.end(); i++) {

			//Make a copy of the que so that I can loop through it.
			priority_queue <Event> copy = e;
			//Determine which wire is scheduled to change.
			//loop through the que searching for an Event with the same wire number while newEvents[i] < the current event from the que.
			while (newEvents[i] < copy.top() | copy.empty() != true) {						//I'm not sure why I can't access elements of the vector like this.
				//Check if the Events are scheduled to change the same wire
				if (newEvents[i].getWireNum() == (copy.top()).getWireNum()) {
					//Check if they have the same value
					if (newEvents[i].getEventValuen() == copy.top().getEventValue()) {
						isDuplicate = true;
					}
					//If the two events have different values than it is not a duplicate.
					else {
						isDuplicate = false;
					}
				}
				//Remove that object from the copy que
				copy.pop();
			}
			//If the event isn't a duplicate add it to the que, 
			//if it is, than ignore it.
			if (isDuplicate == false) {
				e.push(newEvents[i]);
			}

			//Is it better to loop in reverse searching backwards? 
			//than I could see if it reaches an equivalent event or a contradictory event first.
			//It is organized smallest time to largest. 
		}
	}
}

void generateOutput(const Circuit& c)
{

}

int main()
{
   
   priority_queue<Event> events;

   Circuit c;

   // Create the file streams
   ifstream circuitInput("Supa-Secret/circuit0.txt");
   ifstream vectorInput("Supa-Secret/circuit0_vector.txt");

   // Parse the circuit file
   parseCircuit(circuitInput, c);

   // Parse the vector file
   parseVector(vectorInput, events, c);

   //Run the simulation
   runSimulation(c, events);

   return 0;
}
