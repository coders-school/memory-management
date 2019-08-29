
#include "LinkedList.hpp"

LinkedList::LinkedList() :
    first(nullptr)
{}


void LinkedList::addToTheEnd(std::unique_ptr<Node> node)
{
    if(!node) {
        return;
    }

    std::shared_ptr<Node> temp(std::move(node));

    if(!addIfFirst(temp))
    {
        std::shared_ptr<Node>& current = first;

        while(current) {
            current = current->next;
        }
        
        temp->previous = current;
        current.swap(temp);
        last = current;
    }
}


void LinkedList::addToTheFront(std::unique_ptr<Node> node)
{
    if(!node) {
        return;
    }

    std::shared_ptr<Node> temp(std::move(node));

    if(addIfFirst(temp)) {
        return;
    }

    temp->next = first;
    first->previous = temp; 
    first = temp;
}


std::shared_ptr<Node> LinkedList::frontSearch(const int value)
{
    assertListNotEmpty();

    std::shared_ptr<Node> current = first;
    do
    {
        if(current->value == value)
        {
            std::cout << "Found value " << current->value << std::endl;
            return current;
        }
        else
        {
            std::cout << "Going through " << current->value << std::endl;
            current = current->next;
        }
    } while(current);

    
    std::cout << "Not found: value " << value << std::endl;
    return nullptr;
}

std::shared_ptr<Node> LinkedList::backSearch(const int value)
{
    assertListNotEmpty();
    
   std::shared_ptr<Node> current = last;

    do
    {
        if(current->value == value)
        {
            std::cout << "Found value " << current->value << std::endl;
            return current;
        }
        else
        {
            std::cout << "Going through " << current->value << std::endl;
            current = current->previous.lock();
        }

    }while(current);

    std::cout << "Not found: value " << value << std::endl;
    return nullptr;
}

void LinkedList::assertListNotEmpty()
{
    if(!first) {
        throw EmptyListError("List is empty!");
    }
}

bool LinkedList::addIfFirst(std::shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
        last = first;
        return true;
    }
    return false;
}

int main()
{
    LinkedList lista;

    try {
        auto node = lista.frontSearch(1);       //throw Empty list exception;
    } catch(const EmptyListError& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        auto node2 = lista.backSearch(1);       //throw Empty list exception;
    } catch(const EmptyListError& e) {
        std::cerr << e.what() << '\n';
    }

    std::unique_ptr<Node> node7(new Node(7));

    lista.addToTheEnd(std::make_unique<Node>(4));
    lista.addToTheFront(std::make_unique<Node>(2)); //add to the fornt
    lista.addToTheEnd(std::move(node7));
    lista.addToTheEnd(std::move(node7)); // Message that this node is present
    lista.addToTheEnd(std::make_unique<Node>(9));

    try
    {
        auto node = lista.frontSearch(1);
        auto node2 = lista.frontSearch(4);

        auto nodeB = lista.backSearch(1);
        auto nodeB2 = lista.backSearch(4);

        if (node)
            std::cout << node->value << '\n';

        if (node2)
            std::cout << node2->value << '\n';

        if (nodeB)
            std::cout << nodeB->value << '\n';

        if (nodeB2)
            std::cout << nodeB2->value << '\n';

        return 0;
    }
    catch(const EmptyListError& e) {
        std::cerr << e.what() << '\n';
    }
}

