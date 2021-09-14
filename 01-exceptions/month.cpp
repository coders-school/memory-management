
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

struct MonthRangeError : public std::range_error {
    MonthRangeError(std::string const& msg) : std::range_error(msg) {}
};

class Month {
    int number;
public:
    bool validate(int n) { return n >= 1 && n <=12; }
    Month(int n) {
        if (validate(n)) {
            number = n;
        } else {
            throw MonthRangeError{"Month should be between 1 and 12"};
        }
    }
};

int main() {
    try {
        Month month{13};
    } catch (std::range_error const & re) {
        std::cout << re.what() << '\n';
    } catch (MonthRangeError const & mre) {
        std::cout << mre.what() << '\n';
    }
    return 0;
}
