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
    int deep=0;
    Node(){}
    Node(const int& value_, Node<Type>* right_,Node<Type>* left_, Node<Type>* parent_, Color color_, const int& deep_):
            value(value_),right(right_), left(left_), parent(parent_), color(color_),  deep(deep_) {}
};

template<typename Type>
void func(Node<Type>* node, int beg, int end, const std::vector<Type>& v){
    if(beg>end){
        return;
    }
    int id=(beg+end)/2;
    Node<Type>* tmp=new Node<Type>(v[id], NULL, NULL, node, BLACK, node->deep+1);
    if(tmp->value>node->value){
        node->right=tmp;
    }else{
        node->left=tmp;
    }
    func(tmp, id+1, end, v);
    func(tmp, beg, id-1, v);
}

int bin_approx_(const int& N){
    int c=1;
    while(true){
        if(c>=N){
            break;
        }
        c*=2;
    }
    return c;
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
    RED_BLACK_TREE(const std::vector<Type>& v) {
        root = new Node<Type>(v[v.size() / 2], NULL, NULL, NULL, BLACK, 0);
        func(root, v.size() / 2 + 1, v.size() - 1, v);
        func(root, 0, v.size() / 2 - 1, v);
        std::queue<Node<Type> *> q;
        q.push(root);
        int N = bin_approx_(v.size() + 1);
        int true_N = bin_approx_(v.size());
        for (int i = 0; i < v.size(); i++) {
            if (q.front()->left) {
                q.push(q.front()->left);
            }
            if (q.front()->right) {
                q.push(q.front()->right);
            }
            if (i >= N / 2 - 1 and v.size() != true_N - 1) {
                q.front()->color = RED;
            }
            q.pop();
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
    void insert(const Type& value){
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
    Node<Type>* get_root(){
        return root;
    }
};
void test_3(const int& m){
    std::vector<int> v;
    for(int i=0; i<m; i++){
        v.push_back(i);
    }
    RED_BLACK_TREE<int> rbt = RED_BLACK_TREE(v);
    std::queue<Node<int>*> q;
    q.push(rbt.get_root());
    int N=bin_approx_(v.size()+1);
    int true_N=bin_approx_(v.size());
    int counter=0;
    int tmp_deep=0;
    int red_counter=0;
    for(int i=0; i<v.size(); i++){
        if(q.front()->deep>tmp_deep){
            tmp_deep=q.front()->deep;
            std::cout<<counter<<'\n';
            counter=0;
        }
        if(q.front()->left) {
            q.push(q.front()->left);
        }
        if(q.front()->right){
            q.push(q.front()->right);
        }
        if(i >= N/2-1 and v.size()!=true_N-1){
            if(q.front()->color==RED) {
                red_counter++;
            }
        }
        q.pop();
        counter++;
    }
    std::cout<<counter<<' '<<'\n';
    std::cout<<"nodes were repainted: "<<red_counter;
}
int main(){
    test_3(3215356);
    return 0;
}