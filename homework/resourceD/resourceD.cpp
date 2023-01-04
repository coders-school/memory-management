#include <iostream>
#include <stdexcept>

using namespace std;

class Resource
{ 
public:
    void use(const char* N)
    {   
        cout << "Using resource. Passed " << endl;
        {
            throw logic_error("Passed d. d is prohibited.");
        }
        delete N;
    };
};

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }
    const char* N = argv[1];
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
