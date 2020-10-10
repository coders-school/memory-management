#include <atomic>

namespace cs {

class control_block
{
    std::atomic_size_t sharedRef_{1};
    std::atomic_size_t weakRef_{0};

   public:
    control_block() = default;
    int getSharedRef() const noexcept;
    int getWeakRef() const noexcept;
    void incrementSharedRef() noexcept;
    void decrementSharedRef() noexcept;
    void incrementWeakRef() noexcept;
    void decrementWeakRef() noexcept;
};

};
