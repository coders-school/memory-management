#pragma once
#include <iostream>

class Data {
public:
    Data (size_t day, std::string month, size_t year) : day_(day),
                                                        month_(month),
               
                                                        year_(year) {}
    void print() {
        std::cout << day_ << " " << month_ << " " << year_ << '\n';
    }

    size_t getDay() const { return day_; }
    const std::string& getMonth() const { return month_; };
    size_t getYear() const { return year_;  }

private:
    size_t day_{};
    std::string month_{};
    size_t year_{};
};

