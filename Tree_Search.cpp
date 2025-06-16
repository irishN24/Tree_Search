//Двоичные деревья поиска :
//
//Конструкторы(4), деструктор, =
//поиск узла по ключу
//добавление узла
//удаление узла
//минимум и максимум
//обход в ширину(по уровням)
//обход в высоту(на выбор : ЛПК, КЛП, КПЛ)
//
//
//По желанию :
//сумма ключей
//занести четные ключи в массив
//проверить на сбалансированность
//проверить на идеальность
//вывести листья
//и др.
#include <stdlib.h>
#include <iostream>

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
    friend class BinaryTree;
    friend class SearchTree;
};
//Класс Двоичное дерево
class BinaryTree {
protected:
    Node* root;
public:
    //конструктор по умолчанию
    BinaryTree() {
        root = nullptr;
    }
    //конструктор по n элементов
    BinaryTree(int n) {
        root = createBinaryTree(n);
    }
    Node* createBinaryTree(int n) {
        if (n == 0) {
            return nullptr;
        }
        Node* newNode = new Node(rand() % 100);
        int L_subtreeSize = n / 2;
        newNode->left = createBinaryTree(L_subtreeSize);
        newNode->right = createBinaryTree(n - 1 - L_subtreeSize);
        return newNode;
    }
    //Конструктор копирования
    BinaryTree(const BinaryTree& other);
    Node* copyTree(Node* q);
    //деструктор
    ~BinaryTree();
    void deleteTree(Node* q);
};
class Tree_Search : public BinaryTree {
public:
    Tree_Search() : BinaryTree() {}
    Tree_Search(int n);
};
BinaryTree::BinaryTree(const BinaryTree& t) {
    if (t.root == nullptr) {
        root = nullptr;
    }
    else {
        root = new Node(t.root->key);
        root->left = copyTree(t.root->left);
        root->right = copyTree(t.root->right);
    }
}
Node* BinaryTree::copyTree(Node* q) {
    if (q == nullptr) {
        return nullptr;
    }
    Node* p = new Node(q->key);
    p->left = copyTree(q->left);
    p->right = copyTree(q->right);
    return p;
}
BinaryTree::~BinaryTree()
{
    deleteTree(root);
}
void BinaryTree::deleteTree(Node* q)
{
    if (q == nullptr)
        return;
    deleteTree(q->left);
    deleteTree(q->right);
    delete q;
}
Tree_Search::Tree_Search(int n) {
     

}
int main()
{
    
}
