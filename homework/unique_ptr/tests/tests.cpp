
#include "../TestClass.hpp"
#include "../uniqueptr.hpp"
#include "catch.hpp"

SCENARIO("Working on home implemented unique_ptr") {

  GIVEN("Created FirstUniquePtr and PtrCollection") {
    double input1 = 2.0;
    double input2 = 3.0;
    unique_ptr<TestClass> firstUnique(new TestClass(input1));
    std::vector<unique_ptr<TestClass>> PtrCollection;

    REQUIRE(firstUnique.get()->data_ == input1);
    REQUIRE(firstUnique.get() != nullptr);

    WHEN("Reseting unique_ptr with new object and value") {
      firstUnique.reset(new TestClass(input2));
      THEN("new value in unique_ptr, and earlier called get() is empty") {
        REQUIRE(firstUnique.get()->data_ == input2);
      }
    }

    WHEN("Reseted unique_ptr with nullptr") {
      firstUnique.reset(nullptr);
      THEN("unique_ptr is nullptr") { REQUIRE(firstUnique.get() == nullptr); }
    }
    WHEN("Reseted unique_ptr with reset()") {
      firstUnique.reset();
      THEN("unique_ptr is nullptr") { REQUIRE(firstUnique.get() == nullptr); }
    }
    WHEN("Releasing owned pointer without assigning return") {
      firstUnique.release();
      THEN("unique_ptr is nullptr") { REQUIRE(firstUnique.get() == nullptr); }
    }
    WHEN("Releasing owned pointer with assigning return") {
      unique_ptr<TestClass> SecondUnique(firstUnique.release());
      THEN("unique_ptr is nullptr") {
        REQUIRE(firstUnique.get() == nullptr);
        REQUIRE(SecondUnique.get()->data_ == input1);
      }
    }
    WHEN("Dereferencing unique_ptr (not nullptr)") {
      double output = (*firstUnique).data_;
      THEN("comparing data from unique_ptr with original value") {
        REQUIRE(output == input1);
      }
    }
    WHEN("Dereferencing unique_ptr which is null") {
      firstUnique.reset();
      THEN("comparing data from unique_ptr with original value") {
        REQUIRE_THROWS((*firstUnique).data_);
      }
    }
    WHEN("Moving reseted unique_ptr into another container") {
      firstUnique.reset(new TestClass(input2));
      PtrCollection.push_back(std::move(firstUnique));
      THEN("Check if there are new parameters") {
        REQUIRE(PtrCollection.at(0).get()->data_ == input2);
        REQUIRE(firstUnique.get() == nullptr);
      }
    }
    WHEN("Moving into another unique_ptr") {
      unique_ptr<TestClass> secondUnique = std::move(firstUnique);
      THEN("Check if there are new parameters") {
        REQUIRE(firstUnique.get() == nullptr);
        REQUIRE(secondUnique.get()->data_ == input1);
      }
    }
    WHEN("Moving unique_ptr(with nullptr inside) into another unique_ptr") {
      unique_ptr<TestClass> thirdUnique(nullptr);
      unique_ptr<TestClass> SecondUnique = std::move(thirdUnique);
      THEN("Check if there are new parameters") {
        REQUIRE(SecondUnique.get() == nullptr);
      }
    }
    WHEN("Releasing owned pointer with assigning return") {
      double init3 = 4.0;
      unique_ptr<TestClass> thirdUnique(new TestClass(init3));
      unique_ptr<TestClass> SecondUnique = std::move(thirdUnique);
      THEN("unique_ptr is nullptr") {
        REQUIRE(firstUnique.get() != nullptr);
        REQUIRE(SecondUnique.get()->data_ == init3);
      }
    }
  }
}