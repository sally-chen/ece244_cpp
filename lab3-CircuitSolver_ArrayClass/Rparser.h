/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.h
 * Author: sally090230
 *
 * Created on October 16, 2016, 2:23 AM
 */

#ifndef RPARSER_H
#define RPARSER_H
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>

#include "Node.h"


class NewRound {
private:
    int maxResistor;
    int maxNodeNumber;
    Resistor ** all_resis; // Resistor* [] // vector<Resistor*> all_resistor
    Node ** all_node;
    int rIndex_;//how many resistors are there already?
    int nodeIndex_;//how  many nodes created?
     int if_command_delete = 0;
public:
    //set max num of resistors and node upon getting maxval command
    NewRound(int const maxResistor_, int const maxNodeNumber_ );
    ~NewRound();
    void delete_all();
    //adding resistor when getting inserR
    bool insert_resistor(string name_,double resistance_,int endpoints_[2]);
    bool insert_Node(int endpoints);
    bool checkNode(int endpoints[2]);
    void reset(int const new_maxNodeNumber, int const new_maxResistor);
    void pars(stringstream &lineStream, string &command);
};



#endif /* RPARSER_H */

