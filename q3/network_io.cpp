#include "network.hpp"
#include <ctime>

string buildOutput(const Network &n);
Network createSubNetwork();

istream &operator>>(istream &src, Network &c)
{
    c.value=0;
    c.parts.clear();

    src>>c.type;
    if(src.fail()){
        return src;
    }

    if(c.type=='R' || c.type=='C' || c.type=='L'){
        src>>c.value;
    }else if(c.type=='('){
        c.type=0;
        c.value=0;

        Network x;
        char seperator;
        src>>x>>seperator;
        assert(!src.fail());
        c.parts.push_back(x);

        while(seperator!=')'){
            assert( seperator=='&' || seperator=='|' );
            assert( c.type==0 || c.type==seperator );
            c.type=seperator;
            src>>x>>seperator;
            assert(!src.fail());

            c.parts.push_back(x);
        }

        if(c.parts.size()==1){
            c.type='&';
        }
    }

    return src;
}


ostream &operator<<(ostream &dst, const Network &c) //implement output
{
    string outMessage = buildOutput(c); //set the output message to the output builder's string generated for c
		dst<<outMessage; //output the string to dst
    return dst;
}

string buildOutput(const Network &n){
		string outMessage = ""; //create  a string to return
		if(is_primitive(n)){
				outMessage = n.type+to_string(n.value);
		}
		else{
				outMessage += "("; //add an opening bracket
				for(Network sub : n.parts){ //for each subnetwork of n
						outMessage+=buildOutput(sub); //add the output from that subnetwork to the output message
						outMessage+=n.type; //add the operator & or | between the parts
				}
				outMessage = outMessage.substr(0, outMessage.length() - 1); //remove the final char in outMessage, which would be & or |
				outMessage += ")"; //add a closing bracket
		}
		return outMessage; //return the built output
}

Network createSubNetwork(int b){
		Network rtn;
		srand(time(nullptr));
		int rnd;
		if(b==0){
				rnd = rand()%5;
		}
		else{
				rnd = rand()%3;
		}
		switch(rnd){
				case 0:{
						rtn.type = 'R'; //set the type to resistor
						rtn.value = rand()%5; //with value 1-5
						break;
				}
				case 1:{
						rtn.type = 'L'; //set the type to inductor
						rtn.value = rand()%5; //with value 1-5
						break;
				}
				case 2:{
						rtn.type = 'C'; //set the type to capacitor
						rtn.value = rand()%5+1; //with value 1-5
						break;
				}
				case 3:{
						rtn.type = '&'; //set the type to parallel
						int forRndP = rand()%3;
						for(int i=-2;i<forRndP;i++){
								rtn.parts.push_back(createSubNetwork(b-1)); //add 2-5 subnetworks
						}
						break;
				}
				case 4:{
						rtn.type = '|'; //set the type to series
						int forRndS = rand()%3;
						for(int i=-2;i<forRndS;i++){
								rtn.parts.push_back(createSubNetwork(b-1)); //add 2-5 subnetworks
						}
						break;
				}
		}
		return rtn;
}

vector<Network> create_test_networks()
{
		vector<Network> rtn;
		for(int i=0;i<100;i++){
				rtn.push_back(createSubNetwork(5)); //add 100 random networks to the return vector
		}
		return rtn;
}
