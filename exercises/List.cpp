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
    void insertingAtTheBeginning(const int d);
    void searchingNthFromEnd(const int number);
private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> head;
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
        std::shared_ptr<Node>  current = first;
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
        std::shared_ptr<Node>  current = first;
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

// wstawianie elementów na początku listy
 void List::insertingAtTheBeginning(const int d)
 {
         if(!first)
    {
        std::shared_ptr<Node> temp{new Node(d)};
        first = temp;
    }
    else
    {
        std::shared_ptr<Node> temp{new Node(d)};
        temp->value = d;
        temp->next = first;
        first = temp;
    }
}


//wyszukiwanie elementów od końca

void List::searchingNthFromEnd(const int number)
{
    int length = 0;
    std::shared_ptr<Node> temp = first;


    while (temp != NULL)
    {
        temp = temp->next;
        length++;
    }
    temp = first;

    if(length<=number)
    {
        std::cout<<"Nth element from the end doesn't exist."<<std::endl;
    }
    else if(length == number+1)
    {
        std::cout << temp->value << std::endl;
    }
    else
    {
        for(int iterator = 1; iterator < (length-number); iterator ++ )
            temp = temp->next;

        std::cout << temp->value << std::endl;

    }


}

int main()
{
    List lista;
    std::shared_ptr<Node> node4 {new Node(4)};
    std::shared_ptr<Node> node7 {new Node(7)};

    lista.add(node4);
    lista.add(std::make_shared<Node>(2));
    lista.add(node7);
    lista.insertingAtTheBeginning(5);
    lista.add(std::make_shared<Node>(9));

    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';


    lista.searchingNthFromEnd(4);
    lista.searchingNthFromEnd(3);
    lista.searchingNthFromEnd(2);
    lista.searchingNthFromEnd(1);
    lista.searchingNthFromEnd(0);


    return 0;
}

