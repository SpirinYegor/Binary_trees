#include <iostream>
#include <cstdlib>
#include <algorithm>

template <typename c, typename v>
struct node{
	v value;
	c clue;
	unsigned int height;
	node* left;
	node* right;
};

template <typename key, typename value>
class AVL
{
	node<key, value>* root;
	int height(node<key,value>* p){
		if(p == NULL){
			return 0;
		}
		return p->height;
	}
	node<key, value>* minValue(node<key,value>* leaf)
	{
		auto current = leaf;
		while(current->left != NULL)
			current = current->left;
		return current;
	}
	node<key, value>* erase(node <key, value>* leaf, key k){
		if (leaf == NULL){
			return leaf;
		}
		if(k < leaf->clue)
			leaf->left = erase(leaf->left, k);
		else if(k > leaf->clue)
				leaf->right = erase(leaf->right, k);
			else{
				if((leaf->left == NULL) || (leaf->right == NULL)){
					node<key, value>* temp = leaf->left ? leaf->left : leaf->right;
					if(temp == NULL)
					{
						temp = leaf;
						leaf = NULL;
					}else *leaf = *temp;
					delete temp;
				}else{
					node<key, value>* temp = minValue(leaf->right);
					leaf->clue = temp->clue;
					leaf->value = temp->value;
					leaf->right = erase(leaf->right, temp->clue);
				}
			}
		if(leaf == NULL)
		return leaf;
		leaf->height = 1 + std::max(height(leaf->left), height(leaf->right));
		return balance(leaf);
	}
	node<key, value>* insert(key k, value v, node<key, value>* leaf){
		if (leaf == NULL){
				leaf = new node<key, value>;
				leaf->value = v;
				leaf->clue = k;
				leaf->left = NULL;
				leaf->right = NULL;
				leaf->height = 1;
				return leaf;
			}
		if(k < leaf->clue){
			leaf->left = insert(k, v, leaf->left);
		}else{
			if(k > leaf->clue){
				leaf->right = insert(k, v, leaf->right);
			}else{
				leaf->value = v;
			}
		}
		leaf->height = 1 + std::max(height(leaf->left), height(leaf->right));
		return balance(leaf);
	}
	node<key, value>* find(key n, node<key, value>* leaf){
		if(leaf->clue == n){
			return leaf;
		}else{
			if(n < leaf->clue){
				return find(n, leaf->left);
			}else{
				return find(n, leaf->right);
			}
		}
		return NULL;
	}
	node<key,value>* rotateLeft(node<key,value>* a){
		auto b = a->right;
		a->right = b->left;
		b->left = a;
		unsigned int k, l, m;
		if(a->right == NULL) k = 0;
		else k = a->right->height;
		if(a->left == NULL) l = 0;
		else l = a->left->height;
		if(b->left == NULL) m = 0;
		else m = b->right->height;
		a->height = std::max(k, l) + 1;
		b->height = std::max(a->height, m) + 1;
		return b;
	}
	node<key,value>* rotateRight(node<key,value>* a){
		auto b = a->left;
		a->left = b->right;
		b->right = a;
		unsigned int k, l, m;
		if(a->right == NULL) k = 0;
		else k = a->right->height;
		if(a->left == NULL) l = 0;
		else l = a->left->height;
		if(b->left == NULL) m = 0;
		else m = b->left->height;
		a->height = std::max(k, l) + 1;
		b->height = std::max(a->height, m) + 1;
		return b;
	}
	node<key, value>* balance(node<key,value>* p){
		if(bfactor(p) == 2){
			if( bfactor(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if(bfactor(p) == -2){
			if(bfactor(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p;
	}
	int bfactor(node<key, value>* p){
		if(p == NULL){
			return 0;
		}else{
			int r = 0;
			int l = 0;
			if(p->right == NULL) r = 0;
			else r = p->right->height;
			if(p->left == NULL) l = 0;
			else l = p->left->height;
			return r-l;
		}
	}
	void destruct(node<key, value>* leaf){
		if(leaf->left != NULL) destruct(leaf->left);
		if(leaf->right != NULL) destruct(leaf->right);
		delete leaf;
	}
	public:
		AVL(){
			root = NULL;
		};
		~AVL(){
			destruct(root);
		}
		void insert(key k, value v){
			root = insert(k, v, root);
		};
		node<key, value>* find(key n){
			if (root->clue == n){
				return root;
			}else{
				if(root->left == NULL && root->right == NULL){
					return NULL;
				}else{
					if(n < root->clue){
						return find(n, root->left);
					}else{
						return find(n, root->right);
					}
				}
			}
			return 0;
		}
		void erase(key k){
			root = erase(root, k);
		}
		void print(node<key, value>* root){
			if(root != NULL){
				std::cout << root->value << " ";
				print(root->left);
				print(root->right);
			}
		}
};
