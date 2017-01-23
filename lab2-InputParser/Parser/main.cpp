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


#define MAX_NODE_NUMBER 5000

using namespace std;

/*
 * 
 */
/*

  bool check_too_many(string &extra){
    if(extra == ""){        
        return true;
    }
    cout << "Error: too many arguments"<< endl;
    return false;
}*/

bool check_too_many(stringstream &lineStream){
    if(!lineStream.eof()){
         cout << "Error: too many arguments"<< endl;
         return false;
    }
    return true;
}

bool ckeck_equ_nodeid(int nodeid1,int nodeid2){
    if(nodeid1 == nodeid2){
        cout << "Error: both terminals of resistor connect to node "<< nodeid1 << endl;
        return false;
    }
    return true;

}

bool check_node_range(int nodeid){
    if (nodeid < 0 || nodeid > MAX_NODE_NUMBER ){
        cout << "Error: node "<< nodeid << " is out of permitted range 0-"<<MAX_NODE_NUMBER<< endl;
        return false;
    }
    return true;
}

bool check_if_all ( string &name){
    if(name == "all"){
        cout << "Error: resistor name cannot be the keyword 'all'" << endl;
        return false;
    }
    return true;
}
bool check_neg_resist (double res){
      if(res < 0.0){
         cout << "Error: negative resistance" << endl;
        return false;
      }
      return true;
}

bool check_fail(stringstream &lineStream){
    if (lineStream.fail()){
        if (lineStream.eof()){
            cout<< "Error: too few argument"<<endl;
            return false;
        }
        cout<<"Error: invalid argument"<<endl;
        return false;
    }
    return true;
}


bool check_int(stringstream &lineStream){
    //char c = lineStream.get();
    if(!lineStream.eof()){
        int c = lineStream.peek();
        if(c == '.' ){
            cout << "Error: invalid argument" << endl;   
            
            return false;                
        }
    }
    //lineStream.putback (c);
    //cout << "c is"<< c <<11<< endl;
    return true;
}

void pars(stringstream &lineStream, string &command){
    
    string name, marker,extra;//marker: whether entered is all
    double resistance;
    int nodeid1, nodeid2,c;
    
    
        
        //insertR
        if (command == "insertR") {
            // parse an insertR command       
            
            lineStream >> name;            
            lineStream >> resistance;
           
            lineStream >> nodeid1;        
            if(!check_int(lineStream))
               return;
            
            lineStream >> nodeid2;
            if(!check_int(lineStream))
                return; 
           /*
            if (!lineStream.eof()){
                lineStream >> extra;
            }*/
            
            if( check_if_all(name) && check_neg_resist(resistance) &&  check_node_range(nodeid1) && check_fail(lineStream)
            && check_node_range(nodeid2) && ckeck_equ_nodeid(nodeid1,nodeid2) && check_too_many(lineStream)){
                cout <<"Inserted: resistor " << name <<" "<< setprecision(2)<< fixed <<  resistance << " Ohms " <<nodeid1 << " -> " <<nodeid2 << endl;                
                return;
            }               
            //err check
        }//insertR
        //modifyR
        else if (command == "modifyR") {
            lineStream >> name;
            lineStream >> resistance;
            if(check_if_all(name) && check_neg_resist(resistance) && check_fail(lineStream) && check_too_many(lineStream)){
                 cout <<"Modified: resistor " << name << " to " << setprecision(2)<< fixed << resistance << " Ohms" << endl;
                 return;
            }
        }        
        //printR
        else if (command == "printR") {
            lineStream >> marker;
            if (marker == "all" ){
                if(check_fail(lineStream) && check_too_many(lineStream)){
                    cout <<"Print:  all resistors" << endl;
                    return;
                }                
            } else if (marker == ""){
                
                cout << "Error: too few arguments" << endl;
                return;
            }    else {
                name = marker;
                if(check_too_many(lineStream)){
                    cout <<"Print: resistor " << name << endl;
                    return;
                }          
             }                
        }
        //printNode
        else if (command == "printNode") {
            lineStream >> marker;
            if (marker == "all"){
                if(check_too_many(lineStream)){
                    cout <<"Print:  all nodes" << endl;
                    return;
                }       
           } else if (marker == ""){               
                cout << "Error: too few arguments" << endl;
                return;
            } else{
                stringstream marker_dump (marker);
                marker_dump >> nodeid1;
                if(check_fail(marker_dump) && check_int(marker_dump) && check_node_range(nodeid1) && check_too_many(lineStream)){
                    cout <<"Print: node " << nodeid1 << endl;
                    return;
                }
            }
        }
        //deleteR
        else if (command == "deleteR") {
            lineStream >> marker;
            if (marker == "all"){
                if(check_too_many(lineStream)){
                    cout <<"Deleted:  all resistors" << endl;
                    return;
                }    
            } else if (marker == ""){
                
                cout << "Error: too few arguments" << endl;
                return;
            }    else {
                name = marker;
                if(check_too_many(lineStream)){
                    cout <<"Deleted: resistor " << name << endl;
                    return;
                }                  
            }            
        }else{            
            //invalid command
            cout << "Error: invalid command"<<endl;
            return;
        }
}


int main( ) {
    string line, command;
    
    cout << "> ";
    getline (cin, line); // Get a line from standard input
   
    while ( !cin.eof () ) { 
        stringstream lineStream (line);      
        lineStream >> command;
        
        pars(lineStream, command); 
        lineStream.ignore(100, '\n');
         
        cout << "> ";
        getline (cin, line);
    } // End input loop until EOF.
    
    return 0;
}
