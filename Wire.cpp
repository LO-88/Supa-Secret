#include "Wire.h"
//Initialize the static variable so that it
//can be used as a sentinal value.
const int Wire::UNDEF = -1;

void Wire::addGate(Gate * gate)
{
	drives.push_back(gate);
}

void Wire::setName(string nameVal)
{
	name = nameVal;
}

void Wire::setState(short stateVal)
{
	state = stateVal;
}

string Wire::getName() const
{
	return name;
}

short Wire::getState() const
{
	return state;
}
