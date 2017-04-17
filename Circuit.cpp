#include "Circuit.h"
#include "Event.h"


Circuit::Circuit()
{
}

Event Circuit::processEvent(const Event& currentEvent)
{
   Event e = Event::NULL_EVT;


   return e;
}

void Circuit::addGate(Gate* newGate)
{
   gates.push_back(newGate);
}

void Circuit::addWire(Wire* newWire)
{
   wires.push_back(newWire);
}
