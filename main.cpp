#include <iostream>
#include <istream>
#include <queue>
#include <string>

#include "Circuit.h"

using namespace std;

void parseCircuit(ifstream& in, const Circuit& c)
{
	string inputString;
	int inputNumber;

	//skip first line of circuit file:
	cin >> inputString;
	cin >> inputString;

	//Check if there is another line??? If there is:
	cin >> inputString;

	if (inputString == "INPUT") {
		//Skip the letter. We don't need it do we?

	}
	else if (inputString == "OUTPUT") {

	}
	//else it is a gate
	else {
		//Either use if-else statements to determine which type of gate it is and then convert to enum,
		//or use a switch statement based off of the first character of the gate. For the case that is 'N', 
		//then use if-else statements to determine which one of the gates that begin with an "N" it is.
	}
}

void parseVector(ifstream& in, const priority_queue<Event*>& eventContainer)
{

}

void runSimulation(const Circuit& c)
{

}

void generateOutput(const Circuit& c)
{

}

int main()
{

   

   return 0;
}