//Двоичные деревья поиска :
//Конструкторы, деструктор, =
//поиск узла по ключу
//добавление узла
//удаление узла
//минимум и максимум
//обход в ширину(по уровням)
//обход в высоту(на выбор : ЛПК)
//
//По желанию :
//сумма ключей
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <queue>

using namespace std;

//класс Узел
class Node {
    int key;
    Node* left;
    Node* right;
public:
    //Конструктор
    Node(int k = 0, Node* l = nullptr, Node* r = nullptr) {
        key = k;
        left = l;
        right = r;
    }
    friend class Search_B_Tree;
};
class Search_B_Tree {
    Node* root;
    Node* copy(Node* q);                //копирование узла
    void clear(Node* q);                //удаление
    Node* find_Node(Node* q, int k);    //найти узел
    Node* insert_Node(Node*& q, int k); //вставить узел
    Node* delete_Node(Node* q, int k);  //удаление узла
    Node* min_Node(Node* q);            //минимальный узел
    Node* max_Node(Node* q);            //максимальный узел
    void print(Node* q, int h);         //вывод
    void LPK(Node* q);                  //ЛПК
    int sum_Keys(Node* q);              //сумма ключей
public:
    Search_B_Tree(): root(nullptr){}        //конструктор по умолчанию
    Search_B_Tree(int n);                   //конструктор по числу
    Search_B_Tree(const Search_B_Tree& t);  //конструктор копирования
    ~Search_B_Tree() {                      //деструктор
        clear(root);
    }                                       //оператор =
    Search_B_Tree& operator=(const Search_B_Tree& t);
    bool Find(int k);                       //поиск узла
    void Insert(int k);                     //добавить узел
    void Remove(int k);                     //Удаление узла
    int Min();                              //Минимум
    int Max();                              //Максимум
    void level_traversal();                 //Обход в ширину
    void LPK_traversal();                   //Обход в глубину
    int Sum();                              //Сумма ключей
    void Print();                           //Вывод дерева
    int get_key();
};
int Search_B_Tree::get_key(){
    return root->key;
}
Node* Search_B_Tree::copy(Node* q) {
    if (q == nullptr) {
        return nullptr;
    }
    Node* p = new Node(q->key);
    p->left = copy(q->left);
    p->right = copy(q->right);
    return p;
}
void Search_B_Tree::clear(Node* q) {
    if (q == nullptr) {
        return;
    }
    clear(q->left);
    clear(q->right);
    delete q;
}
Node* Search_B_Tree::find_Node(Node* q, int k) {
    if (q == nullptr || q->key == k) {
        return q;
    }
    Node* tmp = root;
    while(tmp && tmp->key != k){
        if(k < tmp->key){
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    }
    return tmp;
}
Node* Search_B_Tree::insert_Node(Node*& q, int k) {
    if (q == nullptr) {
        q = new Node(k);
        return q;
    }
    Node* tmp = q;
    Node* parent = nullptr;
    while(tmp != nullptr){
        parent = tmp;
        if(k == tmp->key){
            return tmp;
        }
        else if(k < tmp->key){
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    }
    Node* newNode = new Node(k);
    if (k < parent->key) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    return newNode;
}
Node* Search_B_Tree::delete_Node(Node* q, int k) {
    if (q == nullptr) {
        return q;
    }
    if (k < q->key) {
        q->left = delete_Node(q->left, k);
    }
    else if(k > q->key){
        q->right = delete_Node(q->right, k);
    }
    else {
        if (q->left == nullptr) {
            Node* tmp = q->right;
            delete q;
            return tmp;
        }
        else if (q->right == nullptr) {
            Node* tmp = q->left;
            delete q;
            return tmp;
        }
        Node* tmp = min_Node(q->right);
        q->key = tmp->key;
        q->right = delete_Node(q->right, tmp->key);
    }
    return q;
}
Node* Search_B_Tree::min_Node(Node* q) {
    while (q && q->left) {
        q = q->left;
    }
    return q;
}
Node* Search_B_Tree::max_Node(Node* q) {
    while (q && q->right) {
        q = q->right;
    }
    return q;
}
void Search_B_Tree::print(Node* q, int h) {
    if (q == nullptr) {
        return;
    }
    print(q->right, h + 3);
    for (int i = 0; i < h; i++) {
        cout << "  ";
    }
    cout.width(2);
    cout << q->key << "\n";
    print(q->left, h + 3);
}
void Search_B_Tree::LPK(Node* q) {
    if (q == nullptr) {
        return;
    }
    LPK(q->left);
    LPK(q->right);
    cout << q->key << " ";
}
int Search_B_Tree::sum_Keys(Node* q) {
    if (q == nullptr) {
        return 0;
    }
    return q->key + sum_Keys(q->left) + sum_Keys(q->right);
}
Search_B_Tree::Search_B_Tree(int n) {
    root = nullptr;
    for (int i = 0; i < n; i++) {
        Insert(rand() % 100);
    }
}
Search_B_Tree::Search_B_Tree(const Search_B_Tree& t) {
    root = copy(t.root);
}
Search_B_Tree& Search_B_Tree::operator=(const Search_B_Tree& t) {
    if (this != &t) {
        clear(root);
        root = copy(t.root);
    }
    return *this;
}
bool Search_B_Tree::Find(int k) {
    return find_Node(root, k) != nullptr;
}
void Search_B_Tree::Insert(int k) {
    insert_Node(root, k);
}
void Search_B_Tree::Remove(int k) {
    root = delete_Node(root, k);
}
int Search_B_Tree::Min() {
    Node* mini = min_Node(root);
    if (mini) {
        return mini->key;
    }
    else {
        return -1;
    }
}
int Search_B_Tree::Max() {
    Node* maxi = max_Node(root);
    if (maxi) {
        return maxi->key;
    }
    else {
        return -1;
    }
}
void Search_B_Tree::level_traversal() {
    if (root == nullptr) {
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* tmp = q.front();
        q.pop();
        cout << tmp->key << " ";
        if (tmp->left) {
            q.push(tmp->left);
        }
        if (tmp->right) {
            q.push(tmp->right);
        }
    }
    cout << "\n";
}
void Search_B_Tree::LPK_traversal() {
    LPK(root);
    cout << "\n";
}
int Search_B_Tree::Sum() {
    return sum_Keys(root);
}
void Search_B_Tree::Print() {
    if (root == nullptr) {
        cout << "The tree is empty!\n";
        return;
    }
    print(root, 0);
    cout << "\n";
    cout << "\n";
}
int main() {
    srand(time(0));

    Search_B_Tree tree1;
    Search_B_Tree tree2(20);
    Search_B_Tree tree3(tree2);

    tree1 = tree3;

    cout << "Tree1 structure:" << "\n";
    tree1.Print();
    cout << "Tree2 structure:" << "\n";
    tree2.Print();
    cout << "Tree3 structure:" << "\n";
    tree3.Print();

    cout << "--------------------------------------------------------------------\n";

    int k = 5;
    for (int i = 0; i <= k; i++) {
        int n = rand() % 100;
        cout << "n = " << n << "\n";
        tree1.Insert(n);
    }
    cout << "Tree1 structure after insert n:" << "\n";
    tree1.Print();

    cout << "--------------------------------------------------------------------";

    cout << "\nIn-order traversal: ";
    tree1.level_traversal();

    cout << "LPK traversal: ";
    tree1.LPK_traversal();

    cout << "--------------------------------------------------------------------";

    cout << "\nMin: " << tree1.Min() << "\n";
    cout << "Max: " << tree1.Max() << "\n";
    cout << "Sum: " << tree1.Sum() << "\n";

    cout << "--------------------------------------------------------------------";

    int f = rand() % 100;
    cout << "\nSearch for " << f << ":\n";
    if (tree1.Find(f)) {
        cout << "Found!\n";
    }
    else {
        cout << "Not found!\n";
    }

    cout << "--------------------------------------------------------------------\n";
    int r = rand() % 100;
    tree1.Insert(r);
    cout << "Tree1 structure after insert " << r << ":\n";
    tree1.Print();

    tree1.Remove(tree1.get_key());
    cout << "After removing "<<":\n";
    tree1.Print();

    return 0;
}
