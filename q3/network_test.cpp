#include "network.hpp"

int main(int argc, char* argv[]){
		Network n;
		cin >> n ;
		Network _n = canonicalise(n);
		cout<<_n;
}
