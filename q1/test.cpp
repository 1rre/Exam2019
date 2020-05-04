#include "tree.hpp"
#include <stack>

string renderNode(const tree_node* n);

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
		cout << "digraph G { "<<endl;

    string rNode = renderNode(a);
		
		rNode.pop_back();
		cout<<rNode;

    cout << "}" << endl;
}

string renderNode(const tree_node* n){
		string rtn = "";
		if(n->left!=nullptr){
				rtn += ("\""+n->value+"\" -> \""+n->left->value+"\" [label=\"L\"]\n");
		}
		if(n->right!=nullptr){
				rtn += ("\""+n->value+"\" -> \""+n->right->value+"\" [label=\"R\"]\n");
		}
		if(n->right!=nullptr||n->left!=nullptr){
				rtn+="\n";
		}
		if(n->left!=nullptr){
				rtn += renderNode(n->left);
		}
		if(n->right!=nullptr){
				rtn += renderNode(n->right);
		}
		return rtn;
}
