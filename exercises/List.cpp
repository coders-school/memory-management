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
};

class DoubleList
{
public:
    DoubleList();
    void addOnBegin(shared_ptr<Node> node);
    void addOnEnd(shared_ptr<Node> node);
    bool checkIfDuplicate(const int value);
    shared_ptr<Node> getFromBegin(const int value);
    shared_ptr<Node> getFromEnd(const int value);

private:
    shared_ptr<Node> first, last;
};

DoubleList::DoubleList() :
    first(nullptr),
    last(nullptr)
{}

bool DoubleList::checkIfDuplicate(const int currentValue)
{
    shared_ptr<Node> current = first;
    while(current)
    {
        if (current->value == currentValue)
            return false;
        current = current->next;
    }
    return true;
}

void DoubleList::addOnBegin(shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        if (checkIfDuplicate(node->value))
        {
            node->next = first;
            first->prev = node;
            first = node;
        }
        else
            std::cout<<"Duplicate, node wasn't add."<<std::endl;
    }
}

void DoubleList::addOnEnd(shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        if (checkIfDuplicate(node->value))
        {
            last->next = node;
            node->prev = last;
            last = node;
        }
        else
            std::cout<<"Duplicate, node wasn't add."<<std::endl;
    }
}

shared_ptr<Node> DoubleList::getFromEnd(const int value)
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
            auto weakPrev = (current->prev).lock();
            if(current->value == value)
            {
                cout << "Found value " << current->value << endl;
                return current;
            }
            else
            {
                cout << "Going through " << current->value << endl;
                current = weakPrev;
            }
        } while(current);
        cout << "Not found: value " << value << endl;
        return nullptr;
    }
}

shared_ptr<Node> DoubleList::getFromBegin(const int value)
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
    DoubleList list1;
    std::cout<< "Adding nodes on begin. Getting nodes from end." << std::endl; 
    shared_ptr<Node> node4 {new Node(4)};
    shared_ptr<Node> node7 {new Node(7)};
    list1.addOnBegin(node4);
    list1.addOnBegin(make_shared<Node>(2));
    list1.addOnBegin(make_shared<Node>(2));
    list1.addOnBegin(make_shared<Node>(2));
    list1.addOnBegin(node7);
    list1.addOnBegin(make_shared<Node>(9));
    auto node1 = list1.getFromEnd(9);
    if (node1)
        cout << node1->value << '\n';

    std::cout<< "\nAdding nodes on end. Getting nodes from end." << std::endl; 
    DoubleList list2;
    shared_ptr<Node> node44 {new Node(44)};
    shared_ptr<Node> node77 {new Node(77)};
    list2.addOnEnd(node44);
    list2.addOnEnd(make_shared<Node>(22));
    list2.addOnEnd(make_shared<Node>(22));
    list2.addOnEnd(make_shared<Node>(22));
    list2.addOnEnd(node77);
    list2.addOnEnd(make_shared<Node>(99));
    list2.addOnEnd(make_shared<Node>(99));
    auto node2 = list2.getFromEnd(99);
    if (node2)
        cout << node2->value << '\n';
    
    return 0;
}

/*
Adding nodes on begin. Getting nodes from end.
Duplicate, node wasn't add.
Duplicate, node wasn't add.
Going through 4
Going through 2
Going through 7
Found value 9
9

Adding nodes on end. Getting nodes from end.
Duplicate, node wasn't add.
Duplicate, node wasn't add.
Duplicate, node wasn't add.
Found value 99
99
*/
