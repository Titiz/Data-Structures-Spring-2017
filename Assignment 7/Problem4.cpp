#include <iostream>
using namespace std;

template <typename S>
class Node
{
  public:
    S key;
    Node<S> *left, *right, *parent;
};

template <typename T>
class BST
{
  private:
    Node<T> *root;

    // The following are helper functions added to facilitate
    // the implementation of the public functions.
    void destroy(Node<T> *ptr);
    Node<T> *findMin(Node<T> *ptr);
    void insert(Node<T> *ptr, T key);
    Node<T> *find(Node<T> *ptr, T key);
    void printPreorder(Node<T> *ptr);
    void printInorder(Node<T> *ptr);
    void printTree(T *A, bool *B, Node<T> *ptr, int n);
    Node<T> *newnode(T key);
    void remove(Node<T> *ptr);
    int depth(Node<T> *ptr);

  public:
    BST();
    ~BST();
    void insert(T key);
    void remove(T key);
    Node<T> *find(T key);
    void printPreorder();
    void printInorder();
    void printTree();
    int depth();
    void rotate(Node<T> *parent, Node<T> *child);
};

template <typename T>
BST<T>::BST()
{
    root = nullptr;
}

template <typename T>
void BST<T>::destroy(Node<T> *ptr)
{
    if (ptr != nullptr)
    {
        destroy(ptr->left);
        destroy(ptr->right);
        delete ptr;
    }
}

template <typename T>
BST<T>::~BST()
{
    destroy(root);
}

template <typename T>
int BST<T>::depth(Node<T> *ptr)
{
    int l, r;
    if (ptr == nullptr)
        return -1; // depth of empty tree is -1
    l = depth(ptr->left);
    r = depth(ptr->right);
    if (l > r)
        return l + 1;
    return r + 1;
}

template <typename T>
int BST<T>::depth()
{
    return depth(root);
}

template <typename T>
void BST<T>::printPreorder(Node<T> *ptr)
{
    if (ptr != nullptr)
    {
        cout << ptr->key << " ";
        printPreorder(ptr->left);
        printPreorder(ptr->right);
    }
}

template <typename T>
void BST<T>::printPreorder()
{
    cout << "Preorder: ";
    printPreorder(root);
    cout << endl;
}

template <typename T>
void BST<T>::printInorder(Node<T> *ptr)
{
    if (ptr != nullptr)
    {
        printInorder(ptr->left);
        cout << ptr->key << " ";
        printInorder(ptr->right);
    }
}

template <typename T>
void BST<T>::printInorder()
{
    cout << "Inorder: ";
    printInorder(root);
    cout << endl;
}

template <typename T>
Node<T> *BST<T>::find(Node<T> *ptr, T key)
{
    if (ptr == nullptr)
        return nullptr;
    if (key < ptr->key)
        return find(ptr->left, key);
    if (key > ptr->key)
        return find(ptr->right, key);
    return ptr;
}

template <typename T>
Node<T> *BST<T>::find(T key)
{
    return find(root, key);
}
template <typename T>
Node<T> *BST<T>::newnode(T key)
{
    Node<T> *n = new Node<T>;
    n->key = key;
    n->left = n->right = nullptr;
    return n;
}

template <typename T>
void BST<T>::insert(Node<T> *ptr, T key)
{
    // assumes ptr!=nullptr
    Node<T> *n;
    if (key < ptr->key)
    {
        if (ptr->left == nullptr)
        {
            n = newnode(key);
            n->parent = ptr;
            ptr->left = n;
        }
        else
        {
            insert(ptr->left, key);
        }
    }
    else
    { // key >= ptr->data
        if (ptr->right == nullptr)
        {
            n = newnode(key);
            n->parent = ptr;
            ptr->right = n;
        }
        else
        {
            insert(ptr->right, key);
        }
    }
}

template <typename T>
void BST<T>::insert(T key)
{
    if (root == nullptr)
    {
        root = newnode(key);
        root->parent = nullptr;
    }
    else
    {
        insert(root, key);
    }
}

template <typename T>
Node<T> *BST<T>::findMin(Node<T> *ptr)
{
    Node<T> *p;
    for (p = ptr; ptr != nullptr; ptr = ptr->left)
    {
        p = ptr;
    }
    return p;
}

template <typename T>
void BST<T>::remove(Node<T> *ptr)
{

    Node<T> *parent, *succ, **pp;

    if (ptr == nullptr)
        return;

    parent = ptr->parent;

    if (ptr == root)
    { // i.e. parent == nullptr
        pp = &root;
    }
    else
    {
        if (ptr == parent->left)
        {
            pp = &(parent->left);
        }
        else
        {
            pp = &(parent->right);
        }
    }

    if (ptr->left == nullptr && ptr->right == nullptr)
    {
        *pp = nullptr;
        delete ptr;
    }
    else if (ptr->left == nullptr)
    {
        *pp = ptr->right;
        ptr->right->parent = parent;
        delete ptr;
    }
    else if (ptr->right == nullptr)
    {
        *pp = ptr->left;
        ptr->left->parent = parent;
        delete ptr;
    }
    else
    {
        succ = findMin(ptr->right);
        ptr->key = succ->key;
        remove(succ);
    }
}

template <typename T>
void BST<T>::remove(T key)
{
    remove(find(key));
}

template <typename T>
void BST<T>::printTree(T *A, bool *B, Node<T> *ptr, int n)
{
    if (ptr != nullptr)
    {
        int mid = (n - 1) / 2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTree(A, B, ptr->left, mid);
        printTree(A + (mid + 1), B + (mid + 1), ptr->right, mid);
    }
}

template <typename T>
void BST<T>::printTree()
{
    char space[3] = "  ";
    int d = depth();
    int n = (1 << (d + 1)) - 1; // n = 2^(d+1)-1

    T *A = new T[n];
    bool *B = new bool[n];
    for (int i = 0; i < n; ++i)
        B[i] = false;

    printTree(A, B, root, n);

    cout << "\nTree:" << endl;
    for (int t = (n + 1) / 2; t > 0; t = t / 2)
    {
        for (int j = 0; j < n; j++)
        {
            if (((j + 1) % t == 0) && B[j])
            {
                cout << A[j];
                B[j] = false;
            }
            else
            {
                cout << space;
            }
        }
        cout << endl;
    }
    cout << endl;
    delete[] A;
    delete[] B;
}

template <typename T>
void BST<T>::rotate(Node<T> *parent, Node<T> *child) {
    if (child == parent->left) {
        child->parent = parent->parent;
        parent->parent->left = child;
        parent->parent = child;
        parent->left = child->right;
        child->right = parent;
    } 
    else if (child == parent->right) {
        child->parent = parent->parent;
        parent->parent->right = child;
        parent->parent = child;
        parent->right = child->left;
        child->left = parent;
    }
}

int main()
{
BST<int> bst = BST<int>();
bst.insert(100);
bst.insert(70);
bst.insert(80);
bst.insert(40);
bst.insert(20);
bst.insert(50);

Node<int> *parent = bst.find(70);
Node<int> *child = bst.find(40);

bst.printTree();

bst.rotate(parent, child);

bst.printInorder();
bst.printTree();

}
