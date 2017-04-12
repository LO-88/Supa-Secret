#ifndef GATE_H
#define GATE_H

/*
   Forward declaration:

   The Gate class uses the Wire class.
*/
class Wire;

/*
   Gate class

   This class simulates Gate logic. It contains the necessary functions for
   gate calculation as well as an enumeration for the Gate Type. 

   Author: Daschel Fortner
   Date:   4/11/17

*/
class Gate
{

public:

   /*
      GateType

      The GateType enum is used to define the type of Gate. Use this Enum
      to define which type of gate, such as NOT, AND, OR, etc.

   */
   enum GateType
   {
      NOT,
      AND, 
      OR,
      XOR,
      NAND,
      NOR,
      XNOR
   };

   /*
      Constructs a new gate with the given inputs and outputs, of the specified GateType.
      The delay is set to the passed value.
   */
   Gate(Wire*, Wire*, Wire*, GateType, short);

   /*
      Calculates whether this Gate should trigger an event. This function is used by the 
      Circuit class's processEvent() function to determine whether the change in inputs 
      should generate an output. This is done so the Circuit class can easily track changes
      and generate a new event without actually changing the data of the wires.
   */
   bool isOutputChanging();

   /*
      Performs the necessary logical operations on the input wires and changes the state 
      of the output wire to reflect the new output.
   */
   void generateOutput();

   // Getters
   // Wires
   Wire* getFirstInput()  const;
   Wire* getSecondInput() const;
   Wire* getOutput()      const;

   // GateType
   GateType getType() const;

   // Delay
   short getDelay() const;

   // Setters
   // Wires
   void setFirstInput(Wire*);
   void setSecondInput(Wire*);
   void setOutput(Wire*);

   // GateType
   void setType(GateType);

   // Delay
   void setDelay(short);

   ~Gate();

private:

   // The inputs and outputs for the Gate
   Wire*    firstInput;
   Wire*    secondInput;
   Wire*    output;

   // The type of Gate (NOT, AND, etc)
   GateType type;

   // The delay for this gate in nanoseconds
   short    delay;

};

#endif