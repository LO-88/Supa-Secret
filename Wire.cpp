#include "Wire.h"

/*
   Modifications:

      - Changed the value of UNDEF to 3 so addition can be used
        for calculations of Gates' outputs - DTF
*/

//Initialize the static variable so that it
//can be used as a sentinal value.
const int Wire::UNDEF = 3;

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

vector<Gate*> Wire::getGates() const
{
   return drives;
}
