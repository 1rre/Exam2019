#include "tree.hpp"
#include <stack>

int main(int argc, char* argv[]){
		tree_node *a = new tree_node;
		tree_node *b = new tree_node;
		tree_node *c = new tree_node;
		tree_node *d = new tree_node;
		a->value = 5;
		b->value = 3;
		c->value = 6;
		d->value = 9;
		a->left = b;
		b->left = c;
		b->right = d;
		cout<<tree_balance(a);
}
