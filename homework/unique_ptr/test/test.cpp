#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch_amalgamated.hpp"
#include "../uniquePTR.hpp"
#include <type_traits>

SCENARIO("Testing unique pointer")
{
    GIVEN("Made pointer")
    {
        auto unique2 = unique_ptr<int>(new int(5));
        WHEN("Checking if it is possible to copy by copy constructor")
        {
            auto copy = std::is_copy_constructible<unique_ptr<int>>::value;
            THEN("Result should be false")
            {
                REQUIRE_FALSE(copy);
            }
        }
        WHEN("Checking if it is possible to copy by copy assignment operator"){
            auto copy2 = std::is_copy_assignable<unique_ptr<int>>::value;
            THEN("Result should be false"){
                REQUIRE_FALSE(copy2);
            }
        }

        // WHEN("Find student with surname Nowak")
        // {
        //     db->GetStudentsWithSurname("Nowak");
        //     THEN("vector contains Nowak")
        //     {
        //         REQUIRE(db->person.size());
        //         auto Surname0 = db->person[0]->GetSurname();
        //         CHECK(Surname0 == "Nowak");
        //     }
        // }
    }
}
