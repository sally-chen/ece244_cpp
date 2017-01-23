#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>
#include "../TreeDB.h"
using namespace std;

void pars(stringstream &lineStream, string &command,TreeDB &tree);

int main(){
    
    string line, command;
    TreeDB tree;
    cout << "> ";
    getline (cin, line); // Get a line from standard input
   
    while ( !cin.eof () ) { 
        stringstream lineStream (line);      
        lineStream >> command;        
        pars(lineStream, command,tree); 
        lineStream.ignore(100, '\n');
        cout << "> ";
        getline (cin, line);
    } // End input loop until EOF.
    
    return 0;
    
}
void pars(stringstream &lineStream, string &command,TreeDB &tree){
    string name,status;
    unsigned int IPaddress;
    bool status_bool;
    
    if (command == "insert") {
        lineStream >> name;
        lineStream >> IPaddress;
        lineStream >> status;
        
        if(status == "active")
            status_bool = 1;
        else if(status == "inactive")
            status_bool = 0;
        
        DBentry* new_entry = new DBentry(name,IPaddress,status_bool);
        if(tree.insert(new_entry))
            cout << "Success"<<endl;
        else
            cout << "Error: entry already exists"<<endl;
        return;             
    }else if (command == "find") {
        lineStream >> name;
        DBentry* query = tree.find(name);
        if(query != NULL)
            cout << *query;
        else
            cout <<"Error:entry does not exist" <<endl;
        return;
    }        
    //printR
    else if (command == "updatestatus") {
        lineStream >> name;
        lineStream >> status;
        
        if(status == "active")
            status_bool = 1;
        else if(status == "inactive")
            status_bool = 0;
        
        DBentry* query = tree.find(name);
        if(query != NULL){
            query->setActive(status_bool);
            cout << "Success" <<endl;
        }else
            cout <<"Error:entry does not exist" <<endl;
        return;                    
    } else if(command == "countactive"){
        tree.countActive();
    }else if(command == "printprobes"){
         lineStream >> name;
        if(tree.find(name)==NULL)
            cout <<"Error:entry does not exist" <<endl;
        else
            tree.printProbes();
         return;
    }else if(command=="printall"){
       cout<<tree;
        return;
    }else if(command =="remove"){
        lineStream >> name;
        if(tree.remove(name))
            cout<<"Success"<<endl;
        else
            cout <<"Error:entry does not exist" <<endl;  
        return;
    }else if(command == "removeall"){
        if(tree.remove("")){
            cout<<"Success"<<endl;
        }
        return;
    }
    return;
}