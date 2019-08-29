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

    std::shared_ptr<std::unique_ptr<Node>> next;
    std::weak_ptr<std::unique_ptr<Node>> previous;
    int value;
};

class LinkedList
{
public:
    LinkedList();

    void addToTheEnd(std::unique_ptr<Node> node);
    void addToTheFront(std::unique_ptr<Node> node);

    std::shared_ptr<std::unique_ptr<Node>> frontSearch(const int value);
    std::shared_ptr<std::unique_ptr<Node>> backSearch(const int value);
    

private:
    void assertListNotEmpty();
    bool addIfFirst(std::unique_ptr<Node>& node);

    std::shared_ptr<std::unique_ptr<Node>> first;
    std::weak_ptr<std::unique_ptr<Node>> last;
};