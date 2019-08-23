#include <iostream>
#include <memory>
#include <stdexcept>

struct EmptyListError : public std::runtime_error
{
    EmptyListError(std::string msg) : runtime_error(msg){};
};

struct Node
{
    Node(const int v) :
        value(v)
    {}

    std::shared_ptr<Node> next;
    std::weak_ptr<Node> previous;
    int value;
};

class LinkedList
{
public:
    LinkedList();
    
    ~LinkedList(){};

    

    void addToTheEnd(Node* node);
    void addToTheFront(Node* node);
    std::weak_ptr<Node> frontSearch(const int value);
    std::weak_ptr<Node> backSearch(const int value);
    

private:
    void isListEmpty();
    bool addIfFirst(Node* node);
    bool isNodePresent(Node* node);

    std::shared_ptr<Node> first;
    std::weak_ptr<Node> last;
};