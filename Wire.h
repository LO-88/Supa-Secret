#ifndef WIRE_H
#define WIRE_H
#include <vector>
#include <string>

using namespace std;

class Gate;

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
	void addGate(Gate*);
	void setName(string nameVal);
	void setState(short stateVal);

	//Getter functions:
	string getName() const;
	short getState() const;
	//getters and setters for the vectors?

	//Destructor??
};




#endif //WIRE_H