#include <stdexcept>
#include <string>

namespace coders {

class ExpiredWeakPtr : public std::exception {
public:
    explicit ExpiredWeakPtr(const char* message)
        : msg_(message) {}
    explicit ExpiredWeakPtr(const std::string& message)
        : msg_(message) {}

protected:
    std::string msg_;
};

}  // namespace coders
