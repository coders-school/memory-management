#include <iostream>
#include <memory>

using namespace std;

class Node
{
public:
    Node(const int v) :
        next(nullptr),
        prev(nullptr),
        value(v)
    {}
    shared_ptr<Node> next;
    shared_ptr<Node> prev;
    //Node* next;
    int value;
    virtual ~Node() {};
};

class List
{
public:
    List();
    void add(shared_ptr<Node> node);
    shared_ptr<Node> get(const int value);
    void addFirstElements(shared_ptr<Node> node); // add first elements
   // ~List(){clean()};
private:
    shared_ptr<Node> first;
    //Node* first;
};

List::List() :
    first(nullptr)
{}

//void List::add(Node* node)
void List::add(shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
    }
    else
    {
        shared_ptr<Node> current = first;
        while(current->next)
        {
            current = current->next;
        }
        current->next = node;
    }
}

void List::addFirstElements(shared_ptr<Node> node)
{
    auto temp = make_shared<Node>(node->value);
    //<Node> current;
    //int v = 0;
     if(!first)
    {
        first = temp;
    }
    else
    {
        first->prev = temp;
        temp->next = first;
        first = temp;
    }
    
}


shared_ptr<Node> List::get(const int value)
{
    if(!first)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    else
    {
        shared_ptr<Node> current = first;
        do
        {
            if(current->value == value)
            {
                cout << "Found value " << current->value << endl;
                return current;
            }
            else
            {
                cout << "Going through " << current->value << endl;
                current = current->next;
            }
        } while(current);
        cout << "Not found: value " << value << endl;
        return nullptr;
    }
}


int main()
{
    List lista;
    shared_ptr<Node> node2 {new Node(2)};
    shared_ptr<Node> node4 {new Node(4)};
    shared_ptr<Node> node7 {new Node(7)};
    auto tempValue = make_shared<Node>(3);
    lista.addFirstElements(tempValue);
    lista.add(node4);
    lista.add(make_shared<Node>(2));
    lista.add(node7);
    lista.add(make_shared<Node>(9));


    
    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';
    return 0;
    
}

