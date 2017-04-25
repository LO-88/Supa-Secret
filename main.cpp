#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

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
         int    delay, wireOne, wireTwo;

         in >> delayWithNS;
         delay = stoi(delayWithNS);

         in >> wireOne;
         in >> wireTwo;

         /*
            Check for the existence of the two input wires. If they don't 
            already exist, they are internal wires, so they need to be 
            added still.
         */
         if (c.getNumWires() <= wireOne || c.getWire(wireOne) == nullptr)
         {
            c.addWire(new Wire("INT", wireOne), wireOne);
         }

         if (c.getNumWires() <= wireTwo || c.getWire(wireTwo) == nullptr)
         {
            c.addWire(new Wire("INT", wireTwo), wireTwo);
         }

         /*
            If the type is a NOT gate, there are only two wires to 
            be read in.
         */
         if (type == "NOT")
         {
            c.addGate(new Gate(c.getWire(wireOne), c.getWire(wireTwo), delay));
            continue;
         }

         int   output;
         in >> output;

         /*
            TODO

            We need to check for NOT gates
         */

         /*
            Check whether the output wire exists, and add it if it doesn't.
         */

         if (c.getNumWires() <= output || c.getWire(output) == nullptr)
         {
            c.addWire(new Wire("INT", output), output);
         }

         c.addGate(new Gate(c.getWire(wireOne), c.getWire(wireTwo), c.getWire(output), Gate::gateTypeFactory.at(type), delay));

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
      string wireName, valueString;
      int    time;
      short  value;

      in >> wireName;
      in >> time;
      in >> valueString;

      // Check for undefined values
      if (valueString == "X")
      {
         value = 3;
      }
      else
      {
         value = stoi(valueString);
      }

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
      eventContainer.push(Event(value, time, wireNum));
   }
}

int runSimulation(Circuit& c, priority_queue <Event>& e)
{
	bool isDuplicate = false;
   int  runTime = 0;
	//while event que isn't empty
	while (!e.empty() && (runTime < 60 || e.top().getTime() == 60)) {
		//remove top event and proccess event. Than function returns a vector of events.
		Event current = e.top();
      runTime = current.getTime();
		e.pop();
      
		vector <Event> newEvents = c.processEvent(current);//								Does this assignment work? We didn't write an assignment
		//																					operator in the Event class. Does it still work?
		//Check if the wire in each event is already scheduled to change before this time.
		for (auto i = newEvents.begin(); i != newEvents.end(); i++) {

			//Make a copy of the que so that I can loop through it.
			priority_queue <Event> copy = e;
			bool isDuplicate = false;
			//Determine which wire is scheduled to change.
			//loop through the que searching for an Event with the same wire number while newEvents[i] < the current event from the que.
			while (!copy.empty() && i->getTime() >= copy.top().getTime()) {						//I'm not sure why I can't access elements of the vector like this.
				//Check if the Events are scheduled to change the same wire
				if (i->getWireNum() == copy.top().getWireNum()) {
					//Check if they have the same value
					if (i->getEventValue() == copy.top().getEventValue()) {
						isDuplicate = true;
                  break;
					}
				}

				//Remove that object from the copy que
				copy.pop();
			}

			//If the event isn't a duplicate add it to the que, 
			//if it is, than ignore it.
			if (!isDuplicate) {
				e.push(*i);
			}

			//Is it better to loop in reverse searching backwards? 
			//than I could see if it reaches an equivalent event or a contradictory event first.
			//It is organized smallest time to largest
		}

	}

   return runTime;
}

void generateOutput(const Circuit& c, int time)
{
	string output = c.generateWireTrace(time);

	//Print the wire trace
   cout << output;
}

int main()
{
   
   priority_queue<Event> events;
   Circuit c;
   string input;
   string secondTry;

   //Recieve the file locations from the user
   cout << "Please enter the name of the circuit input file.\n";
   cin >> input;

   // Create the file streams
   ifstream circuitInput(input + ".txt");
   ifstream vectorInput(input + "_v.txt");

   //Check if the files opened correctly
   if (!circuitInput.is_open()) {
	   cerr << "Error: the specified circuit file could not be opened.\n";
	   cerr << "The file: " << input << ".txt could not be opened.\n";
	   return 1;
   }

   if (!vectorInput.is_open())
   {
	   cerr << "Error: the specified vector file, " << input
		   << ".txt, could not be opened.\n";
	   cerr << "Please enter the name of the vector file\n";
	   cin >> secondTry;

	   //Attempt to open the file again
	   ifstream vectorInput(secondTry + "_v.txt");

	   if (!vectorInput.is_open()) {
		   cerr << "Error: the specified circuit file could not be opened.\n";
		   cerr << "The file: " << input << ".txt could not be opened.\n";
		   return 2;
	   }
   }

   // Parse the circuit file
   parseCircuit(circuitInput, c);

   // Parse the vector file
   parseVector(vectorInput, events, c);

   //Run the simulation
   int time = runSimulation(c, events);

   //Print the wire trace
   generateOutput(c, time);

   getline(cin, string());

   return 0;
}
