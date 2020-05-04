#include "network.hpp"
#include <iostream>

Network flatten(const Network &parts);
vector<Network> sort(const Network &parts);

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

bool operator<(const Network &a, const Network &b){ //applied assuming both a and b have been flattened
		if(a.type==b.type&&is_primitive(a)){ //if a and b both have the same type and are both primitive
				return (a.value<b.value); //return a bool indicating whether b's value is greater than a's
		}
		else if(is_primitive(a)){ //if a and b are primitive but don't have the same type
				return(a.type<b.type); //return whether a's type is less than b's - from readme this should match with the spec
		}
		else if(a.type==b.type){ //if a and b are both either series or parallel
				vector<Network> sa = sort(a.parts);
				vector<Network> sb = sort(b.parts);
				if(sa.parts.size()>sb.parts.size()){
						for(int i = 0;i<sb.size();i++){
								if(sa(i)<sb(i)){
										return true;
								}
						}
						if(a.type=='|'){
								return false;
						}
						else if(a.type=='&'){
								return true;
						}
				}
				else if(sa.parts.size()<sb.parts.size()){
						for(int i = 0;i<sa.size();i++){
								if(sa(i)<sb(i)){
										return true;
								}
						}
						if(a.type=='|'){
								return true;
						}
						else if(a.type=='&'){
								return false;
						}
				}
				else{ //if a and b have the same number of parts
						for(int i = 0;i<sa.size();i++){
								if(sa(i)<sb(i)){
										return true;
								}
						}
						return false;
				}
		}
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

Network flatten(const Network &x){
		Network chX; //create a modifiable network
		chX.type = x.type;
		for(Network n : x.parts){ //for each network in x
				if(is_primitive(n)){ //if n is a primitive network
						chX.parts.push_back(n); //add the component to chx
				}
				else if(x.type != n.type){ //if the subnetwork has a different type (one of series or parallel) to x
						chX.parts.push_back(flatten(n)); //flatten the subnetwork and add it to chx
				}
				else{ //if the subnetwork has the same type as x
						for(Network n0:n.parts){ //for each subnetwork in n
								if(is_primitive(n0)){ //if n0 is a primitive network
										chX.parts.push_back(n0); //add the component to chX
								}
								else{ //if n0 is not primitive
										chX.parts.push_back(flatten(n0)); //flatten n0 and add it to chX
										chX=flatten(chX);
								}
						}
				}
		}
		return chX;
}

vector<Network> sort(const vector<Network> &x){ //basic bubble sort, TODO: test when < implemented
		bool sorted = false;
		vector<Network> xMod = x;
		while(!sorted){
				sorted = true;
				for(int i = 0; i < xMod.size() - 1; i++){
						if(xMod[i+1] < xMod[i]){
								Network temp = xMod[i];
								xMod[i]=xMod[i+1];
								xMod[i+1] = temp;
								sorted = false;
						}
				}
		}
		return xMod;
}

Network canonicalise(const Network &x)
{
		Network chX; //create a new network to return, ch(anged) X
    if(is_primitive(x)){ //if x is a primitive network
				return x; //return the primitive network
		}
		chX = flatten(x); //flatten all parts with x's type
		chX.parts = sort(chX.parts); //sort the list of parts
		chX.type = x.type; //set chX's type to the same as x.
		return chX;
}
