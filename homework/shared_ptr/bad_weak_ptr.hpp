#pragma once
#include <stdexcept>

namespace cs {
    class bad_weak_ptr :public std::exception {
        std::string message{"weak ptr is expired!\n"};
        public:
        bad_weak_ptr() = default;
        explicit bad_weak_ptr(const std::string& what) :message(what) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    };
};
