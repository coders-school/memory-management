
#include "LinkedList.hpp"

LinkedList::LinkedList() :
    first(nullptr)
{}


void LinkedList::addToTheEnd(std::unique_ptr<Node> node)
{
    if(!node) {
        return;
    }

    if(!addIfFirst(node))
    {
        std::shared_ptr<std::unique_ptr<Node>>& current = first;

        while(current) {
            current = current->get()->next;
        }
        
        node->previous = current;

        std::shared_ptr<std::unique_ptr<Node>> temp = std::make_shared<std::unique_ptr<Node>>(std::move(node));
        current.swap(temp);
        last = current;
    }
}


void LinkedList::addToTheFront(std::unique_ptr<Node> node)
{
    if(!node) {
        return;
    }

    if(addIfFirst(node)) {
        return;
    }

    std::shared_ptr<std::unique_ptr<Node>> temp = std::make_shared<std::unique_ptr<Node>>(std::move(node));
    
    temp->get()->next = first;
    first->get()->previous = temp; 
    first = temp;
}


std::shared_ptr<std::unique_ptr<Node>> LinkedList::frontSearch(const int value)
{
    assertListNotEmpty();

    std::shared_ptr<std::unique_ptr<Node>> current = first;
    do
    {
        if(current->get()->value == value)
        {
            std::cout << "Found value " << current->get()->value << std::endl;
            return current;
        }
        else
        {
            std::cout << "Going through " << current->get()->value << std::endl;
            current = current->get()->next;
        }
    } while(current);

    
    std::cout << "Not found: value " << value << std::endl;
    return nullptr;
}

std::shared_ptr<std::unique_ptr<Node>> LinkedList::backSearch(const int value)
{
    assertListNotEmpty();
    
   std::shared_ptr<std::unique_ptr<Node>> current = last.lock();

    do
    {
        if(current->get()->value == value)
        {
            std::cout << "Found value " << current->get()->value << std::endl;
            return current;
        }
        else
        {
            std::cout << "Going through " << current->get()->value << std::endl;
            current = current->get()->previous.lock();
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

bool LinkedList::addIfFirst(std::unique_ptr<Node>& node)
{
    if(!first)
    {
        first = std::make_shared<std::unique_ptr<Node>>(std::move(node));
        last = std::weak_ptr<std::unique_ptr<Node>>(first);
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
            std::cout << node->get()->value << '\n';

        if (node2)
            std::cout << node2->get()->value << '\n';

        if (nodeB)
            std::cout << nodeB->get()->value << '\n';

        if (nodeB2)
            std::cout << nodeB2->get()->value << '\n';

        return 0;
    }
    catch(const EmptyListError& e) {
        std::cerr << e.what() << '\n';
    }
}

