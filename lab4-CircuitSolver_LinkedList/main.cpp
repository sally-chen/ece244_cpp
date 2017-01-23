/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sally090230
 *
 * Created on November 7, 2016, 12:26 PM
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

int main(){
    
    string line, command;
    
    NodeList node_list;
    Rparser new_rd(node_list);
    cout << "> ";
    getline (cin, line); // Get a line from standard input
   
    while ( !cin.eof () ) { 
        stringstream lineStream (line);      
        lineStream >> command;     
       
        new_rd.pars(lineStream, command); 
       
        lineStream.ignore(100, '\n');
         
        cout << "> ";
        getline (cin, line);
    } // End input loop until EOF.
    
    return 0;
    
}
