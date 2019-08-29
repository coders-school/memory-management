
#include "LinkedList.hpp"

LinkedList::LinkedList() :
    first(nullptr)
{}



void LinkedList::addToTheEnd(std::shared_ptr<Node> node)
{

    if(!addIfFirst(node))
    {
        std::shared_ptr<Node> current = first;
        if(isNodePresent(node)) {
            return;
        }

        while(current->next) {
            current = current->next;
        }

        node->previous = std::weak_ptr<Node>(current);
        current->next = std::shared_ptr<Node>(node);
        last = current->next;
    }
}

void LinkedList::addToTheFront(std::shared_ptr<Node> node)
{
    if(addIfFirst(node)) {
        return;
    }
    if(isNodePresent(node)) {
        return;
    }

    node->next = first;
    first->previous = std::weak_ptr<Node>(node);
    first = node;    
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
    return std::shared_ptr<Node>(nullptr);
}

std::shared_ptr<Node> LinkedList::backSearch(const int value)
{
    assertListNotEmpty();
    
    std::shared_ptr<Node> current = last.lock();

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
    return std::shared_ptr<Node>(nullptr);
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
        first = std::shared_ptr<Node>(node);
        last = std::weak_ptr<Node>(first);
        return true;
    }
    return false;
}

bool LinkedList::isNodePresent(std::shared_ptr<Node> node)
{
        std::shared_ptr<Node> current = first;

        while(current)
        {
            if(current == node) {
                std::cout << "Node " << node->value << " has been added" << std::endl;
                return true;
            }
            current = current->next;
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

    std::shared_ptr<Node> node7(new Node(7));

    lista.addToTheEnd(std::make_shared<Node>(4));
    lista.addToTheFront(std::make_shared<Node>(2)); //add to the fornt
    lista.addToTheEnd(node7);
    lista.addToTheEnd(node7); // Message that this node is present
    lista.addToTheEnd(std::make_shared<Node>(9));

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

