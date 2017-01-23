/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "NodeList.h"
#include "Node.h"
#include <iostream>

NodeList::NodeList():head(NULL){
    
}
NodeList::~NodeList(){

}
Node* NodeList::search_node(int node_id){
    for (Node* cur = head; cur != NULL; cur = cur->getNext()){
        if (cur->getNodeid() == node_id)
            return cur;
        if (cur->getNodeid() > node_id)
            return NULL;
    }
    return NULL;
}
Resistor* NodeList::findResistor_inNodeList(string &resistorName){
    Resistor* tempRes;
    for (Node* cur = head; cur != NULL; cur = cur->getNext()){
        tempRes = cur->findResistor_inNode(resistorName);
        if (tempRes!= NULL){
            return tempRes;
        }            
    }
    return NULL;
}

void NodeList::change_resistance(string &resistorName, double resistance){
    Resistor* temp = findResistor_inNodeList(resistorName);
    Node* node1;
    Node* node2;
    Resistor* r1;
    Resistor* r2;
    if(temp == NULL){
        cout << "Error: resistor "<<resistorName<<" not found"<<endl;
        return;
    }else{
        node1 = search_node(temp->getNodeID(0));  
        node2 = search_node(temp->getNodeID(1));  
        r1=node1->findResistor_inNode(resistorName);
        r2=node2->findResistor_inNode(resistorName);
        r1->setResistance(resistance);
        r2->setResistance(resistance);
        cout <<"Modified: resistor " << resistorName << " from "<<setprecision(2)<<fixed << resistance <<" Ohms to " << setprecision(2)<< fixed << resistance_ << " Ohms" << endl;
        return;
    }   
}
void NodeList::printR(string &resistorName){
    Resistor* temp = findResistor_inNodeList(resistorName);
    if(temp == NULL){
        cout << "Error: resistor "<<resistorName<<" not found"<<endl;
        return;
    }else{
        temp->print();
        return;
    } 
}
void NodeList::insert_in_node(const int node_id,string &resistor_name, double resistance,int nodeid_array[2]){
    
    if(head==NULL){
        head = new Node(node_id,resistor_name,resistance,nodeid_array);
        return;//return  true
    }
    Node* existed_node = search_node(node_id);
    if(existed_node!=NULL){
        existed_node->addResistor(resistor_name,resistance,nodeid_array);
        return;//return 
    }else{
        existed_node = insert_new_node(node_id);
        existed_node->addResistor(resistor_name,resistance,nodeid_array);
        return;
    }            
}  
Node* NodeList::insert_new_node(int node_id){
    Node *n = new Node(node_id,NULL);
    Node *p = head;
    Node *prev = NULL;
    while (p != NULL && p->getNodeid() < node_id) {
      prev = p;
      p = p->getNext();
    }
    n->setNext(p);
    if (prev == NULL) // head of the list!
      head = n;
    else
      prev->setNext(n);
    
    return n;
}
void NodeList::printAllNode(){
    for (Node* cur = head; cur != NULL; cur = cur->getNext()){
        cur->printNode();
    }
    return;
}
void NodeList::printOneNode(int node_id){
    Node* tempNode = search_node(node_id);
    if(tempNode == NULL){
        cout << "Error: Node "<<node_id<<" not found"<<endl;
        return;
    }else{
        tempNode->printNode();
        return;
    }
}
void NodeList::deleteResistor(string &resistor_name){
    Resistor* found = findResistor_inNodeList(resistor_name);   
    if(found == NULL){
        cout << "Error: resistor "<<resistor_name<<" not found"<<endl;
        return;
    }else{
        Node* endp1 = search_node(found->getNodeID(0));
        Node* endp2 = search_node(found->getNodeID(1));        
        endp1->deleteRes_inNode(resistor_name);
        endp2->deleteRes_inNode(resistor_name);
        cout <<"Deleted: resistor "<<resistor_name<<endl;
        return;
    }
}
void NodeList::deleteAll(){
    Node *p;
    while (head != NULL) {
         p = head;
        head = p->getNext();
        delete p;
    }
    cout<<"Deleted all resistors"<<endl;
}
void NodeList::setV(int node_id,double volt){
    Node* temp = search_node(node_id);
    if(temp == NULL){
        cout << "Error: Node "<<node_id<<" not found"<<endl;
        return;
    }else{
        temp->setVNode(volt);
        return;
    }
}
void NodeList::unsetV(int node_id){
    Node* tempNode = search_node(node_id);
    if(tempNode == NULL){
        cout << "Error: Node "<<node_id<<" not found"<<endl;
        return;
    }else{
        tempNode->unsetVNode();
        return;
    }
}
void NodeList::solve(){
    Resistor* cur_resis;
    Node* connected_node;
    double top, bottom,diff,min_change;
    int count_if_set;
    count_if_set=0;
    min_change = 0.00015;
    for (Node* cur = head; cur != NULL; cur = cur->getNext()){
        if (cur->getIf_volt_set()){
           count_if_set ++;
        }
    }
    if(!count_if_set){
        cout << "Error: no nodes have their voltage set"<<endl;
        return;
    }
    while(min_change > MIN_ITERATION_CHANGE ){
        min_change = 0.0001;
        for(Node* cur = head; cur != NULL; cur = cur->getNext()){
            if (!cur->getIf_volt_set()){
                cout<<"Entered if"<<endl;
                top = 0.0;
                bottom = 0.0;  
                cur_resis = cur->getPositionNode();
                while(cur_resis!=NULL){
                    bottom += 1/(cur_resis->getResistance());
                    connected_node = search_node(cur_resis->getOtherNodeid(cur->getNodeid()));                    
                    top += (connected_node->getVolt())/(cur_resis->getResistance());
                    cur_resis = cur->getPositionNode();
                }
                diff = cur->setNodeVSolve(top/bottom);                 
            }    
            if(diff > min_change)
                min_change = diff;
        }
    }
    cout <<"Solve:"<<endl;
    for (Node* cur = head; cur != NULL; cur = cur->getNext()){
        cur->printVolt();
    }
    return;
}