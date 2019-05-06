#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Resource
{
    Resource(char* byte) : byte_(byte) {}
    char* byte() const { return byte_; }
    virtual string name() const = 0;
    ~Resource() { delete byte_; }

protected:
    char* byte_ = nullptr;
};

struct ResourceA : Resource
{
    ResourceA(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceA ").append(byte_); }
};

struct ResourceB : Resource
{
    ResourceB(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceB ").append(byte_); }
};

struct ResourceFactory
{ 
    Resource* makeResourceA(char* byte) { return new ResourceA{byte}; }
    Resource* makeResourceB(char* byte) { return new ResourceB{byte}; }
};

struct ResourceCollection
{
    void add(Resource* r) { resources.push_back(r); }
    void clear() { resources.clear(); }
    Resource* operator[](int index) { return resources[index]; }
    void printAll()
    {
        for (const auto & res : resources)
        {
            cout << res->name() << endl;
        }
    }

private:
    vector<Resource*> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char{0x01}));
    collection.add(rf.makeResourceB(new char{0x02}));
    collection.printAll();

    auto firstByte = collection[0]->byte();
    collection.clear();
    cout << *firstByte << endl;

    return 0;
}

