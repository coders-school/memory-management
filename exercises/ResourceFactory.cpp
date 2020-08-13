#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Resource
{
    Resource(char* byte) : byte_(byte) {}
    char byte() const { return *byte_; }
    virtual string name() const = 0;
    virtual ~Resource() = default;

protected:
    unique_ptr<char> byte_ = nullptr;
};

struct ResourceA : Resource
{
    ResourceA(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceA ").append(byte_.get(), 1); }
};

struct ResourceB : Resource
{
    ResourceB(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceB ").append(byte_.get(), 1); }
};

struct ResourceFactory
{
    shared_ptr<Resource> makeResourceA(char* byte) { return make_shared<ResourceA>(byte); }
    shared_ptr<Resource> makeResourceB(char* byte) { return make_shared<ResourceB>(byte); }
};

struct ResourceCollection
{
    void add(shared_ptr<Resource> r) { resources.push_back(r); }
    void clear() { resources.clear(); }
    shared_ptr<Resource> operator[](int index) { return resources[index]; }
    void printAll()
    {
        for (const auto & res : resources)
        {
            cout << res->name() << endl;
        }
    }

private:
    vector<shared_ptr<Resource>> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char{0x40}));
    collection.add(rf.makeResourceB(new char{0x41}));
    collection.printAll();

    auto firstByte = collection[0]->byte();
    cout << firstByte << endl;
    collection.clear();

    return 0;
}
