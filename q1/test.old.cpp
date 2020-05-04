#include "tree.hpp"
#include <stack>

void nodeInsert(tree_node *a,tree_node *n);

int main(int argc, char* argv[]){
		tree_node *a = new tree_node; //1
		cin>>a->value;
		while(cin){
				tree_node *n = new tree_node;
				cin>> n->value;
				nodeInsert(a,n);
		}
		cout<<tree_balance(a)<<endl;
}

void nodeInsert(tree_node *a,tree_node *n){
		if(a->value>n->value){
				if(a->left==nullptr){
						a->left=n;
				}
				else{
						nodeInsert(a->left,n);
				}
		}
		else{
				if(a->right==nullptr){
						a->right = n;
				}
				else{
						nodeInsert(a->right,n);
				}
		}
}
