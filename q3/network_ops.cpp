#include "network.hpp"

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
