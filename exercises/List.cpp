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

    std::weak_ptr<Node> previous;
    std::shared_ptr<Node> next;
    int value;
};

class List
{
public:
    List();
    void add(std::shared_ptr<Node> node);
    void add_front(std::shared_ptr<Node> node);
    std::shared_ptr<Node> find_back(const int value);
    std::shared_ptr<Node> get(const int value);

private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
};

List::List() :
    first(nullptr),
    last(nullptr)
{}

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

int main()
{
    List lista2;
    auto node4 = std::make_shared<Node>(4);
    auto node7 = std::make_shared<Node>(7);
    lista2.add_front(node4);
    lista2.add_front(std::make_shared<Node>(2));
    lista2.add_front(node7);
    lista2.add_front(std::make_shared<Node>(9));
    lista2.find_back(1);

    return 0;
}

