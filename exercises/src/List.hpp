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
    friend bool operator==(const Node &lhs, const Node &rhs);
    std::weak_ptr<Node> previous;
    std::shared_ptr<Node> next;
    int value;
};

bool operator==(const Node &lhs, const Node &rhs)
{
    return (lhs == rhs);
}

class List
{
public:
    List();
    void add(std::shared_ptr<Node> node);
    void add_front(std::shared_ptr<Node> node);
    std::shared_ptr<Node> find_back(const int value);
    std::shared_ptr<Node> get(const int value);
    std::shared_ptr<Node> getFirst() const;
    

private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
};

List::List() :
    first(nullptr),
    last(nullptr)
{}

std::shared_ptr<Node> List::getFirst() const
{
    return first;
}

std::shared_ptr<Node> List::find_back(const int value)
{
    if(!first)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    else
    {
        std::shared_ptr<Node> current = last;
        do
        {
            if(current->value == value)
            {
                std::cout << "Found value: " << current->value << std::endl;
                return current;
            }
            else
            {
                std::cout << "Going through: " << current->value << std::endl;
                current = current->previous.lock();
            }
        } while (current);
        std::cout << "Not found value: " << value << std::endl;
        return nullptr;
    }

}

void List::add_front(std::shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        node->next = first;
        first->previous = node;
        first = node;
    }

}

void List::add(std::shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = node;
    }
    else
    {
        std::shared_ptr<Node> current = first;
        while(current->next)
        {
            current = current->next;
        }
        current->next = node;
        node->previous = current;
        last = node;
    }
}

std::shared_ptr<Node> List::get(const int value)
{
    if(!first)
    {
        cout << "List is empty!" << endl;
        return nullptr;
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
