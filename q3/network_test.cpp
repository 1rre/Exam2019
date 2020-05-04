#include "network.hpp"

int main(int argc, char* argv[]){
		Network n,n0;
		cin>>n>>n0;
		vector<float> omega;
		for(float i = 1; i<10;i++){
				omega.push_back(i);
		}
		for(complex<float> x :transfer_function(n,n0,omega)){
				cout<<x<<endl;
		}
}
