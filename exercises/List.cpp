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
    std::shared_ptr<Node> prev;
    int value;
};

class List
{
public:
    List();
    void add(std::shared_ptr<Node> node);
    std::shared_ptr<Node> get(const int value);
    std::shared_ptr<Node> insertAtTheBeginning(const int d);
    std::shared_ptr<Node> searchNthFromEnd(const int number);
    std::shared_ptr<Node> searchElement(int number);
private:
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
};

List::List() :
    first(nullptr)
{}

void List::add(std::shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        head = first->prev;
    }
    else
    {
        std::shared_ptr<Node>  current = first;
        while(current->next)
        {
            current = current->next;
        }
        current->next = node;
        node->prev = current;
        tail = node;
        cout<<"Prev: "<<node->prev->value<<endl;
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
std::shared_ptr<Node>  List::insertAtTheBeginning(const int d)
 {
    if(!first)
    {
        std::shared_ptr<Node> temp{new Node(d)};
        first = temp;
        first->prev = head;
        first->next = nullptr;
    }
    else
    {
        std::shared_ptr<Node> temp{new Node(d)};
        temp->next = first;
        first = temp;
        first->prev = head;
    }
    return first;
    
}


//wyszukiwanie elementów od końca

std::shared_ptr<Node>  List::searchNthFromEnd(const int number)
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
    return temp;


}

// szukanie elementu od konca 
std::shared_ptr<Node>  List::searchElement(const int number)
 {
    int length = 0;
    std::shared_ptr<Node> temp = first;
    while (temp != NULL)
        {
            temp = temp->next;
            length++;
        }  
    temp=tail;

    if (length == 0)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    else
    {
        while(temp->value != number && length>1)
        {
            temp = temp->prev;
            length--;
        }
        if(temp->value == number)
            return temp;
        else
            return nullptr;      
    } 
}

int main()
{
    List lista;
    std::shared_ptr<Node> node4 {new Node(4)};
    std::shared_ptr<Node> node7 {new Node(7)};

    lista.add(std::make_shared<Node>(5));
    lista.add(node4);
    lista.add(std::make_shared<Node>(2));
    lista.add(node7);
   // lista.insertAtTheBeginning(5);   <- funkcja "serchElement" nie działa wraz z elementami
   //                                     wstawianymi przy uzyciu "insertAtTheBeginning" ale
   //                                     nie jestem w stanie odkryć gdzie jest bład
    lista.add(std::make_shared<Node>(9));

    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';


    lista.searchElement(5);
 


    return 0;
}

