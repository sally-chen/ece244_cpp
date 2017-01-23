

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include "Rparser.h"

using namespace std;

Rparser::Rparser(NodeList &node_list):node_list(node_list){
}

void Rparser::pars(stringstream &lineStream, string &command){
    string name, marker;//marker: whether entered is all
    double resistance,volt;
    int nodeid[2];
    
    if (command == "insertR") {
        lineStream >> name;            
        lineStream >> resistance;
        lineStream >> nodeid[0];        
        lineStream >> nodeid[1];
        Resistor* temp_resis = node_list.findResistor_inNodeList(name);    
        if(temp_resis != NULL){
           cout << "Error: resistor "<<name<<" already exists"<<endl;
            return;
        }        
        node_list.insert_in_node(nodeid[0],name,resistance,nodeid);
        node_list.insert_in_node(nodeid[1],name,resistance,nodeid);
        cout <<"Inserted: resistor " << name <<" "<< setprecision(2)<< fixed <<  resistance << " Ohms " <<nodeid[0] << " -> " <<nodeid[1] << endl;  
        return;             
    }else if (command == "modifyR") {
        lineStream >> name;
        lineStream >> resistance;
        node_list.change_resistance(name,resistance);
        return;
    }        
    //printR
    else if (command == "printR") {
        lineStream >> name;
        cout <<"Print:" << endl;
        node_list.printR(name);
        return;
                    
    } else if (command == "printNode") {
        lineStream >> marker;
        if (marker == "all"){
            cout <<"Print:" << endl;
            node_list.printAllNode();
        } else{
            stringstream marker_dump (marker);
            marker_dump >> nodeid[0];
            nodeid[1] = 0;
            node_list.printOneNode(nodeid[0]);
        }
    }else if (command == "deleteR") {
        lineStream >> marker;
        if (marker == "all"){
            node_list.deleteAll();
            return;
        } else{
            node_list.deleteResistor(marker);
            return;
        }
    }else if(command == "setV"){
        lineStream >> nodeid[0];
        lineStream >> volt;
        node_list.setV(nodeid[0],volt);
        return;        
    }else if(command == "unsetV"){
        lineStream >> nodeid[0];
        node_list.unsetV(nodeid[0]);
        return;
    }if(command == "solve"){        
        node_list.solve();        
        return;
    }
    return;
}


Rparser:: ~Rparser(){
    delete_all();    
}
void Rparser:: delete_all(){
    
}
