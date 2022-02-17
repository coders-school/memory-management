#include <iostream>
#include <stdexcept>

using namespace std;

class Resource
{ 
public:
    void use(const char* N)
    {
        cout << "Using resource. Passed " << *N << endl;
        if (*N == 'd')
        {
            throw logic_error("Passed d. d is prohibited.");
        }
    };
};

int main(int argc, char* argv[])
{

    const char* N = argv[1];
    Resource* rsc = nullptr;
    try
    {
        rsc = new Resource();
        rsc->use(N);
        rsc = new Resource();
        delete rsc;
    }
    catch (logic_error & e)
    {
        cout << e.what() << endl;
    }

    if(argc != 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }

    return 0;
}

