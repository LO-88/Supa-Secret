#include "Circuit.h"
#include "Event.h"
#include "Wire.h"
#include "Gate.h"


Circuit::Circuit()
{
}

vector<Event*> Circuit::processEvent(const Event& currentEvent)
{

   vector<Event*> newEvents;

   // Set the new state of the wires
   wires[currentEvent.getWireNum()]->setState(currentEvent.getEventValue());

   vector<Gate*> drivenGates = wires[currentEvent.getWireNum()]->getGates();

   // Recalculate the output for the gates driven by this wire
   for (auto i = drivenGates.begin(); i != drivenGates.end(); i++)
   {
      
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
