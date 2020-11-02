#include <stdexcept>
#include <string>

namespace coders {

class ExpiredWeakPtr : public std::exception {
public:
    explicit ExpiredWeakPtr(const char* message)
        : msg_(message) {}
    explicit ExpiredWeakPtr(const std::string& message)
        : msg_(message) {}
    virtual ~ExpiredWeakPtr() noexcept {}
    virtual const char* what() const noexcept {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

}  // namespace coders
