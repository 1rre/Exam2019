#include "network.hpp"

void print_parts(const Network &n)
{
    if(is_primitive(n)){ //if n is a primitive component
        cout<<n.type<<n.value<<endl; //print n's type then its value
    }else{
        for(unsigned i=0; i<n.parts.size(); i++){ //if there are any subnetworks of n
            print_parts(n.parts[i]); //recursively print the parts of the subnetworks
        }
    }
}

int main()
{
    Network n; //declare a new network, n

    cin >> n; //read n from cin

    print_parts(n); //print each part of the network
}
