#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

class Node
{
public:
    Node(const int v) :
        next(nullptr),
        value(v)
    {}
    
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    int value;
};

class DoubleList
{
public:
    DoubleList();
    void addOnBegin(std::unique_ptr<Node> node);
    void addOnEnd(std::unique_ptr<Node> node);
    shared_ptr<Node> getFromBegin(const int value);
    shared_ptr<Node> getFromEnd(const int value);

private:
    std::shared_ptr<Node> first, last;
};

DoubleList::DoubleList() :
    first(nullptr),
    last(nullptr)
{}

void DoubleList::addOnBegin(std::unique_ptr<Node> node)
{
    std::shared_ptr<Node> temp(std::move(node));
    if(!first)
    {
        first = temp;
        last = temp;
    }
    else
    {
        temp->next = first;
        first->prev = temp;
        first = temp;
    }
}

void DoubleList::addOnEnd(std::unique_ptr<Node> node)
{
    std::shared_ptr<Node> temp(std::move(node));
    if(!first)
    {
        first = temp;
        last = temp;
    }
    else
    {
        last->next = temp;
        temp->prev = last;
        last = temp;
    }
}

std::shared_ptr<Node> DoubleList::getFromEnd(const int value)
{
    try
    {
        if(!last)
        {
            throw std::runtime_error("before get something add something.");
        }
        else
        {
            std::shared_ptr<Node> current = last;
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
    catch (std::exception& e)
    {
        std::cout<<"Empty list! " << e.what() << std::endl;
        return nullptr;
    }
}

shared_ptr<Node> DoubleList::getFromBegin(const int value)
{
    try
    {
        if(!first)
        {
            throw std::runtime_error("before get something add something.");
        }
        else
        {
            std::shared_ptr<Node> current = first;
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
    catch (std::exception& e)
    {
        std::cout<<"Empty list! " << e.what() << std::endl;
        return nullptr;
    }
}

int main()
{
    DoubleList list1;
    std::cout<< "Adding nodes on begin. Getting nodes from end." << std::endl; 
    std::unique_ptr<Node> node4 {new Node(4)};
    std::unique_ptr<Node> node7 {new Node(7)};
    list1.addOnBegin(std::move(node4));
    list1.addOnBegin(std::make_unique<Node>(2));
    list1.addOnBegin(std::move(node7));
    list1.addOnBegin(std::make_unique<Node>(9));
    auto node1 = list1.getFromEnd(9);
    if (node1)
        cout << node1->value << '\n';

    std::cout<< "\nAdding nodes on end. Getting nodes from end." << std::endl; 
    DoubleList list2;
    std::unique_ptr<Node> node44 {new Node(44)};
    std::unique_ptr<Node> node77 {new Node(77)};
    list2.addOnEnd(std::move(node44));
    list2.addOnEnd(make_unique<Node>(22));
    list2.addOnEnd(std::move(node77));
    list2.addOnEnd(make_unique<Node>(99));
    auto node2 = list2.getFromEnd(99);
    if (node2)
        cout << node2->value << '\n';
   
    DoubleList list3;
    std::cout << "\nGetting node from empty list." << std::endl;
    auto node3 = list3.getFromEnd(1);
 
    return 0;
}

/*
Adding nodes on begin. Getting nodes from end.
Going through 4
Going through 2
Going through 7
Found value 9
9

Adding nodes on end. Getting nodes from end.
Found value 99
99

Getting node from empty list.
Empty list! before get something add something.
*/

