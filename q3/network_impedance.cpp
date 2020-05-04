#include "network.hpp"

complex<float> impedance(const Network &c, float omega)
{
    if(c.type=='R'){
        return {c.value, 0};

    }else if(c.type=='C'){
        return {0, -((float)1)/(omega*c.value) };

    }else if (c.type=='L'){
        return {0, omega*c.value}; //if c is an inductor
    }
    else if(c.type == '|'){ //if c is a series network
				complex<float> rtn = {0,0}; //create an empty return float
				for(Network x : c.parts){ //for each subnetwork in c
						rtn += impedance(x,omega); //a
				}
				return rtn;
		}
		else{ //if c is a parallel network
				complex<float> rtn = {0,0};
				for(Network x : c.parts){
						rtn += ((float)1)/(impedance(x,omega));
				}
				return ((float)1)/rtn;
		}
}

vector<complex<float>> transfer_function(const Network &v1, const Network &v2, const vector<float> &omega)
{
    vector<complex<float>> res;

    // TODO

    return res;
}

vector<float> make_log10_space(float xLo, float xHi, int points)
{
    vector<float> res;

    // TODO

    return res;
}
