/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Node.h"

Node::Node(int id, string &resistor_name, double resistance,int nodeid_array[2]):node_id(id),next_node(NULL){
    R_list.insert_resistor(resistor_name,resistance,nodeid_array);
    count_resistor = 1;
    if_volt_set = 0;   
    prev_volt = 0;
    voltage = 0.0;//maybe optional
}
Node::Node(int node_id, Node* _next):node_id(node_id),next_node(_next){
    if_volt_set = 0; 
    prev_volt = 0;
    voltage = 0.0;//maybe optional
}

Node* Node::getNext(){
  return next_node;
}
int Node::getNodeid(){
    return node_id;
}

void Node::setNext(Node* _next){
    next_node = _next;
}
void Node::addResistor(string &resistor_name, double resistance,int nodeid_array[2]){
    R_list.insert_resistor(resistor_name,resistance,nodeid_array);
    count_resistor++;
    
}
Resistor* Node::findResistor_inNode(string &resistor_name){
    Resistor* temp = R_list.search_resistor(resistor_name);
    if(temp != NULL){
        return temp;
    }else
        return NULL;
}
void Node::printNode(){
    cout<<"Connections at node "<<node_id<<": "<<count_resistor<<" resistor(s)"<<endl; //need a counter
    R_list.printAllRes(count_resistor);
    return;
}
void Node::deleteRes_inNode(string &resistor_name){
    R_list.deleteValue(resistor_name);
    count_resistor--;
    return;
}
void Node::setVNode(double volt){
    voltage = volt;
    cout << "Set: node "<<node_id<<" to "<<setprecision(2)<< fixed <<voltage<<" Volts"<<endl;
    if_volt_set = 1;
}
double Node::setNodeVSolve(double volt){
    double diff;
    prev_volt = voltage;
    voltage = volt;
   diff = abs(voltage-prev_volt);
    return diff;
}
void Node::unsetVNode(){
    if_volt_set = 0;
    prev_volt = 0.0;
    cout<<"Unset: the solver will determine the voltage of node " <<node_id<<endl;
}
int Node::getIf_volt_set(){
    return if_volt_set;
}
Resistor* Node::getPositionNode(){
    return R_list.getPosition();
}
double Node::getVolt(){
    return voltage;
}
void Node::printVolt(){
    cout<<"  Node "<<node_id<<": "<<setprecision(2)<<voltage<<" V"<<endl;
    return;
}
Node::~Node(){

}
