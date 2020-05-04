#include "network.hpp"

bool evaluate_parallel(const Network &a, const Network &b);
bool evaluate_series(const Network &a, const Network &b);

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


Network canonicalise(const Network &x)
{
    // TODO
}
