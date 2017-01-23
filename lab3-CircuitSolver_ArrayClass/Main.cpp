/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Main.cpp
 * Author: sally090230
 *
 * Created on October 16, 2016, 2:16 AM
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
    int maxNodeNumber,maxResistor;
    int if_firstRound = 1;
    NewRound *new_rd = NULL;
    
    cout << "> ";
    getline (cin, line); // Get a line from standard input
   
    while ( !cin.eof () ) { 
        stringstream lineStream (line);      
        lineStream >> command;
        
        if(command == "maxVal"){
            lineStream >> maxNodeNumber;
            lineStream >> maxResistor;
        
            if(maxNodeNumber <= 0 || maxResistor <= 0 ){
                cout << "Error: maxVal arguments must be greater than 0" << endl;                
            }else{
                if(if_firstRound){
                     new_rd = new NewRound(maxResistor,maxNodeNumber);
                     cout << "New network: max node number is " <<maxNodeNumber <<"; max resistors is "<<maxResistor<<endl; 
                     if_firstRound = 0;
                }else{
                    new_rd -> reset(maxNodeNumber,maxResistor);
                    /*delete new_rd;
                    new_rd = new NewRound(maxResistor,maxNodeNumber);
                    cout << "New Network: max node number is " <<maxNodeNumber <<"; maxResistor is "<<maxResistor<<endl; 
                    */
               }
            }               
        }else{
            new_rd->pars(lineStream, command); 
        }        
        lineStream.ignore(100, '\n');
         
        cout << "> ";
        getline (cin, line);
    } // End input loop until EOF.
    
    return 0;
    
}
