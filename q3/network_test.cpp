#include "network.hpp"

int main(int argc, char* argv[]){
		int points;
		float xLo,xHi;
		cin>>xLo>>xHi>>points;
		for(float f : make_log10_space(xLo,xHi,points)){
				cout<<f<<endl;
		}
}
