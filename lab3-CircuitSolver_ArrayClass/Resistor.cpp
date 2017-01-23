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

Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]):
rIndex(rIndex_),name(name_),resistance(resistance_){
    for(int i = 0 ; i<2; i++){
        endpointNodeIDs[i] = endpoints_[i];
    }
}

string Resistor:: getName() const{
    return name;
} // returns the name

double Resistor::getResistance() const{
    return resistance;
} // returns the resistance

int Resistor::getNodeID(int index) const{
    return endpointNodeIDs[index];
    
}

void Resistor::setResistance (double resistance_){
    cout <<"Modified: resistor " << name << " from "<<setprecision(2)<<fixed << resistance <<" Ohms to " << setprecision(2)<< fixed << resistance_ << " Ohms" << endl;
    resistance = resistance_;
    return;
} 

void Resistor::print (){
    cout << std::setfill (' ') << std::setw (20);
    cout<<left<< name<<" ";
    cout << std::setfill (' ') << std::setw (8);
    cout<<right<<resistance<<" Ohms "<<endpointNodeIDs[0]<<" -> "<<endpointNodeIDs[1]<<endl;
}
   
