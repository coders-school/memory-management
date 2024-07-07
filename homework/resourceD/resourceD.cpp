#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

class Resource
{
public:
    void use(std::unique_ptr<const char> N)
    {
        cout << "Using resource. Passed " << *N << endl;
        if (*N == 'd')
        {
            throw logic_error("Passed d. d is prohibited.");
        }
    };
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }

    auto N = std::make_unique<const char>(*argv[1]);

    try
    {
        std::unique_ptr<Resource> rsc = std::make_unique<Resource>();
        rsc->use(std::move(N));
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
