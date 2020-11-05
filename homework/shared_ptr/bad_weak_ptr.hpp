#pragma once
#include <stdexcept>

namespace cs {
    class bad_weak_ptr :public std::exception {
        public:
        bad_weak_ptr() = default;
    };
};
