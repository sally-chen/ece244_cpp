#ifndef RESISTOR_H
#define RESISTOR_H
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>

using namespace std;


//each object holds info about one resistor in the network
//program shall store all resistors in an array, starting at element 0,when 
//adding a resistor to a node, the resistor shall be refered to by its position in the resistor array 
class Resistor
{
private:
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   int rIndex;
   // static int rIndexGenerator;

public:
   Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects

   //~Resistor();

   string getName() const; // returns the name
   double getResistance() const; // returns the resistance
   int getNodeID(int index) const;

   void setResistance (double resistance_);

   // you *may* create either of the below to print your resistor
   void print ();
 
};


#endif	/* RESISTOR_H */

