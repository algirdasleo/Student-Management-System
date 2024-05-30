#define CATCH_CONFIG_MAIN
#include "NewVector.h"
#include "catch_amalgamated.hpp"

TEST_CASE("NewVector basic operations", "[NewVector]") {
    NewVector<int> vec;

    SECTION("Default constructor") {
        REQUIRE(vec.size() == 0);
        REQUIRE(vec.empty());
    }

    SECTION("Push and Pop") {
        vec.push_back(1);
        vec.push_back(2);
        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);

        vec.pop_back();
        REQUIRE(vec.size() == 1);
        REQUIRE(vec.back() == 1);
    }

    SECTION("Front and Back accessors") {
        vec.push_back(10);
        vec.push_back(20);
        REQUIRE(vec.front() == 10);
        REQUIRE(vec.back() == 20);
    }

    SECTION("Bracket operator and const correctness") {
        vec.push_back(3);
        vec.push_back(4);
        const NewVector<int> constVec = vec;

        REQUIRE(constVec[0] == 3);
        REQUIRE(constVec[1] == 4);
    }
}

TEST_CASE("NewVector iterators", "[NewVector]") {
    NewVector<int> vec{1, 2, 3, 4, 5};

    SECTION("Iterator access") {
        auto it = vec.begin();
        REQUIRE(*it == 1);
        ++it;
        REQUIRE(*it == 2);
    }

    SECTION("Const iterator access") {
        const NewVector<int> constVec = vec;
        auto cit = constVec.begin();
        REQUIRE(*cit == 1);
        ++cit;
        REQUIRE(*cit == 2);
    }

    SECTION("Using iterators to modify elements") {
        for (auto& item : vec) {
            item *= 10;
        }
        REQUIRE(vec[0] == 10);
        REQUIRE(vec[4] == 50);
    }
}

TEST_CASE("NewVector capacity functions", "[NewVector]") {
    NewVector<int> vec;

    SECTION("Empty and Size checks") {
        REQUIRE(vec.empty());
        REQUIRE(vec.size() == 0);

        vec.push_back(100);
        REQUIRE_FALSE(vec.empty());
        REQUIRE(vec.size() == 1);
    }

    SECTION("Reserve and Shrink to fit") {
        vec.reserve(10);
        REQUIRE(vec.max_size() >= 10);

        vec.push_back(1);
        vec.push_back(2);
        auto old_capacity = vec.max_size();
        vec.shrink_to_fit();

        REQUIRE(vec.size() == 2);                 
        REQUIRE(vec.max_size() <= old_capacity);  
        REQUIRE(vec.max_size() >= vec.size());   
    }
}

TEST_CASE("NewVector modifiers", "[NewVector]") {
    NewVector<int> vec{1, 2, 3};

    SECTION("Clear vector") {
        vec.clear();
        REQUIRE(vec.empty());
    }

    SECTION("Erase elements") {
        vec.erase(vec.begin() + 1); 
        REQUIRE(vec.size() == 2);
        REQUIRE(vec[1] == 3);
    }

    SECTION("Insert elements") {
        int arr[] = {7, 8};
        auto insertPos = vec.begin() + 1; 

        vec.insert(insertPos, arr, arr + 2);

        REQUIRE(vec.size() == 5); 
        REQUIRE(vec[1] == 7);  
        REQUIRE(vec[2] == 8);   
    }
}

TEST_CASE("NewVector copy and move semantics", "[NewVector]") {
    NewVector<int> original{1, 2, 3};

    SECTION("Copy constructor") {
        NewVector<int> copy = original;
        REQUIRE(copy == original);
    }

    SECTION("Move constructor") {
        NewVector<int> moved = std::move(original);
        REQUIRE(moved.size() == 3);
        REQUIRE(original.size() == 0);
    }

    SECTION("Copy assignment") {
        NewVector<int> copy;
        copy = original;
        REQUIRE(copy == original);
    }

    SECTION("Move assignment") {
        NewVector<int> moved;
        moved = std::move(original);
        REQUIRE(moved.size() == 3);
        REQUIRE(original.size() == 0); 
    }
}
