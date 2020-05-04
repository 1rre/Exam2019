#include "tree.hpp"
#include <stack>


int main(int argc, char* argv[]){
		tree_node *a = new tree_node;
		cin>>a->value;
		while(cin){
				tree_node *b = new tree_node;
				cin>>b->value;
				if(b->value!=""){
						tree_insert(a,b);
				}
		}
		cout<<tree_balance(a)<<endl;
}
