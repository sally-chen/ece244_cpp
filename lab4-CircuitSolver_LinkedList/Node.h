/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: sally090230
 *
 * Created on November 7, 2016, 12:30 PM
 */

#ifndef NODE_H
#define NODE_H
#include <string>
#include <iomanip>
#include <cmath> 
#include "ResistorList.h"
using namespace std;
class Node{
private:
    int node_id;
    int count_resistor;
    int if_volt_set;//1 is set, 0 not set
    double voltage;
    double prev_volt;
    Node *next_node;
    ResistorList R_list;
public:
    Node(int const id, string &resistor_name, double resistance,int nodeid_array[2]);
    Node(int node_id, Node* _next);
    Node* getNext();
    int getNodeid();
    void setNext(Node* _next);
    void addResistor(string &resistor_name, double resistance,int nodeid_array[2]);
    Resistor* findResistor_inNode(string &resistor_name);
    void printNode();
    void deleteRes_inNode(string &resistor_name);
    void setVNode(double volt);
    double setNodeVSolve(double volt);
    void unsetVNode();
    int getIf_volt_set();
    Resistor* getPositionNode();
    double getVolt();
    void printVolt();
    ~Node();
};

#endif /* NODE_H */

