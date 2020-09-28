#include <iostream>
#include <memory>
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
    if(argc != 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }
    const char* N = argv[1];
    try {
        auto rsc = std::make_unique<Resource>();
        rsc->use(N);
    } catch (logic_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}

