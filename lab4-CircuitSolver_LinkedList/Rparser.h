#ifndef RPARSER_H
#define RPARSER_H
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>

#include "NodeList.h"

class NodeList;

class Rparser {
private:
    //is this needed????
    NodeList node_list;
public:
    Rparser(NodeList &node_list);
    ~Rparser();
    void delete_all();
    //adding resistor when getting inserR
    bool insert_resistor(string name_,double resistance_,int endpoints_[2]);
    bool insert_Node(int endpoints);
    void pars(stringstream &lineStream, string &command);
};
#endif /* RPARSER_H */