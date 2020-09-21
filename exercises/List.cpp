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

    std::shared_ptr<Node> next;
    int value;
};

class List
{
public:
    List();
    void add(std::shared_ptr<Node> node);
    std::shared_ptr<Node> get(const int value);

private:
    std::shared_ptr<Node> first;
};

List::List() :
    first(nullptr)
{}

void List::add(std::shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
    }
    else
    {
        std::shared_ptr<Node> current = first;
        while(current->next)
        {
            current = current->next;
        }
        current->next = node;
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
    List lista;
    std::shared_ptr<Node> node4 = std::make_shared<Node>(4);
    std::shared_ptr<Node> node7 = std::make_shared<Node>(4);

    lista.add(node4);
    lista.add(std::make_shared<Node>(2));
    lista.add(node7);
    lista.add(std::make_shared<Node>(9));
    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';

    return 0;
}

