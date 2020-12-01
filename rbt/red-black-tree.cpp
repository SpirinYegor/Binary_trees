#include <iostream>
#include <vector>
#include <queue>

enum Color{
    RED,
    BLACK
};
template<typename Type>
struct Node {
    Type value;
    Node *right;
    Node *left;
    Node *parent;
    Color color;
};
template<typename Type>
void recurcive_constructor(Node<Type>* ROOT, typename std::vector<Type>::iterator begin,
        typename std::vector<Type>::iterator end){
    if(begin==end){
        return;
    }else{
        Node <Type>* tmp=new Node<Type>;
        tmp->color=BLACK;
        tmp->left=NULL;
        tmp->right=NULL;
        auto it=(begin+end)/2;
        tmp->value=*it;
        if(!ROOT){
            tmp->parent=NULL;
            ROOT=tmp;
        }else {
            tmp->parent = ROOT;
        }
        if(ROOT->value>*it){
            ROOT->right=tmp;
            recurcive_constructor(tmp, ++it, end);
        }else {
            ROOT->left = tmp;
            recurcive_constructor(tmp, begin, --it);
        }

    }
}
template<typename Type>
class RED_BLACK_TREE{

private:

    Node<Type>* root;
    Node<Type>* GetGrandParent(Node<Type>* node)const{
        if(!node){
            return NULL;
        }
        if(node->parent){
            return node->parent->parent;
        }else{
            return NULL;
        }
    }
    Node<Type>* GetBrother(const Node<Type>* node)const{
        if(node->parent) {
            if(node->parent==node->parent->left){
                return node->left;
            }else{
                return node->right;
            }
        }else{
            return NULL;
        }
    }


    void RotateLeft(Node<Type>* node) {
        Node<Type>* nnew = node->right;
        Node<Type>* p = node->parent;

        node->right = nnew->left;
        nnew->left = node;
        node->parent = nnew;
        if (node->right != NULL) {
            node->right->parent = node;
        }
        if (p != NULL) {
            if (node == p->left) {
                p->left = nnew;
            } else if (node == p->right) {
                p->right = nnew;
            }
        }
        nnew->parent = p;
    }
    void RotateRight(Node<Type>* node) {
        Node<Type>* nnew = node->left;
        Node<Type>* p = node->parent;
        node->left = nnew->right;
        nnew->right = node;
        node->parent = nnew;


        if (node->left != NULL) {
            node->left->parent = node;
        }
        if (p != NULL) {
            if (node == p->left) {
                p->left = nnew;
            } else if (node == p->right) {
                p->right = nnew;
            }
        }
        nnew->parent = p;
    }
    void insert_(Node<Type>*& root, Node<Type>* node) {
        Node<Type>* t_node = root;
        Node<Type>* t_parent = NULL;

        while (t_node) {
            t_parent = t_node;
            if (node->value > t_node->value ) {
                t_node = t_node->right;
            }
            else {
                t_node = t_node->left;
            }
        }
        node->parent = t_parent;
        if (t_parent)
            if (node->value  > t_parent->value )
                t_parent->right = node;
            else
                t_parent->left = node;
        else
            root = node;
        node->color = RED;
        RepairInsertion(root, node);
    }
    void RepairInsertion(Node<Type>*& root, Node<Type>* node) {
        Node<Type>* p = node->parent;
        while (node != RED_BLACK_TREE::root and p->color == RED) {
            Node<Type>* g = GetGrandParent(node);
            if (g->left == p) {
                Node<Type>* uncle = g->right;
                if (uncle and uncle->color == RED) {
                    p->color = BLACK;
                    uncle->color = BLACK;
                    g->color = RED;
                    node = g;
                    p = node->parent;
                }
                else {
                    if (p->right == node) {
                        RotateLeft(p);
                        std::swap(node, p);
                    }
                    RotateRight(g);
                    g->color = RED;
                    p->color = BLACK;
                    break;
                }
            }else {
                Node<Type>* uncle = g->left;
                if (uncle and uncle->color == RED) {
                    g->color = RED;
                    p->color = BLACK;
                    uncle->color = BLACK;
                    node = g;
                    p= node->parent;
                }else {
                    if (p->left == node) {
                        RotateRight(p);
                        std::swap(p, node);
                    }
                    RotateLeft(g);
                    p->color = BLACK;
                    g->color = RED;
                    break;
                }
            }
        }
        root->color = BLACK;
    }
    void erase_(Node<Type>* node){
        Node<Type>* c, *p;
        Color color;
        if(node->left and node->right) {
            Node<Type> *replace = node->right;
            while (replace->left) {
                replace = replace->left;
            }
            if (node->parent) {
                if(node->parent->left==node){
                    node->parent->left=replace;
                }else{
                    node->parent->right=replace;
                }
            }else{root=replace;}
            c= replace->right;
            p = replace->parent;
            color = replace->color;
            if(p==node) {
                p = replace;
            }else{
                if(c){
                    c->parent=p;
                }
                p->left=c;
                replace->right=node->right;
                node->right->parent=replace;
            }
            replace->parent=node->parent;
            replace->color=node->color;
            replace->left=node->left;
            node->left->parent=replace;
            if(color==BLACK){
                EraseRepair(node);
            }delete node;
            return;
        }
        if(node->left){
            c=node->left;
        }else{
            c=node->right;
        }
        p=node->parent;
        color=node->color;
        if(c){
            c->parent=p;
        }
        if(p){
            if(node==p->left){
                p->left=c;
            }else{
                p->right=c;
            }
        }else{
            this->root=c;
        }
        if(color==BLACK){
            if(c and c->color==RED){
                c->color=BLACK;
            }else if(c and c->color==BLACK) {
                EraseRepair(node);
            }
        }
        delete node;
    }
   void EraseRepair(Node<Type>* node) {

       if (node->parent) {
           delete_case2(node);
       }

   }
   void delete_case2(Node<Type>* node) {

       Node<Type> *b = GetBrother(node);
       if (b) {
           if (b->color == RED) {
               node->parent->color = RED;
               b->color = BLACK;
               if (node == node->parent->left) {
                   RotateLeft(node->parent);
               } else {
                   RotateRight(node->parent);
               }
           } else {
               delete_case3(node);
           }
       }
   }
   void delete_case3(Node<Type>* node) {

       Node<Type> *b = GetBrother(node);
       if (b and b->left) {
           if (node->parent->color == BLACK and b->color == BLACK and b->left->color == BLACK and
               b->right->color == BLACK) {
               b->color == RED;
               EraseRepair(node->parent);
           } else {
               delete_case4(node);
           }
       }
   }
   void delete_case4(Node<Type>* node) {

       Node<Type> *b = GetBrother(node);
       if (b and b->left) {
           if (node->parent->color == RED and b->color == BLACK and b->left->color == BLACK and
               b->right->color == BLACK) {
               b->color == RED;
               node->parent->color = BLACK;
           } else {
               delete_case5(node);
           }
       }
   }
   void delete_case5(Node<Type>* node) {

       Node<Type> *b = GetBrother(node);
       if (b and b->left and b->right) {
           if (b->color == BLACK) {
               if (node == node->parent->left and b->right->color == BLACK and b->left->color == RED) {
                   b->color = RED;
                   b->left->color = BLACK;
                   RotateRight(b);
               }
           } else if (node == node->parent->right and b->left->color == BLACK and b->right->color == RED) {
               b->color = RED;
               b->right->color = BLACK;
               RotateLeft(b);
           }
           delete_case6(node);
       }
   }
   void delete_case6(Node<Type>* node) {

       Node<Type> *b = GetBrother(node);
       if (b and b->left) {
           b->color = node->parent->color;
           node->parent->color = BLACK;

           if (node == node->parent->left) {
               b->right->color = BLACK;
               RotateLeft(node->parent);
           } else {
               b->left->color = BLACK;
               RotateRight(node->parent);
           }
       }
   }
     Node<Type>* find_(Node<Type>* node, const int& value) const {
         if (!node or node->value == value) {
             return node;
         }
         if (node->value > value) {
             return find_(node->left, value);
         } else {
             return find_(node->right, value);
         }
     }
     void uproot(Node<Type>* node){
        if(node){
            if(node->left) {
                uproot(node->left);
            }
            if(node->right) {
                uproot(node->right);
            }
            delete node;
        }else{
            return;
        }
    }
public:
    RED_BLACK_TREE(){
        root=NULL;
    }
    RED_BLACK_TREE(const std::vector<Type>& v){
        root=NULL;
        recurcive_constructor(root, v.begin(), v.end()--);
       int approx_elements=1;
       while(1){
            if(approx_elements-1>=v.size()){
                break;
            }
            approx_elements*=2;
       }
       if(approx_elements!=v.size()){
            std::queue<Node<Type>> q;
            q.push(root);
            for(int i=0; i<v.size(); i++){
                if(i>approx_elements/2-1){
                    q.front()->color=RED;
                    q.pop();
                }else {
                    q.push(q.front()->left);
                    q.push(q.front()->right);
                    q.pop();
                }
            }
        }
    }
    ~RED_BLACK_TREE(){
        uproot(root);
    }
    Node<Type>* find(const int& value) const{
        return find_(root, value);
    }
    void erase(const int& value){
        if(find_(root, value)){
            erase_(find_(root, value));
        }
    }
    void insert(const Type& value) {
        if(!root){
            root=new Node<Type>;
            root->value=value;
            root->right=NULL;
            root->left=NULL;
            root->parent=NULL;
            root->color=BLACK;
        }else{
            Node<Type>* tmp= new Node<Type>;
            tmp->value=value;
            tmp->right=NULL;
            tmp->left=NULL;
            tmp->parent=NULL;
            tmp->color=RED;
            insert_(root, tmp);
        }
    }

};
