#include "Wire.h"

/*
   Modifications:

      - Changed the value of UNDEF to 3 so addition can be used
        for calculations of Gates' outputs - DTF

		Questions:
		1. UNDEF value?
		2. mapHistory()?
		
		TODO:
		Change the getDrives() function to get based on an index
*/

//Initialize the static variable so that it
//can be used as a sentinal value.
const int Wire::UNDEF = 3;

void Wire::mapHistory(int time, short state)
{
   int   prevStateIndex = history.size() - 1;
   short prevState      = history[prevStateIndex];
     
   for (int i = 0; i < (time - prevStateIndex); i++)
   {
      history.push_back(prevState);
   }

   history.push_back(state);
}

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

void Wire::setWireNumber(short num)
{
   wireNum = num;
}

string Wire::getName() const
{
   return name;
}

short Wire::getState() const
{
   return state;
}

short Wire::getWireNumber() const
{
   return wireNum;
}

vector<Gate*> Wire::getGates() const
{
   return drives;
}
