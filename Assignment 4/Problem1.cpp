#include <iostream>
#include <stdlib.h>

// The implementation from our last assignment was not optimal. Thus we have modified the implementation from the model answers:

using namespace std;

// First we implement the node class that will be used for lists:
template <typename T>
class Node
{
  public:
    T data;
    Node<T> *next;
    ;
};

// now we implement functions that will allow lists to act like stacks.
template <typename T>
T pop_from_list(Node<T> *&start)
{
    T value = start->data;
    Node<T> *deletion = start;
    start = start->next;
    delete deletion;
    return value;
}

template <typename T>
void push_to_list(Node<T> *&start, T value)
{
    Node<T> *next_node = new Node<T>();
    if (start)
    {
        next_node->data = start->data;
        next_node->next = start->next;
        start->next = next_node;
        start->data = value;
    }
    else
    {
        start = next_node;
        start->data = value;
    }
};

template <typename T>
bool isEmpty(Node<T> *start)
{
    return (start == NULL);
}

int prec(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void process(Node<double> *&D, char o)
{
    double a, b, c;
    b = pop_from_list(D);
    a = pop_from_list(D);
    if (o == '+')
        c = a + b;
    else if (o == '-')
        c = a - b;
    else if (o == '*')
        c = a * b;
    else if (o == '/')
        c = a / b;
    else
    {
        cout << "Error: Unexpected operator " << o << " .";
        exit(1);
    }
    push_to_list(D, c);
}

int main()
{
    char op, c;
    double x, u, v;
    Node<char> *C = NULL;
    Node<double> *D = NULL;

    cout << "Type an expression in infix notation and press Enter." << endl;

    while (true)
    {
        c = cin.get();
        if (c == '\n')
            break;
        else if (c == ' ')
            continue;
        else if ('0' <= c && c <= '9')
        {
            cin.putback(c);
            cin >> x;
            push_to_list(D, x); // push into operands stack
        }
        else if (c == '(' || isEmpty(C))
            push_to_list(C, c);
        else if (c == ')')
        { // pop until '(' is popped
            for (op = pop_from_list(C); op != '('; op = pop_from_list(C))
            {
                process(D, op);
            }
        }
        else
        {
            bool flag = true;
            for (op = pop_from_list(C); prec(op) >= prec(c) && op != '('; op = pop_from_list(C))
            {
                process(D, op);
                if (isEmpty(C))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                push_to_list(C, op); // un-pop the last operator
            push_to_list(C, c);      // push new operator
        }
    }
    while (!isEmpty(C))
    { // Empty operator stack
        process(D, pop_from_list(C));
    }

    if (isEmpty(D))
        push_to_list(D, 0.0);
    cout << " = " << pop_from_list(D) << endl;

    return 0;
}
