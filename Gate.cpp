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
   if (secondInput != nullptr)
   {
      secondInput->addGate(this);
   }
}

Gate::Gate(Wire* inputA, Wire* out, short d) : Gate(inputA, nullptr, out, Gate::NOT, d)
{
}


/*
   Determines whether the current state of the wires even changes the output for 
   this gate. This function evaluates to true if the current state of this Gate's
   output wire is different from the calculation of its output, and false if they
   are the same.
*/
bool Gate::isOutputChanging()
{
   short newOutput = calculateOutput();

   return newOutput != output->getState() || (scheduledOutput != -1 && newOutput != scheduledOutput);
}

/*
   Calculates the value that should be on this Gate's output wire. This function
   returns 0 if the output of this gate should be false, 1 if it should be true
   and Wire::UNDEF (3) if the value is undefined.
*/
short Gate::calculateOutput()
{

   short a   = firstInput->getState(), b;
   short sum = a;

   // Check for NOT gates so we don't blow up with a nullptr
   if (type != Gate::NOT)
   {
      b   = secondInput->getState();
      sum += b;
   }

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
         
         // Set the output to be the value of a, and get it ready to be complimented
         output = a;

         break;

      case AND:
      case NAND:

         // If the sum has exceeded 3, one of the values is not zero and the other is undefined, 
         // or they are both undefined. In either case, we want to return UNDEF.
         if (sum > 3)
         {
            return Wire::UNDEF;
         }
         
         output = a & b;

         break;

      case OR:
      case NOR:

         // If the sum is 3, one of the wires is UNDEF and the other is 0. This is an UNDEF case
         if (sum == 3)
         {
            return Wire::UNDEF;
         }
         
         // This needs to be adjusted in case there is an UNDEF, which is accomplished with & 1
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
      output ^= 1;
   }

   // We have acheived the scheduled output, so we can now forget about it.
   if (scheduledOutput == output)
   {
      scheduledOutput = -1;
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

void Gate::scheduleOutput(short value)
{
   scheduledOutput = value;
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

int Gate::getDelay() const
{
   return delay;
}