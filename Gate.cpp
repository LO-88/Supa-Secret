#include "Gate.h"
#include "Wire.h"

/*
   Map each string value to its corresponding GateType so that the parsing of 
   the file can be greatly simplified.
*/
const map<string, Gate::GateType> Gate::gateTypeFactory =
{
   { "AND" , Gate::AND  },
   { "OR"  , Gate::OR   },
   { "XOR" , Gate::XOR  },
   { "NOT" , Gate::NOT  },
   { "NAND", Gate::NAND },
   { "NOR" , Gate::NOR  },
   { "XNOR", Gate::XNOR }
};

Gate::Gate(Wire* inputA, Wire* inputB, Wire* out, GateType t, short d)
{
   firstInput  = inputA;
   secondInput = inputB;
   output      = out;
   type        = t;
   delay       = d;

   firstInput->addGate(this);
   secondInput->addGate(this);
}

/*
   Determines whether the current state of the wires even changes the output for 
   this gate. This function evaluates to true if the current state of this Gate's
   output wire is different from the calculation of its output, and false if they
   are the same.
*/
bool Gate::isOutputChanging()
{
   return calculateOutput() != output->getState();
}

/*
   Calculates the value that should be on this Gate's output wire. This function
   returns 0 if the output of this gate should be false, 1 if it should be true
   and Wire::UNDEF (3) if the value is undefined.
*/
short Gate::calculateOutput()
{

   short a   = firstInput->getState();
   short b   = secondInput->getState();
   short sum = a + b;
   short output;

   switch (type)
   {

      // Set the value of the logical operation for the BASE of the Gate.
      //
      case NOT:

         // Only perform the operation on the first wire since it's a one input
         // gate.
         if (a == Wire::UNDEF)
         {
             return Wire::UNDEF;
         }
         
         // Set the output to be the value of a, and get it ready to be notted
         output = a;

         break;

      // For both AND and NAND gates, set the logical output to be an AND. Later, this 
      // function will NOT all the negated gates.
      case AND:
      case NAND:

         // If the sum has exceeded 3, one of the values is not zero and the other is undefined, 
         // or they are both undefined. In either case, we want to return UNDEF.
         if (sum > 3)
         {
            return Wire::UNDEF;
         }
         
         // This operation holds even if one of the values is undefined, because 0 & 3 is still
         // zero.
         output = a & b;

         break;

      // Perform the operation for either OR or NOR gates
      case OR:
      case NOR:

         // If the sum is 3, one of the wires is UNDEF and the other is 0. This is an UNDEF case
         if (sum == 3)
         {
            return Wire::UNDEF;
         }
         
         /*
            This output has to be adjusted in case we get an UNDEF (11) and a 1. If we perform a 
            bitwise OR on 11 (3) and 1, we will get back 11. To correct this, we need to kill the 
            leftmost bit, which can be acheived by performing a bitwise AND with 01. Thus, 11 | 1 
            yields 11, but 11 & 01 yields 1, which is what we want. The case where this fails is 
            when an UNDEF is ORRED with a 0. UNDEF, 11, OR 0 is 11, which is 1 when ANDED with 01. 
            However, this case has already been handled above so it doesn't need to be considered
            here.
         */
         output = (a | b) & 1;

         break;

     case XOR:
     case XNOR:

        // If the sum is greater than 2, there is an undefined value which is undefined for XOR/XNOR
        if (sum > 2)
        {
           return Wire::UNDEF;
        }

        // This expression evaluates to 1 if a is different from b, and 0 if a is equivalent to b.
        output = (int)(a != b);

        break;

   }

   // All of the negated Gates are defined after the second index, so making this comparison checks if 
   // the Gate is negated logic.
   if (type > 2)
   {
      // Perform an XOR operation on the output value. By this point output is equal to either 0 or 1.
      // Performing an XOR with 1 causes switches it to 0 if the current value is 1, and 1 if the 
      // current value is 0. (Equivalent to a NOT operation)
      output ^= 1;
   }

   return output;

}

/*
   Sets the state of the output wire to the value of getOutput().
*/
void Gate::applyOutput()
{
   output->setState(calculateOutput());
}

Wire* Gate::getFirstInput() const
{
   return firstInput;
}

Wire* Gate::getSecondInput() const
{
   return secondInput;
}

Wire* Gate::getOutput() const
{
   return output;
}

Gate::GateType Gate::getType() const
{
   return type;
}

short Gate::getDelay() const
{
   return delay;
}

void Gate::setFirstInput(Wire* in)
{
   delete firstInput;
   firstInput = in;
}

void Gate::setSecondInput(Wire* in)
{
   delete secondInput;
   secondInput = in;
}

void Gate::setOutput(Wire* out)
{
   delete output;
   output = out;
}

void Gate::setType(GateType t)
{
   type = t;
}

void Gate::setDelay(short d)
{
   delay = d;
}

Gate::~Gate()
{
   delete firstInput;
   delete secondInput;
   delete output;
}

