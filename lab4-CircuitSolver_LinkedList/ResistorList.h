/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: sally090230
 *
 * Created on November 7, 2016, 12:29 PM
 */

#ifndef RESISTORLIST_H
#define RESISTORLIST_H
#include <string>
#include "Resistor.h"

using namespace std;

class Resistor;

class ResistorList{
private:
    Resistor* head;  
    Resistor* position;
public:
    ResistorList();
    ~ResistorList();
    void insert_resistor(string &resistor_name, double resistance,int nodeid_array[2]);
    Resistor* search_resistor(string &resistor_name);
    void printAllRes(int count_resistor);
    void deleteValue(string &resistor_name);
    void deleteAllRes();
    Resistor* getPosition();
};


#endif /* RESISTORLIST_H */

