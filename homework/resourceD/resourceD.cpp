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
    const char* N = nullptr;
    if(argc >= 2)
    {
       N  = argv[1];
    }
    else
    {
        N = "example_text";
    }

    Resource* rsc = nullptr;
    try
    {
        rsc = new Resource();
        rsc->use(N);
        delete rsc;
    }
    catch (logic_error & e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

