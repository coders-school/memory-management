#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

struct EmptyListError : runtime_error
{
    EmptyListError() : runtime_error("List is empty") {}
};

class Node
{
public:
    Node(const int v)
        : next(nullptr)
        , value(v)
    {}

    shared_ptr<Node> next;
    int value;
};

class List
{
public:
    void add(shared_ptr<Node> node);
    shared_ptr<Node> get(const int value);

private:
    shared_ptr<Node> first = nullptr;
};

void List::add(shared_ptr<Node> node)
{
    if(node == first)
    {
        cerr << "Node already added: " << node->value << '\n';
        return;
    }
    if(!first)
    {
        first = node;
    }
    else
    {
        shared_ptr<Node> current = first;
        while(current->next)
        {
            if(current->next == node)
            {
                cerr << "Node already added: " << node->value << '\n';
                return;
            }
            current = current->next;
        }
        current->next = node;
    }
}

shared_ptr<Node> List::get(const int value)
{
    if(!first)
    {
        throw EmptyListError{};
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

    try
    {
        auto node = lista.get(1);
    }
    catch (const runtime_error & re)
    {
        cerr << re.what() << '\n';  // possible Windows console order problem - endl
    }

    auto node4 = make_shared<Node>(4);
    auto node7 = make_shared<Node>(7);

    lista.add(node4);
    lista.add(make_shared<Node>(2));
    lista.add(node7);
    lista.add(node4);
    lista.add(make_shared<Node>(9));

    try
    {
        auto node = lista.get(1);
        if (node)
        {
            cout << node->value << '\n';
        }
    }
    catch (const runtime_error & re)
    {
        cerr << re.what() << '\n';
    }

    return 0;
}
