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

    void addToTheEnd(std::shared_ptr<Node> node);
    void addToTheFront(std::shared_ptr<Node> node);

    std::shared_ptr<Node> frontSearch(const int value);
    std::shared_ptr<Node> backSearch(const int value);
    

private:
    void assertListNotEmpty();
    bool addIfFirst(std::shared_ptr<Node> node);
    bool isNodePresent(std::shared_ptr<Node> node);

    std::shared_ptr<Node> first;
    std::weak_ptr<Node> last;
};