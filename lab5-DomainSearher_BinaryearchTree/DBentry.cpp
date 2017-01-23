#include "DBentry.h"

using namespace std;
DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active):
name(_name),IPaddress(_IPaddress),active(_active){
}

// the destructor
DBentry:: ~DBentry(){

}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name){
    name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active){
    active = _active;
}

// returns the name.
string DBentry::getName() const{
    return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const{
    return active;
}

// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs){
    string if_active;
    if_active = (rhs.active)? "active":"inactive";
    out << rhs.name<<" : "<<rhs.IPaddress<<" : "<<if_active<<endl;
    return out;
}
