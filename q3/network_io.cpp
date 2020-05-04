#include "network.hpp"

string buildOutput(const Network &n);

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

vector<Network> create_test_networks()
{
    return {
        R(1),
        C(1),
        L(1)
        // TODO Make sure there are at least ten test-cases
    };
}
