/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include "Resistor.h"

Resistor::Resistor(string resistor_name, double resistance,int nodeid_array[2], Resistor *n):
    resistor_name(resistor_name),resistance(resistance),next(n){  
    endpoints[0] = nodeid_array[0];
    endpoints[1] = nodeid_array[1];
}
Resistor* Resistor::getNext() const{
    return next;
} 
void Resistor::setNext(Resistor *_n){
    next = _n;
}
string Resistor:: getName() const{
    return resistor_name;
} // returns the name

double Resistor::getResistance() const{
    return resistance;
} // returns the resistance

int Resistor::getNodeID(int index) const{
    return endpoints[index];
    
}

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
    return;
} 

void Resistor::print (){
    cout << std::setfill (' ') << std::setw (20);
    cout<<left<< resistor_name<<" ";
    cout << std::setfill (' ') << std::setw (8);
    cout<<right<< setprecision(2)<<resistance<<" Ohms "<<endpoints[0]<<" -> "<<endpoints[1]<<endl;
}
int Resistor::getOtherNodeid(int nodeid){
    if(endpoints[0] != nodeid)
        return endpoints[0];
    else
        return endpoints[1];
}