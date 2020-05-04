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
				for(Network x : c.parts){ //for each subnetwork in c
						rtn += ((float)1)/(impedance(x,omega)); //add (impedance of subnetwork)⁻¹ to the return value
				}
				return ((float)1)/rtn; //return (the return value)⁻¹
		}
}

vector<complex<float>> transfer_function(const Network &v1, const Network &v2, const vector<float> &omega)
{
    vector<complex<float>> res;
		for(float freq : omega){ //for each frequency value
				complex<float> n1 = impedance(v1, freq); //set v1's impedance at a given omega
				complex<float> n2 = impedance(v2, freq); //set v2's impedance at a given omega
				complex<float> tf = n2/(n1+n2); //the transfer function of n1 & n2 given the assumption in errata.md is made
				res.push_back(tf); //add the value of the transfer function at omega to the corresponding place in res
		}
    return res;
}

vector<float> make_log10_space(float xLo, float xHi, int points)
{
    vector<float> res;
		float logLo = log10(xLo);
		float logHi = log10(xHi);
		float interval = (logHi-logLo)/((float)(points-1));
		for(int i = 0; i< points;i++){
				res.push_back(pow(10, logLo+interval*i));
		}
    return res;
}
