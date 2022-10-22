#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <time.h>


using namespace std;

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
int placeholder;


template <class T>
struct Node
{
    T value;
    int height;
    Node<T>* nodes[2]; //0 left, 1 right
    Node(T _value) {value = _value; nodes[0] = nodes[1] = 0; height = 1;}
};

template <class T>
class AVL
{
    Node<T>* Root(){return root;}

    int Altura(Node<T>* p) { //Retorna altura 

        if (p->nodes[0] && p->nodes[1]) {
            if (p->nodes[0]->height < p->nodes[1]->height)
                return p->nodes[1]->height + 1;
            else return  p->nodes[0]->height + 1;
        }
        else if (p->nodes[0] && p->nodes[1] == NULL) {
            return p->nodes[0]->height + 1;
        }
        else if (p->nodes[0] == NULL && p->nodes[1]) {
            return p->nodes[1]->height + 1;
        }
        return 0;
    }
    int bf(Node<T>* n) { //Balance Factor
        if (n->nodes[0] && n->nodes[1]) {
            return n->nodes[0]->height - n->nodes[1]->height;
        }
        else if (n->nodes[0] && n->nodes[1] == NULL) {
            return n->nodes[0]->height;
        }
        else if (n->nodes[0] == NULL && n->nodes[1]) {
            return -n->nodes[1]->height;
        }
    }

    Node<T>* RLL(Node<T>* n) {
        Node<T>* p;
        Node<T>* q;
        p = n;
        q = p->nodes[0];
        p->nodes[0] = q->nodes[1];
        q->nodes[1] = p;
        return q;
    }
    Node<T>* RRR(Node<T>* n) {
        Node<T>* p;
        Node<T>* q;
        p = n;
        q = p->nodes[1];
        p->nodes[1] = q->nodes[0];
        q->nodes[0] = p;
        return q;
    }
    Node<T>* RRL(Node<T>* n) {
        Node<T>* p;
        Node<T>* q;
        Node<T>* aux;
        p = n;
        q = p->nodes[1];
        aux = p->nodes[1]->nodes[0];

        p->nodes[1] = aux->nodes[0];
        q->nodes[0] = aux->nodes[1];
        aux->nodes[0] = p;
        aux->nodes[1] = q;

        return aux;
    }
    Node<T>* RLR(Node<T>* n) {
        Node<T>* p;
        Node<T>* q;
        Node<T>* aux;
        p = n;
        q = p->nodes[0];
        aux = p->nodes[0]->nodes[1];

        p->nodes[0] = aux->nodes[1];
        q->nodes[1] = aux->nodes[0];
        aux->nodes[1] = p;
        aux->nodes[0] = q;

        return aux;
    }
    bool brep; //bool replace

public:
    
    Node<T>* root;
    AVL(){ root = 0; brep = 0;}
    ~AVL() { delete root; }

    bool Find(T x, Node<T>**& p);  //Search
    Node<T>* insert(Node<T>* r, T data);
    void Ins(T x);                 //Insert
    bool Delete(T x);              //Delete
    Node<T>** Rep(Node<T>** p);    //Replace
    void InOrder(Node<T>* n);
    void LevelOrder(Node<T>* n);
    int MaxDepth(Node<T>* n);   //Profundidad
    void Print(); //Llama InOrder

    void print_aux(Node<T>* n);
    void Print_fila(const Node<T>* n, int height, int depth);
    void Get_Line(const Node<T>* n, int depth, vector<int>& vals);  
};

//INSERT
template <class T>
Node<T>* AVL<T>::insert(Node<T>* r, T data) { //Raiz y valor, incluye balanceo

    if (r == NULL) {
        Node<T>* n;
        n = new Node<T>(data);
        n->value = data;
        r = n;
        r->nodes[0] = r->nodes[1] = NULL;
        r->height = 1;
        return r;
    }
    else {  //Find position
        if (data < r->value)
            r->nodes[0] = insert(r->nodes[0], data);
        else
            r->nodes[1] = insert(r->nodes[1], data);
    }

    r->height = Altura(r);

    if (bf(r) == 2 && bf(r->nodes[0]) == 1) {
        r = RLL(r);
    }
    else if (bf(r) == -2 && bf(r->nodes[1]) == -1) {
        r = RRR(r);
    }
    else if (bf(r) == -2 && bf(r->nodes[1]) == 1) {
        r = RRL(r);
    }
    else if (bf(r) == 2 && bf(r->nodes[0]) == -1) {
        r = RLR(r);
    }
    return r;
}

template <class T>
void AVL<T>::Ins(T x)
{
    root = insert(root, x);
}

// FIND
template <class T>
bool AVL<T>::Find(T x, Node<T>**& p)
{
    for (p = &root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));

    return *p != 0;
}

//DELETE
template <class T>
Node<T>** AVL<T>::Rep(Node<T>** p) //Replace
{
    Node<T>** q;
    for (q = &(*p)->nodes[!brep]; (*q)->nodes[brep]; q = &(*q)->nodes[brep]);
    brep = !brep;
    return q;
}

template <class T>
bool AVL<T>::Delete(T x)
{
    Node<T>** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        Node<T>** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    Node<T>* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

template <class T>
void AVL<T>::InOrder(Node<T>* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    std::cout << n->value << " ";
    InOrder(n->nodes[1]);
}

template <class T>
void AVL<T>::LevelOrder(Node<T>* n)
{   
    if (!root) return;
    
    queue< Node<T>* > q;
    
    for (q.push(root); !q.empty(); q.pop())
    {
        cout << q.front()->value << " ";
        if (q.front()->nodes[0]) 
            q.push(q.front()->nodes[0]);
        if (q.front()->nodes[1]) 
            q.push(q.front()->nodes[1]);
    }
}

template <class T>
int AVL<T>::MaxDepth(Node<T>* n) //Profundidad del árbol
{
    if (!n) 
        return 0;
    return max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void AVL<T>::Print()
{
    InOrder(root); cout << "\n";
}

template <class T>
void AVL<T>::print_aux(Node<T>* n)
{   
    int height = MaxDepth(root);
    for (int i = 0; i < height; i++) 
        Print_fila(n, height, i); 
}

template <class T>
void AVL<T>::Print_fila(const Node<T>* n, const int height, int depth)
{
    vector<int> vec;
    vector<string> s;
    Get_Line(n, depth, vec);
    
    for (int v : vec) 
         cout << v << "   ";
    cout << endl;
}
template <class T>
void AVL<T>::Get_Line(const Node<T>* n, int depth, vector<int>& vals)
{
    if (depth <= 0 && n != nullptr) {
        vals.push_back(n->value);
        return;
    }
    if (n->nodes[0] != nullptr)
        Get_Line(n->nodes[0], depth - 1, vals);
    else if (depth - 1 <= 0)
        vals.push_back(placeholder);
    if (n->nodes[1] != nullptr)
        Get_Line(n->nodes[1], depth - 1, vals);
    else if (depth - 1 <= 0)
        vals.push_back(placeholder);
}

int main() {

    AVL<int> A;
    cout << "AVL TREE  A"<<endl;

    A.Ins(50); 
    A.Ins(40); 
    A.Ins(80); 
    A.Ins(30); 
    A.print_aux(A.root); cout << endl;
    A.Ins(43); 
    A.Ins(60); 
    A.Ins(95); 
    A.print_aux(A.root); cout << endl;
    A.Ins(20); 
    A.Ins(35); 
    A.Ins(73); 
    A.print_aux(A.root); cout << endl;
    A.Ins(90); 
    A.Ins(99); 
    A.Ins(10); 
    A.print_aux(A.root); cout << endl;
    A.Ins(28); 
    A.Ins(70);

    A.print_aux(A.root); cout << endl;

    A.Delete(50); 
    //A.Print();
    cout << endl;
    A.print_aux(A.root); cout << endl;

    Node<int>** p;
    cout << A.Find(50, p) << endl;
    cout << A.Find(70, p) << endl;

    vector<int> ns = { 1000,10000,100000,1000000 };

    unsigned t0, t1;

    
    srand(time(NULL));

    // /*
    for (int x = 0; x < ns.size(); x++)
    {
        t0 = clock();
        AVL<int> B;
        cout << "AVL TREE  B" << endl;
        for (int i = 0; i < ns[x]; i++)
        {
            int num = rand() % ns[x];
            B.Ins(num);
        }
        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);
        cout << "Execution Time of " << ns[x] << " :" << time << endl;
    }
    // */
}
