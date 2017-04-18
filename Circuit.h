#include <vector>

#ifndef CIRCUIT_H
#define CIRCUIT_H

/*
   Forward declarations:

   The Circuit class uses the Gate, Wire, and Event classes. 

*/
class Gate;
class Wire;
class Event;

/*
   Circuit class

   The circuit class manages all the components of a circuit and handles the processing
   of events.

   Modifications:
      - Added the addGate and addWire functions - DTF
      - Added the getGate and getWire functions - DTF

   Author: Daschel Fortner
   Date:   4/11/17

*/
class Circuit
{

public:

   /*
      Default constructor
   */
   Circuit();

   /*
      This function propogates an event through the circuit. It updates all the components,
      and then generates a new Event list, changing each output for the gates driven by the
      wire targeted by the passed Event.  

      If the Event passed generates no new event, the "null event" is returned.
   */
   //vector<Event*> processEvent(const Event&);

   /*
      Adds a Gate to the circuit.
   */
   void addGate(Gate*);

   /*
      Adds a Wire to the circuit.
   */
   void addWire(Wire*);

   /*
      Adds a Wire to the circuit at the specific index. If necessary, the vector is resized
      to accomodate the new Wire.
   */
   void addWire(Wire*, int);

   /*
      Gets the Gate associated with the passed index.
   */
   Gate* getGate(int) const;

   /*
      Gets the Wire associated with the passed wire number
   */
   Wire* getWire(int) const;

private:

   /*
      Contains all of the Gates that this circuit drives. 
   */
   std::vector<Gate*> gates;

   /*
      Contains all of the wires that comprise this circuit. The first
      index is nullptr, so that the index the gate corresponds to the
      value that is set up by the input files.
   */
   std::vector<Wire*> wires;

};

#endif // !CIRCUIT_H
