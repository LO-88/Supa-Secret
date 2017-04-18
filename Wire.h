#ifndef WIRE_H
#define WIRE_H
#include <vector>
#include <string>

using namespace std;

class Gate;

/*
    Wire class

    The Wire class contains the state and name of a specific Wire.
    It is used to propogate a value through the circuit.

    Modifications:
      - Corrected type of history from char to short - DTF
      - Added getGates() function for use in the Circuit class - DTF
      - Added wireNum property for ease of calculation in Circuit - DTF
      - Added the mapHistory() function - DTF

    Author: Logan O'Brien
    Date:   4/11/17
*/
class Wire {
private:
   string name;
   short state;
   short wireNum;
   vector <Gate*> drives;
   vector <short> history;
public:
   //Define a constant for the undefined value for wire objects
   const static int UNDEF;

   //Constructors:
   Wire(string nameVal, short num) : name(nameVal), wireNum(num), state(UNDEF) {}

   /*
      Adds the value of the passed state parameter to the history vector. If the time
      passed exceeds the length of the vector, the current state of the wire is added
      to the history until the time of reached, and then the new state is added.
   */
   void mapHistory(int time, short state);

   //Setter functions:
   void addGate(Gate* gate);
   void setName(string nameVal);
   void setState(short stateVal);
   void setWireNumber(short num);

   //Getter functions:
   string getName() const;
   short getState() const;
   short getWireNumber() const;

   //getters and setters for the vectors
   vector<Gate*> getGates() const;

   //Destructor??
};




#endif //WIRE_H
