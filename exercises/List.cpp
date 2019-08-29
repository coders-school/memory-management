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

    void add(std::unique_ptr<Node> node);
    Node* get(const int value);

private:
    unique_ptr<Node> first;
};

List::List() :
    first(nullptr)
{}

void List::add(std::unique_ptr<Node> ptrNode)
{
    if(ptrNode == nullptr) {
        return;
    }

    if(!first)
    {
        first = unique_ptr<Node>(ptrNode.release());
    }
    else
    {
        Node* current = first.get();

        while(current->next.get())
        {
            current = current->next.get();
        }

        current->next = unique_ptr<Node>(ptrNode.release());
    }
}

Node* List::get(const int value)
{
    if(!first)
    {
        throw EmptyListError("List is empty!");
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


    std::unique_ptr<Node> node4(new Node(4));
    std::unique_ptr<Node> node7(new Node(7));
    std::unique_ptr<Node> node2(new Node(2));
    std::unique_ptr<Node> node9(new Node(9));


    lista.add(std::move(node4));
    lista.add(std::move(node4));
    lista.add(std::move(node2));
    lista.add(std::move(node7));
    lista.add(std::move(node9));
    lista.add(std::make_unique<Node>(10));

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

