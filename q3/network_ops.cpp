#include "network.hpp"

Network flatten(const char &nType,const Network &parts);
Network sort(const Network &parts);

Network R(float v)
{
    return {'R', v, {} };
}

Network C(float v)
{
    return {'C', v, {} };
}

Network L(float v)
{
    return {'L', v, {} };
}


bool operator==(const Network &a, const Network &b)
{
    if(a.type != b.type) return false;
    if(a.value != b.value) return false;
    return a.parts == b.parts;
}

bool operator<(const Network &a, const Network &b){
		if(b.type==a.type){
				return(a.value<b.value);
		}
		switch(a.type){
				case '|': //if a is a series network
								return false; //return false, as a>b
						break;
				case 'R': //if a is a resistor
						if(b.type!='|'){ //and b is not a series network
								return false; //return false, as a>b
						}
						else{ //and b is a series network
								return true; //return true, as a<b
						}
						break;
				case 'L': //if a is an inductor
						if(b.type == '&'|| b.type == 'C'){ //and b is a parallel network or a capacitor
								return false; //return false, as a>b 
						}
						else{ //and b is a series network or a resistor
								return true; //return true, as a<b
						}
						break;
				case 'C': //if a is a capacitor
						if(b.type == '&'){ //and b is a parallel network
								return false; //return false as a>b
						}
						else{ //and b is a series network, resistor or inductor
								return true;
						}
						break;
				case '&': //if a is a parallel network and b is not
						return true; //return true as a<b
						break;
		}
		cout<<"A or B has an invalid type or value"<<endl;
		exit(19); //exit with error code 19 if a or b's value or type is invalid
}

Network operator|(const Network &a, const Network &b)
{
    return Network{'|', 0, {a,b} };
}

Network operator&(const Network &a, const Network &b)
{
    return Network{'&', 0, {a,b} };
}
/*
Network operator=(const Network &a){
		Network b;
		b.value = a.value;
		b.parts = a.parts;
		b.type = a.type;
		return b;
}
*/
bool is_primitive(const Network &a)
{
    if((a.parts).size()==0){
				return true; //Return true if the vector of subparts is empty
		}
		return false; //Return false otherwise
}

bool is_composite(const Network &a)
{
    return !is_primitive(a);
}

vector<Network> flatten(const char &nType,const vector<Network> &parts){ //TODO: implement flatten
		vector<Network> _;
		return _;
}

vector<Network> sort(const vector<Network> &parts){ //TODO: implement sort
		vector<Network> _;
		return _;
}

Network canonicalise(const Network &x)
{
    if(is_primitive(x)){ //if x is a primitive network
				return x; //return the primitive network
		}
		vector<Network> parts = x.parts; //create a modifiable parts list
		for(Network n : x.parts){ //for each network in x
				parts.push_back(canonicalise(n)); //push it to the back of the modifiable parts list
		}
		parts = flatten(x.type,parts); //flatten all parts with x's type
		parts = sort(parts); //sort the list of parts
		Network chX; //create a new network to return, ch(anged) X
		chX.parts = parts; //set the parts network of chX to our modified parts list
		chX.type = x.type; //set chX's type to the same as x.
		//TODO: Figure out what to do with chX.value
		return chX;
}
