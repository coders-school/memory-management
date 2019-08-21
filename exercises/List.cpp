#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

struct EmptyListError : public runtime_error
{
    EmptyListError(string msg) : runtime_error(msg){};
};

class Node
{
public:
    Node(const int v) :
        value(v)
    {}

    unique_ptr<Node> next;
    int value;
};

class List
{
public:
    List();
    
    ~List(){};


    void add(Node* node);
    Node* get(const int value);
    bool IsPresent(Node* current, Node* testNode);

private:
    unique_ptr<Node> first;
};

List::List() :
    first(nullptr)
{}

void List::add(Node* node)
{
    if(!first)
    {
        first = unique_ptr<Node>(node);
    }
    else
    {
        Node* current = first.get();

        while(current->next.get())
        {
            current = current->next.get();
            if(IsPresent(current, node)) {
                return;
            }
        }
        
        if(IsPresent(current, node)) {
            return;
        }
        current->next = unique_ptr<Node>(node);
    }
}

Node* List::get(const int value)
{
    if(!first.get())
    {
        throw EmptyListError("List is empty!");
        return nullptr;
    }
    else
    {
        Node* current = first.get();
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
                current = current->next.get();
            }
        } while(current);
        cout << "Not found: value " << value << endl;
        return nullptr;
    }
}

bool List::IsPresent(Node* current, Node* testNode)
{
        
    if(current == testNode)
    {
        std::cout << "Node " << testNode << " has been added" << std::endl;
        return true;
    }
    return false;
}

int main()
{
    List lista;

    try
    {
        lista.get(1);
    }
    catch(const EmptyListError& e)
    {
        std::cerr << e.what() << '\n';
    }


    Node* node4 = new Node(4);
    Node* node7 = new Node(7);

    lista.add(node4);
    lista.add(node4);
    lista.add(new Node(2));
    lista.add(node7);
    lista.add(new Node(9));

    try
    {
        auto node = lista.get(1);

        if (node)
            cout << node->value << '\n';

        return 0;
    }
    catch(const EmptyListError& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}

