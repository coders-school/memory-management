#include <iostream>
#include <vector>

using namespace std;

vector<int*> allocate_ints()
{
    vector<int*> numbers;
    for(int i = 0; i < 10; i++)
    {
        numbers.push_back(new int(i));
        cout << "Added " << i << endl;
    }
    return numbers;
}

void deallocate_ints(vector<int*> numbers)
{
    for(auto number : numbers)
    {
        delete number;
    }
}

int main()
{
    vector<int*> num = allocate_ints();
    cout << "Hello World!" << endl;
    return 0;
}

