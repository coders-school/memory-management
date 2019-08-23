
#include "LinkedList.hpp"

LinkedList::LinkedList() :
    first(nullptr)
{}



void LinkedList::addToTheEnd(Node* node)
{

    if(!addIfFirst(node))
    {
        std::weak_ptr<Node> current = first;
        if(isNodePresent(node)) {
            return;
        }

        while(current.lock()->next) {
            current = std::weak_ptr<Node>(current.lock()->next);
        }

        node->previous = std::weak_ptr<Node>(current);
        current.lock()->next = std::shared_ptr<Node>(node);
        last = current.lock()->next;
    }
}

void LinkedList::addToTheFront(Node* node)
{
    if(addIfFirst(node)) {
        return;
    }
    if(isNodePresent(node)) {
        return;
    }
    
    std::shared_ptr<Node> temp = first;
    first.reset(node);
    temp.get()->previous = std::weak_ptr<Node>(first);
    first.get()->next = temp;
    
}

std::weak_ptr<Node> LinkedList::frontSearch(const int value)
{
    isListEmpty();

    std::weak_ptr<Node> current = first;
    do
    {
        if(current.lock()->value == value)
        {
            std::cout << "Found value " << current.lock()->value << std::endl;
            return current.lock();
        }
        else
        {
            std::cout << "Going through " << current.lock()->value << std::endl;
            current = current.lock()->next;
        }
    } while(current.lock());

    
    std::cout << "Not found: value " << value << std::endl;
    return std::weak_ptr<Node>();
}

std::weak_ptr<Node> LinkedList::backSearch(const int value)
{
    isListEmpty();
    
    std::weak_ptr<Node> current = last;

    do
    {
        if(current.lock()->value == value)
        {
            std::cout << "Found value " << current.lock()->value << std::endl;
            return current.lock();
        }
        else
        {
            std::cout << "Going through " << current.lock()->value << std::endl;
            current = current.lock()->previous;
        }

    }while(current.lock());

    std::cout << "Not found: value " << value << std::endl;
    return std::weak_ptr<Node>();;
}

void LinkedList::isListEmpty()
{
    if(!first.get()) {
        throw EmptyListError("List is empty!");
    }
}

bool LinkedList::addIfFirst(Node* node)
{
    if(!first)
    {
        first = std::shared_ptr<Node>(node);
        last = std::weak_ptr<Node>(first);
        return true;
    }
    return false;
}

bool LinkedList::isNodePresent(Node* node)
{
        std::weak_ptr<Node> current = first;

        while(current.lock())
        {
            if(current.lock().get() == node) {
                std::cout << "Node " << node << " has been added" << std::endl;
                return true;
            }
            current = std::weak_ptr<Node>(current.lock()->next);
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

    Node* node4 = new Node(4);
    Node* node7 = new Node(7);

    lista.addToTheEnd(node4);
    lista.addToTheFront(new Node(2)); //add to the fornt
    lista.addToTheEnd(node7);
    lista.addToTheEnd(node7); // Message that this node is present
    lista.addToTheEnd(new Node(9));

    try
    {
        auto node = lista.frontSearch(1);
        auto node2 = lista.frontSearch(4);

        auto nodeB = lista.backSearch(1);
        auto nodeB2 = lista.backSearch(4);

        if (node.lock())
            std::cout << node.lock()->value << '\n';

        if (node2.lock())
            std::cout << node2.lock()->value << '\n';

        if (nodeB.lock())
            std::cout << nodeB.lock()->value << '\n';

        if (nodeB2.lock())
            std::cout << nodeB2.lock()->value << '\n';

        return 0;
    }
    catch(const EmptyListError& e) {
        std::cerr << e.what() << '\n';
    }
    

}

