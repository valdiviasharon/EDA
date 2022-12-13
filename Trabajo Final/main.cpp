#include <iostream>
#include <vector>
#include <time.h>
#include <thread>
#include <queue>
#include <string>
#include <iomanip>

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
    Node(T _value) { value = _value; nodes[0] = nodes[1] = 0; height = 1; }
};

template <class T>
class AVL
{
    Node<T>* Root() { return root; }

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
    Node<T>* root1;
    Node<T>* root2;
    Node<T>* root3;
    Node<T>* root4;
    Node<T>* r1;
    Node<T>* r2;

    AVL() { root = 0; brep = 0; root1 = 0; root2 = 0; root3 = 0; root4 = 0; r1 = 0; r2 = 0; }
    ~AVL() { delete root; }

    bool Find(T x, Node<T>**& p, T op);  //Search
    Node<T>* insert(Node<T>* r, T data);
    void Ins2(T x, T op);     //Insert
    void Ins(T x);                 //Insert
    bool Delete(T x, T op);              //Delete
    Node<T>** Rep(Node<T>** p);    //Replace
    void InOrder(Node<T>* n);
    void LevelOrder(Node<T>* n);
    int MaxDepth(Node<T>* n);   //Profundidad
    void Print(); //Llama InOrder
    void aumentar_altura(Node<T>* n)
    {
        if (!n) return;
        aumentar_altura(n->nodes[0]);
        n->height += 2;
        aumentar_altura(n->nodes[1]);
    }
    void join_t(T A, T B, T C)
    {
        Node<T>* n;
        n = new Node<T>(A+1);
        n->value = A+1;
        r1 = n;
        r1->nodes[0] = root1;
        r1->nodes[1] = root2;
        r1->height = 0;
        
        n = new Node<T>(C+1);
        n->value = C+1;
        r2 = n;
        r2->nodes[0] = root3;
        r2->nodes[1] = root4;
        r2->height = 0;

        n = new Node<T>(B+1);
        n->value = B+1;
        root = n;
        root->nodes[0] = r1;
        root->nodes[1] = r2;
        root->height = -1;
        aumentar_altura(root);
    }
    void concurrence(T ini, T fin, T op)
    {
        for (T i = ini; i < fin; i++)
            Ins2(i+1,op);
            
    }
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
template <class T>
void AVL<T>::Ins2(T x, T op)
{
    if(op==1)   
        root1 = insert(root1, x);
    else if(op==2)
        root2 = insert(root2, x);
    else if(op==3)
        root3 = insert(root3, x);
    else 
        root4 = insert(root4, x);
}

// FIND
template <class T>
bool AVL<T>::Find(T x, Node<T>**& p, T op)
{
    if(op==0)
        for (p = &root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    else if (op == 1)
        for (p = &root1; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    else if (op == 2)
        for (p = &root2; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    else if (op == 3)
        for (p = &root3; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    else 
        for (p = &root4; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));

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
bool AVL<T>::Delete(T x , T op)
{
    Node<T>** p;
    if (!Find(x, p, op)) return 0;

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
    int height = MaxDepth(n);
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

int main()
{
    vector<int> ns = { 1000,10000,100000,1000000,3000000,5000000,7000000,10000000,30000000 };
    //vector<int> ns = { 16 };    //,10,20,50,100 };

    unsigned t0, t1;
    srand(time(NULL));

    cout << "INSERCION\n" << endl;
    // /*
    cout << "AVL TREE  A - Secuencial " << endl;
    for (int x = 0; x < ns.size(); x++)
    {
        t0 = clock();
        AVL<int> A;

        for (int i = 0; i < ns[x]; i++)
        {
            //int num = rand() % ns[x];
            //A.Ins(num);
            A.Ins(i+1);
        }
        //A.print_aux(A.root);
        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);
        cout << "\t Execution Time of " << ns[x] << " :" << time << endl;
    }


    //int nt = thread::hardware_concurrency()/2;
    int nt = 4;
    cout << "AVL TREE  B - con threads " << endl;
    cout << "Threads : " << nt << endl;
    for (int x = 0; x < ns.size(); x++)
    {
        vector<thread> t(nt);
        
        AVL<int> B;
        int ind = 0;
        int inc = ns[x] / nt;
        t0 = clock();

        thread t_1(&AVL<int>::concurrence, ref(B), ind, ind + (inc-1),1);
        ind += inc;
        int n1 = ind-1;  // A
        thread t_2(&AVL<int>::concurrence, ref(B), ind, ind + inc,2);
        ind += inc;
        thread t_3(&AVL<int>::concurrence, ref(B), ind+1, ind + (inc-1),3);
        int n2 = ind; 
        ind += inc;
        int n3 = ind-1;
        thread t_4(&AVL<int>::concurrence, ref(B), ind, ns[x], 4);

        t_1.join();
        t_2.join(); 
        t_3.join(); 
        t_4.join();

        //B.insert()
        //cout << B.root1->value; cout << endl;
        //cout << B.root2->value; cout << endl;
        //B.print_aux(B.root1);
        //B.print_aux(B.root2);
        //B.print_aux(B.root3);
        //B.print_aux(B.root4);
        //B.join_t(n1, n2, n3);
        //B.print_aux(B.root);
        //B.Delete(4, 0);
        //B.print_aux(B.root);

        t1 = clock();

        double time = (double(t1 - t0) / CLOCKS_PER_SEC);
        cout << "\t Execution Time of " << ns[x] << " :" << time << endl;
    }


}