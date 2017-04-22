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
