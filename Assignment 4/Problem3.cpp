#include <iostream>

using namespace std;

// Make the node class
class Node
{
  public:
    int data;
    Node *next;
};

int requestInteger()
{
    int input;
    std::cout << "Please enter a number (0 to finish input): \n";
    cin >> input;
    return input;
};

// The create function; returns a node point
Node *createList()
{
    // initialize the input variable
    int input = -1;
    // initialize the previousNode variable
    //Use the first input to create the starting Node
    input = requestInteger();
    Node *startingNode = new Node();
    startingNode->data = input;
    Node *previousNode = startingNode;
    //Loop through the creation of nodes.
    while (true)
    {
        input = requestInteger();
        if (input == 0)
            break;
        // create the next node using the user input
        Node *newNode = new Node();
        newNode->data = input;
        // set the next of the previous node to the newly created node.
        previousNode->next = newNode;
        // set the newNode to the previous node to continue the loop.
        previousNode = newNode;
    }
    // set the last node's pointer to null
    previousNode->next = NULL;
    // return the result
    return startingNode;
}

void printList(Node *startingNode)
{
    cout << startingNode->data << " ";
    Node *nextNode = startingNode->next;
    while (nextNode)
    {
        cout << nextNode->data << " ";
        nextNode = nextNode->next;
    }
    cout << endl;
}

Node *findMiddleNode(Node *start)
{ //finds the center node of the linked list
    Node *lower_pointer = start;
    Node *upper_pointer = start;
    while (true)
    {
        if (upper_pointer->next)
            upper_pointer = upper_pointer->next;
        else
            break;
        if (upper_pointer->next)
        {
            upper_pointer = upper_pointer->next;
            lower_pointer = lower_pointer->next;
        }
        else
            break;
    }
    return lower_pointer;
}

Node *combineTwoLists(Node *start1, Node *start2)
{
    Node *topNode;
    Node *startingNode;
    int nodeFinished = 0;

    if (start1->data < start2->data)
    {
        topNode = start1;
        if (start1->next)
            start1 = start1->next;
        else
            nodeFinished = 1;
    }
    else
    {
        topNode = start2;
        if (start2->next)
            start2 = start2->next;
        else
            nodeFinished = 2;
    }

    startingNode = topNode;

    while (nodeFinished == 0)
    {
        if (start1->data < start2->data)
        {
            topNode->next = start1;
            topNode = start1;
            if (start1->next)
                start1 = start1->next;
            else
                nodeFinished = 1;
        }
        else
        {
            topNode->next = start2;
            topNode = start2;
            if (start2->next)
                start2 = start2->next;
            else
                nodeFinished = 2;
        }
    }

    switch (nodeFinished)
    {
    case 1:
        topNode->next = start2;
        break;
    case 2:
        topNode->next = start1;
        break;
    }
    return startingNode;
}

Node **splitList(Node *start)
{
    Node **twolists = new Node *[2];
    twolists[0] = start;
    Node *middleNode = findMiddleNode(start);
    twolists[1] = middleNode->next;
    middleNode->next = NULL;
    return twolists;
}

Node *mergeSort(Node *start)
{
    if (!start->next)
    {
        return start;
    }
    else
    {
        Node **twolists = splitList(start);
        Node *node1 = mergeSort(twolists[0]);
        Node *node2 = mergeSort(twolists[1]);
        start = combineTwoLists(node1, node2);
    }
    return start;
}

int main()
{
    Node *node1 = createList();
    cout << "Original list: ";
    printList(node1);
    cout << "Sorted list: ";
    printList(mergeSort(node1));

    return 0;
}