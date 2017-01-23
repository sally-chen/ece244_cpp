/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sally090230
 *
 * Created on September 29, 2016, 10:12 PM
 */

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include "Rparser.h"

using namespace std;

NewRound::NewRound(int const maxResistor_, int const maxNodeNumber_ )
    : maxResistor(maxResistor_),
      maxNodeNumber(maxNodeNumber_),
        all_resis(new Resistor *[maxResistor_]()),
        all_node(new Node *[maxNodeNumber_+1]()),
        rIndex_(0),nodeIndex_(0){
}

void NewRound::pars(stringstream &lineStream, string &command){
    string name, marker;//marker: whether entered is all
    double resistance;
    int nodeid[2];
    
    if (command == "insertR") {
        lineStream >> name;            
        lineStream >> resistance;
        lineStream >> nodeid[0];        
        lineStream >> nodeid[1];
        
        if (insert_resistor(name, resistance,nodeid)){
            cout <<"Inserted: resistor " << name <<" "<< setprecision(2)<< fixed <<  resistance << " Ohms " <<nodeid[0] << " -> " <<nodeid[1] << endl;                
            return;
        }
        return;
    }else if (command == "modifyR") {
        lineStream >> name;
        lineStream >> resistance;
        
        for(int i = 0; i < rIndex_; i++){
            if ( all_resis[i]->getName() == name){
                all_resis[i]->setResistance(resistance);
                return;
            }
        }
        cout << "Error: resistor "<<name<<" not found" <<endl;
        return;
    }        
    //printR
    else if (command == "printR") {
        lineStream >> marker;
        if (marker == "all" ){
            cout <<"Print:" << endl;
            for(int i = 0; i < rIndex_; i++){
                all_resis[i]->print();
            }
            return;
        }  else {
            name = marker;
            cout <<"Print:" << endl;
            for(int i = 0; i < rIndex_; i++){
                if ( all_resis[i]->getName() == name){
                    all_resis[i]->print();
                    return;
                }
            }
            cout << "Error: resistor "<<name<<" not found" <<endl;
            return;
         }                
    } else if (command == "printNode") {
        lineStream >> marker;
        if (marker == "all"){
            for(int i = 0; i <= maxNodeNumber; i++){
                if(all_node[i]==NULL){
                   cout << "Connections at node  "<<i<<" : 0 resistor(s) "<<endl;
                }else{                   
                    all_node[i]->print(i, all_resis, maxResistor);
                }
            }
            return;
        } else{
            stringstream marker_dump (marker);
            marker_dump >> nodeid[0];
            nodeid[1] = 0;
            if( checkNode(nodeid)){
                cout << "Print:"<<endl;
                if(all_node[nodeid[0]]==NULL){
                   cout << "Connections at node  "<<nodeid[0]<<" : 0 resistor(s) "<<endl;
                    return;
                }else{                   
                    all_node[nodeid[0]]->print(nodeid[0], all_resis, maxResistor);
                    return;
                }
                return;
            }
        }
    }else if (command == "deleteR") {
        delete_all();
        cout <<"Deleted:  all resistors" << endl;
        return; 
    }
    return;
}

bool NewRound::insert_resistor(string name_,double resistance_,int endpoints_[2]){
    
    if(rIndex_ == maxResistor){
        cout << "Error: resistor array is full" << endl;
        return false;
    }
    for(int i=0;i<rIndex_;i++){
        if ( all_resis[i]->getName() == name_){
            cout<<"Error: resistor "<<name_<<" already exists "<<endl;
            return false;
        }
    }
    if(!checkNode(endpoints_))
        return false;    
    //create a new resistor object with increasing index
    all_resis[rIndex_] = new Resistor(rIndex_,name_, resistance_,endpoints_);    
    
    //add a new node, storing nodeIndex in node obj     
    if (!insert_Node(endpoints_[0])){
        return false;
    };
    if(!insert_Node(endpoints_[1])){
        return false;
    }
    
    ++rIndex_;

    return true;
}
bool NewRound::insert_Node(int endpoints){
   
    if (all_node[endpoints]==NULL){
        all_node[endpoints] = new Node(endpoints);
        all_node[endpoints] -> addResistor(rIndex_);
        return true;
    }
     else{
        if (all_node[endpoints] -> canAddResistor()){
           all_node[endpoints] -> addResistor(rIndex_);
            return true;
        }
        return false;
    }    
}
bool NewRound::checkNode(int endpoints[2]){
    if (endpoints[0] == endpoints[1]){
        cout << "Error: both terminals of resistor connect to node" << endpoints[0] << endl;
        return false;
    }
    if (endpoints[0] > maxNodeNumber || endpoints[0] < 0){
        cout << "Error: node "<<endpoints[0] << " is out of permitted range 0-"<<maxNodeNumber<<endl;
        return false;
    }
    if (endpoints[1] > maxNodeNumber || endpoints[1] < 0){
        cout << "Error: node "<<endpoints[1] << " is out of permitted range 0-"<<maxNodeNumber<<endl;
        return false;
    }
    return true;
}

NewRound:: ~NewRound(){
    delete_all();    
}
void NewRound:: delete_all(){
    if(if_command_delete)
        return;
    
    for(int i=0;i<maxNodeNumber; i++){
        if(all_node[i]!=NULL){
            delete all_node[i];
        }
    }
    delete [] all_node;
    
    for(int i=0;i<maxResistor; i++){
        if(all_resis[i]!=NULL){
            delete all_resis[i];
        }
    }
    delete [] all_resis;    
    rIndex_ = 0;
    nodeIndex_=0;
    if_command_delete = 1;
    return;
}

void NewRound::reset(int const new_maxNodeNumber, int const new_maxResistor){
    delete_all();
    
    maxNodeNumber = new_maxNodeNumber;
    maxResistor = new_maxResistor;
    cout << "New network: max node number is " <<maxNodeNumber <<"; max resistor is "<<maxResistor<<endl; 
    all_resis = new Resistor *[new_maxResistor]();
    all_node = new Node *[new_maxNodeNumber+1](); 
    rIndex_ = 0;
    nodeIndex_=0;
    if_command_delete = 0;
    return;
}