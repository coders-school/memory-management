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

    shared_ptr<Node> next, prev;
    int value;
};

class DoubleList
{
public:
    DoubleList();
    void add(shared_ptr<Node> node);
    shared_ptr<Node> get(const int value);

private:
    shared_ptr<Node> first, last;
};

DoubleList::DoubleList() :
    first(nullptr),
    last(nullptr)
{}

void DoubleList::add(shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        node->next = first;
        first->prev = node;
        first = node;
    }
}

shared_ptr<Node> DoubleList::get(const int value)
{
    if(!last)
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
                current = current->prev;
            }
        } while(current);
        cout << "Not found: value " << value << endl;
        return nullptr;
    }
}

int main()
{
    DoubleList list;
    shared_ptr<Node> node4 {new Node(4)};
    shared_ptr<Node> node7 {new Node(7)};

    list.add(node4);
    list.add(make_shared<Node>(2));
    list.add(node7);
    list.add(make_shared<Node>(9));
    auto node = list.get(9);

    if (node)
        cout << node->value << '\n';

    return 0;
}

