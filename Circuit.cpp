#include "Circuit.h"
#include "Event.h"
#include "Wire.h"
#include "Gate.h"


Circuit::Circuit()
{
}

vector<Event*> Circuit::processEvent(const Event& currEvt)
{

   vector<Event*> newEvents;

   // Set the new state of the wires
   wires[currEvt.getWireNum()]->setState(currEvt.getEventValue());

   vector<Gate*> drivenGates = wires[currEvt.getWireNum()]->getGates();

   // Recalculate the output for the gates driven by this wire
   for (auto i = drivenGates.begin(); i != drivenGates.end(); i++)
   {
      Gate* iGate = *i;
      iGate->applyOutput();

      // Make sure the output of the Gate has changed
      if (iGate->isOutputChanging())
      {
         // Create a new event for the change in output
         Event* e = new Event(currEvt.getEventNum() + 1, iGate->calculateOutput(), 
                              currEvt.getTime() + iGate->getDelay(), iGate->getOutput()->getWireNumber());
         // Add the event to the list of generated events
         newEvents.push_back(e);
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
   if (index > wires.size())
   {
      wires.resize(index);
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
