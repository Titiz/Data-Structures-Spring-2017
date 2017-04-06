#include <iostream>
#include <random>

using namespace std;

class Node
{
  public:
    double key;
    Node *left, *right, *parent;
};

class BST
{
  private:
    void postorderDelete(Node *node1); // used for deletion of BST // used for removal
    Node *root = NULL;                 // useful to have a reference to the root of the tree.
  public:
    BST();
    ~BST();
    void insert(double key);
    int max_depth = 0;
};

void BST::postorderDelete(Node *ptr)
{ // Goes through the bst is postorder and deletes the nodes one by one.
    if (ptr)
    {
        postorderDelete(ptr->left);
        postorderDelete(ptr->right);
        delete ptr;
    }
}

BST::BST(){
    // unsure as to what should go here.
};

BST::~BST()
{ // calls function to delete all connections of the node.
    postorderDelete(root);
}

void BST::insert(double key) //iterative approach to inserting a node. Alters the max depth of the BST
{
    int depth = 0; // depth variable used to see if the new addition has increased depth
    Node *node = new Node();
    node->key = key;
    if (!root)
    {
        root = node;
        return;
    }
    Node *pointer = root;
    while (true)
    {
        depth++;
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
    if (depth > max_depth) // Change of max_depth if necessary
        max_depth = depth;
}

// Random insertion function:
// Generates n random numbers between 0.0, 1.0 and inserts them into the BST.
int randomInsertions(int n)
{
    BST bst;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < n; i++)
    {
        double number_to_insert = distribution(generator);
        bst.insert(number_to_insert);
    }
    return bst.max_depth;
}

int main()
{
    for (int k = 10; k < 26; k++)
    {
        int depth = randomInsertions(pow(2, k));
        cout << "Number of insertions: 2^" << k << " | Resulting depth dk: " << depth << " | Ratio dk/k: " << (float)depth / (float)k << endl;
    }

    return 0;
}