/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <iostream>
#include "Node.h"

using namespace std;

 Node::Node(int node_id_)
    :node_id(node_id_){ 
 } 
 Node:: ~Node(){}

   // Checks to see if the resistor can be added to poistion rIndex
   // in the resistor array. Returns true if yes, otherwise false.
   bool Node::canAddResistor(/*int rIndex*/){
        ++numRes;
       if (numRes >= MAX_RESISTORS_PER_NODE){
           cout << "Error: Node is full" << endl;
           --numRes;
           return false;
       }
       return true;
   }
   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
   void Node::addResistor (int rIndex){       
       resIDArray[numRes] = rIndex;
       return;
   }
   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void Node::print (int nodeIndex,Resistor *all_resis[],int maxResistor ){
       cout << "Connections at node "<<nodeIndex<<": "<<(numRes+1)<<" resistor(s)"<<endl;
       for(int i=0; i < (numRes+1);i++){
           cout << "  ";
           all_resis[resIDArray[i]] -> print();//how to use 
        } 
       return;
   }
