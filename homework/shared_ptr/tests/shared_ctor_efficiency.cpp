#include <vector>
#include "shared.hpp"

int main () {
    constexpr int count{1000 * 1000 * 10};
    static_assert(count == 10000000);
    std::vector<cs::shared_ptr<int>> vec;
    vec.reserve(count);
    for (int i = 0; i < count; ++i) {
        vec.emplace_back(cs::shared_ptr<int>(new int{5}));
    }
}
