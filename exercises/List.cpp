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
    std::shared_ptr<Node> insertAtTheBeginning(std::shared_ptr<Node> temp);
    std::shared_ptr<Node> searchElement(int number);
private:
    std::shared_ptr<Node> first;
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
        first->prev = nullptr;
        first->next = nullptr;
        tail = first;
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
        node->next = nullptr;
        tail = node;
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
std::shared_ptr<Node>  List::insertAtTheBeginning(std::shared_ptr<Node> temp)
 {
    if(!first)
    {
        first = temp;
        first->next = nullptr;
        first->prev = nullptr;
    }
    else
    {
        temp->next = first;
        first->prev = temp;
        first = temp;
        first->prev = nullptr;
    }
    return first; 
}

// szukanie elementu od konca 
std::shared_ptr<Node>  List::searchElement(const int number)
 {
    std::shared_ptr<Node> temp = tail;
    while (temp != nullptr)
    {
        if(temp->value == number)
        {
            std::cout<<"szukana wartosc: "<<temp->value<<std::endl;
            return temp;
        }
        else
        {
            temp = temp->prev;
        }
    }  
    std::cout<<"Nie znaleziono elementu o wartosci "<<number<<std::endl;
    return temp;
}

int main()
{
    List lista;
    std::shared_ptr<Node> node4 {new Node(4)};
    std::shared_ptr<Node> node7 {new Node(7)};
    std::shared_ptr<Node> node5 {new Node(5)};

    lista.add(node4);

    /*
    Nadaj występuja wycieki pamieci, jednak pojawiają sie one gdy dodam drugi 
    i kolejny element do listy:
    
    HEAP SUMMARY:
    ==7351==     in use at exit: 304 bytes in 8 blocks
    ==7351==   total heap usage: 10 allocs, 2 frees, 74,032 bytes allocated
    ==7351== 
    ==7351== 304 (40 direct, 264 indirect) bytes in 1 blocks are definitely lost in loss record 8 of 8
    ==7351==    at 0x4C3017F: operator new(unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==7351==    by 0x108FEC: main (in /home/monika/Coders-School_kurs_cpp/memory_management/sforkowane/memory_management/exercises/l)
    ==7351== 
    ==7351== LEAK SUMMARY:
    ==7351==    definitely lost: 40 bytes in 1 blocks
    ==7351==    indirectly lost: 264 bytes in 7 blocks
    */

    lista.add(std::make_shared<Node>(2));
    lista.add(node7);
    lista.insertAtTheBeginning(node5); 
    lista.add(std::make_shared<Node>(9));

    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';

    lista.searchElement(5);

    return 0;
}

