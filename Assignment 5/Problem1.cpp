#include <iostream>
#include <stack>

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
    void postorderDelete(Node<T> *node1);            // used for deletion of BST
    void transplant(Node<T> *node1, Node<T> *node2); // used for removal
    int getDepth(Node<T> *node);                     // used for the depth function
    void preorder(Node<T> *node);                    // used for the printPreorderfunction
    Node<T> *min(Node<T> *root);                     // finds the minimum in subtree
    Node<T> *root = NULL;                            // useful to have a reference to the root of the tree.
  public:
    BST();
    ~BST();
    void insert(T key);
    void remove(T key);
    Node<T> *find(T key);
    void printPreorder();
    int depth();
};

template <typename T>
BST<T>::BST()
{ // unsure as to what should go here.
    cout << "A binary search tree was created!" << endl;
};

template <typename T>
BST<T>::~BST()
{ // calls function to delete all connections of the node.
    postorderDelete(root);
    cout << "BINARY SEARCH TREE DELETED" << endl;
}

template <typename T>
void BST<T>::insert(T key) //iterative approach to inserting a node.
{
    Node<T> *node = new Node<T>();
    node->key = key;
    if (!root)
    {
        root = node;
        return;
    }
    node->key = key;
    Node<T> *pointer = root;
    while (true)
    {
        if (pointer->key > key)
        {
            if (pointer->left)
            {
                pointer = pointer->left;
            }
            else
            {
                pointer->left = node;
                node->parent = pointer;
                break;
            }
        }
        else
        {
            if (pointer->right)
                pointer = pointer->right;
            else
            {
                pointer->right = node;
                node->parent = pointer;
                break;
            }
        }
    }
}

template <typename T>
Node<T> *BST<T>::find(T key)
{
    Node<T> *node = root;
    while (node)
    {
        if (key == node->key)
            return node;
        else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    if (!node)
        cout << "NODE WITH THE GIVEN VALUE NOT FOUND" << endl;
    return node;
}

template <typename T>
void BST<T>::preorder(Node<T> *ptr)
{ //recursively preorder traversal that prints out the values at each node.
    if (!ptr)
        return;
    cout << ptr->key << " ";
    preorder(ptr->left);
    preorder(ptr->right);
}

template <typename T>
void BST<T>::postorderDelete(Node<T> *ptr)
{ // Goes through the bst is postorder and deletes the nodes one by one.
    if (ptr)
    {
        postorderDelete(ptr->left);
        postorderDelete(ptr->right);
        delete ptr;
    }
}

template <typename T>
Node<T> *BST<T>::min(Node<T> *node)
{ // finds the minimum of a subtree
    if (node)
    {
        while (node->left)
        {
            node = node->left;
        }
    }
    return node;
}

template <typename T>

void BST<T>::remove(T key)
{ // remove function as explained in cormen
    Node<T> *node = find(key);
    if (node)
    {
        if (!node->left)
            transplant(node, node->right);
        else if (!node->right)
            transplant(node, node->left);
        else
        {
            Node<T> *successor = min(node->right);
            if (successor->parent != node)
            {
                transplant(successor, successor->right);
                successor->right = node->right;
                successor->right->parent = successor;
            }
            transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
        }
        delete node;
    }
}

template <typename T>
void BST<T>::transplant(Node<T> *node1, Node<T> *node2)
{ // transplant function as explained in Cormen.
    if (!node1->parent)
        root = node2;
    else if (node1 == node1->parent->left)
        node1->parent->left = node2;
    else
        node1->parent->right = node2;
    if (node2)
        node2->parent = node1->parent;
}

template <typename T>
void BST<T>::printPreorder()
{
    preorder(root);
    cout << endl;
}

template <typename T>
int BST<T>::getDepth(Node<T> *pointer)
{ // Recurisve function to geth the depth of the tree
    if (!pointer)
        return 0;
    int left_height = getDepth(pointer->left);
    int right_height = getDepth(pointer->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

template <typename T>
int BST<T>::depth()
{
    return getDepth(root);
}

int main()
{
    return 0;
}