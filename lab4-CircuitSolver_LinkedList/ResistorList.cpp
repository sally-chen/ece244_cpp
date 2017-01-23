/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ResistorList.h"
#include "Resistor.h"
#include <iostream>

ResistorList::ResistorList():head(NULL){
    
}
void ResistorList::insert_resistor(string &resistor_name, double resistance,int nodeid_array[2]){
    Resistor* new_resis = new Resistor(resistor_name,resistance,nodeid_array,head);
    head = new_resis;
    position = head;
    return;
}
Resistor* ResistorList::search_resistor(string &resistor_name){
    if(head == NULL)
        return NULL;
    for (Resistor* cur = head; cur != NULL; cur = cur->getNext()){
        if (cur->getName() == resistor_name){
            return cur;
        } 
    }
    return NULL;
}
void ResistorList::printAllRes(int count_resistor){
    Resistor* toBePrinted[count_resistor];
    int i=0;
    for (Resistor* cur = head; cur != NULL; cur = cur->getNext()){
        toBePrinted[i] = cur;
        i++;
    }
    for(i=count_resistor-1;i>=0;i--){
        cout << "  ";
        toBePrinted[i]->print();
    }
    return;
}
void ResistorList::deleteValue(string &resistor_name) {
    Resistor *p = head, *prev = NULL;
    while (p != NULL && p->getName() != resistor_name) {
        prev = p;
        p = p->getNext();
    }
    if (p == NULL) // _data is not in the list
        return;
    /* Remove the node pointed by p from the list. */
    if (prev == NULL) // p is the head of the list!
        head = p->getNext();
    else
        prev->setNext(p->getNext());
    delete p;
    return;
}
void ResistorList::deleteAllRes(){
    Resistor *p;
    while (head != NULL) {
        p = head;
        head = p->getNext();
        delete p;
    }
    return;
}
Resistor* ResistorList::getPosition(){
    Resistor* p = position;        
    if (p != NULL){
        position = p->getNext();
        return p;        
    }else{
        position = head;
        return NULL;
    }
}
ResistorList::~ResistorList(){
    deleteAllRes();
}