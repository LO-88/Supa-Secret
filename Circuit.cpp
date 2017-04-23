#include "Circuit.h"
#include "Event.h"
#include "Wire.h"
#include "Gate.h"


Circuit::Circuit()
{
   // Add the null element so that the wire numbers correspond to the index.
   wires.push_back(nullptr);
}

vector<Event> Circuit::processEvent(const Event& currEvt)
{

   vector<Event> newEvents;

   // Get the Wire referenced by the passed Event
   Wire* eventWire = wires[currEvt.getWireNum()];

   // Set the new state of the wires
   eventWire->setState(currEvt.getEventValue());
   eventWire->addHistory(currEvt.getTime(), currEvt.getEventValue());

   vector<Gate*> drivenGates = eventWire->getGates();

   // Recalculate the output for the gates driven by this wire
   for (auto i = drivenGates.begin(); i != drivenGates.end(); i++)
   {
      Gate* iGate = *i;

      // Make sure the output of the Gate has changed
      if (iGate->isOutputChanging())
      {
         // Change the output of the Gate
         iGate->applyOutput();
        
         // Add the event to the list of generated events
         newEvents.push_back(Event(iGate->calculateOutput(), currEvt.getTime() + iGate->getDelay(),
                                   iGate->getOutput()->getWireNumber()));
      }
   }

   return newEvents;
}

void Circuit::addGate(Gate* newGate)
{
   gates.push_back(newGate);
}

void Circuit::addWire(Wire* newWire)
{
   wires.push_back(newWire);
}

void Circuit::addWire(Wire* newWire, int index)
{
   if (index >= wires.size())
   {
      wires.resize(index + 1);
   }

   wires[index] = newWire;
}

Gate* Circuit::getGate(int index) const
{
   return gates[index];
}

Wire* Circuit::getWire(int wireNumber) const
{
   return wires[wireNumber];
}

Wire* Circuit::getWire(string name) const
{
   for (int i = 1; i < wires.size(); i++)
   {
      if (wires[i]->getName() == name)
      {
         return wires[i];
      }
   }

   return nullptr;
}

string Circuit::generateWireTrace(int simLen) const
{
	string trace;
	int length;
	for (auto i = ++wires.begin(); i != wires.end(); i++) {
		Wire* currWire = *i;
		//Ensure that the wire is not an internal one
		if (currWire->getName() != "INT") {

			// Add the name of the wire to the trace
			string name = currWire->getName() + " ";
			string data;
			
			// Make sure there is history for this Wire. If there is not, make it
			// undefined for the duration of the simulation.
			if (currWire->getNumHistoryItems() == 0) {
				data = string(simLen, 'X');
				trace += name + data;
				continue;
			}

			// Create the part of the string from the undefined portion
			// to the first event
			length = currWire->getHistory(0).second;
			data = string(length, 'X');

			// Go through each history item and add its value to the trace
			for (int i = 1; i < currWire->getNumHistoryItems(); i++) {
				int traceLen = currWire->getHistory(i).second - currWire->getHistory(i - 1).second;
				data += string(traceLen, currWire->getHistory(i - 1).first);
			}

			//Add the remainder of the wire trace to the data variable
			length = simLen - data.length() + 1;
			int index = currWire->getNumHistoryItems() - 1;
			data += string(length, currWire->getHistory(index).first);

			//Construct the trace of the wire
			trace += name + data + "\n";
		}
	}

	return trace;
}
