/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Resistor.h
 * Author: sally090230
 *
 * Created on November 7, 2016, 12:30 PM
 */

#ifndef RESISTOR_H
#define RESISTOR_H
#include <string>
#include <iostream>
using namespace std;

class Resistor{
private:
    string resistor_name;
    int endpoints[2];
    double resistance;
    Resistor* next;
public:
    Resistor(string resistor_name, double resistance,int getN[2], Resistor *n);
    Resistor *getNext() const; 
    void setNext(Resistor *_n); 
    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    int getNodeID(int index) const;
    void setResistance (double resistance_);
    void print ();
    int getOtherNodeid(int nodeid);
};


#endif /* RESISTOR_H */

