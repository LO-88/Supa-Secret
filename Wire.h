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
    
    Author: Logan O'Brien
    Date:   4/11/17
*/
class Wire {
private:
	string name;
	short state;
	vector <Gate*> drives;
	vector <char> history;
public:
	//Define a constant for the undefined value for wire objects
	const static int UNDEF;
	
	//Constructors:
	Wire(string nameVal) : name(nameVal), state(UNDEF) {}

	//Setter functions:
	void addGate(Gate* gate);
	void setName(string nameVal);
	void setState(short stateVal);

	//Getter functions:
	string getName() const;
	short getState() const;
	//getters and setters for the vectors?

	//Destructor??
};




#endif //WIRE_H
