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
    std::cout << "Please enter a number: \n";
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
	{
	    break;
	}
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

Node *Last(Node &startingNode)
{
    Node *nextNode = startingNode.next;
    while (nextNode->next)
	nextNode = nextNode->next;
    return nextNode;
}

Node *LastBefore(Node *startingNode, Node *endingNode)
{
    if (startingNode != endingNode)
    {
	Node *nextNode = startingNode->next;
	while (nextNode->next != endingNode)
	{
	    nextNode = nextNode->next;
	}
	return nextNode;
    }
    else
    {
	return startingNode;
    }
}

//void shiftValuesRight(Node& startingNode) {
//	Node* nextNode = startingNode.next;
//	while (nextNode->next) {
//		nextNode->next->data = nextNode->data;
//		nextNode = nextNode->next;
//	}
//	startingNode.data = nextNode->data;
//}

void swap(Node *i, Node *j)
{
    int tmp = i->data;
    i->data = j->data;
    j->data = tmp;
}

Node *Reverse(Node &startingNode)
{

    Node *lastNode = Last(startingNode);
    Node *i = &startingNode;
    Node *j = lastNode;
    while (true)
    {
	// switch values of last and first node.
	swap(i, j);

	j = LastBefore(i, j);
	i = i->next;

	if (i->next == j)
	{
	    swap(i, j);
	    break;
	}
	else if (i == j)
	    break;
    }
    return lastNode;
}

int main()
{
    Node *node = createList();
    cout << "ORIGINAL LIST: ";
    printList(node);
    Reverse(*node);
    cout << "REVERSED LIST: ";
    printList(node);
    return 0;
}