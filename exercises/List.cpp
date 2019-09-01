#include <iostream>
#include <memory>

using namespace std;

class Node
{
public:
    Node(const int v) :
        next(nullptr),
        value(v)
    {}

    shared_ptr<Node> next;
    weak_ptr<Node> prev;

    int value;
    virtual ~Node() {};
};

class List
{
public:
    List();
    void add(shared_ptr<Node> node);
    shared_ptr<Node> getFirst(const int value);
    shared_ptr<Node> getLast(const int value);
    void addFirstElements(shared_ptr<Node> node);


private:
    shared_ptr<Node> first;
    shared_ptr<Node> last;
    
};

List::List() :
    first(nullptr),
    last(nullptr)
{}


void List::add(shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = first;
    }
    else
    {
        shared_ptr<Node> current = first;
        while(current->next)
        {
            current = current->next;
        }
        current->next = node;

        last = node;
        last->prev = current;
    }
}

void List::addFirstElements(shared_ptr<Node> node)
{
    auto temp = make_shared<Node>(node->value);

     if(!first)
    {
        first = temp;
    }
    else
    {
        temp->next = first;
        first = temp;
    }
    
}


shared_ptr<Node> List::getFirst(const int value)
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

shared_ptr<Node> List::getLast(const int value)
{
    if(!first)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    else
    {
        shared_ptr<Node> current = last;
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
                current = current->prev.lock();
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
    lista.addFirstElements(make_shared<Node>(5));
    lista.add(make_shared<Node>(9));


    
    auto node = lista.getFirst(1);

    if (node)
        cout << node->value << '\n';

    node = lista.getLast(2);

    if (node)
        cout << node->value << '\n';

    return 0;
    
}

