/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: sally090230
 *
 * Created on November 7, 2016, 12:30 PM
 */

#ifndef NODELIST_H
#define NODELIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Node.h"

#define MIN_ITERATION_CHANGE 0.0001
//holds a linked-list of nodes
//each node contains  a resistor list
//each resistor contain resistors
using namespace std;

class Node;

class NodeList{
private:
    Node* head; 
public:
    //accept a nodeid and return a pointer to the corresponding node, or null if does not exist
    NodeList();
    ~NodeList();
    
    Node* search_node(int node_id);
    Resistor* findResistor_inNodeList(string &resistorName);
    void change_resistance(string &resistorName, double resistance);
    void printR(string &resistorName);
    void printAllNode();
    void printOneNode(int node_id);
    void insert_in_node(const int node_id,string &resistor_name, double resistance,int nodeid_array[2]);
    Node* insert_new_node(int node_id);
    void deleteResistor(string &resistor_name);
    void deleteAll();
    void setV(int node_id,double volt);
    void unsetV(int node_id);
    void solve();
    
    
};


#endif /* NODELIST_H */

