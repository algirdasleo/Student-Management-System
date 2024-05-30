#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "functions.h"

TEST_CASE("Studentas Constructor and Property Tests", "Studentas") {
    Studentas student;

    SECTION("Default Constructor Test") {
        REQUIRE(student.getName() == "");
        REQUIRE(student.getSurname() == "");
    }

    SECTION("Set and Get Name and Surname"){
        student.setName("John");
        student.setSurname("Doe");

        REQUIRE(student.getName() == "John");
        REQUIRE(student.getSurname() == "Doe");
    }

    SECTION("Add Grades and Calculate Scores") {
        student.addGrade(10);
        student.addGrade(9);
        student.addGrade(8);
        student.addGrade(7);
        student.addGrade(6);
        student.setEgz(5);

        student.calculate();

        REQUIRE(student.getFinalGradeVid() == 6.2);
        REQUIRE(student.getFinalGradeMed() == 8);
    }
}

TEST_CASE("Copy Constructor properly copies all attributes", "[Studentas]") {
    Studentas original;
    original.setName("Jonas");
    original.setSurname("Jonaitis");
    original.addGrade(8);
    original.setEgz(9);
    original.calculate();

    Studentas copyConstructed(original);

    REQUIRE(copyConstructed.getName() == original.getName());
    REQUIRE(copyConstructed.getSurname() == original.getSurname());
    REQUIRE(copyConstructed.getEgz() == original.getEgz());
    REQUIRE(copyConstructed.getFinalGradeVid() == original.getFinalGradeVid());
    REQUIRE(copyConstructed.getFinalGradeMed() == original.getFinalGradeMed());
    REQUIRE(copyConstructed.getGrades() == original.getGrades());
}

TEST_CASE("Move Constructor transfers ownership of attributes properly", "[Studentas]") {
    Studentas original;
    original.setName("Jonas");
    original.setSurname("Jonaitis");
    original.addGrade(10);
    original.setEgz(9);
    original.calculate();

    Studentas movedTo(std::move(original));

    REQUIRE(movedTo.getName() == "Jonas");
    REQUIRE(movedTo.getSurname() == "Jonaitis");
    REQUIRE(movedTo.getEgz() == 9);
    REQUIRE(original.getName().empty());    
    REQUIRE(original.getSurname().empty());  
}

TEST_CASE("Copy Assignment Operator copies all attributes", "[Studentas]") {
    Studentas original;
    original.setName("Jonas");
    original.setSurname("Jonaitis");
    original.addGrade(10);
    original.setEgz(9);
    original.calculate();

    Studentas assigned;
    assigned = original;

    REQUIRE(assigned.getName() == original.getName());
    REQUIRE(assigned.getSurname() == original.getSurname());
    REQUIRE(assigned.getEgz() == original.getEgz());
    REQUIRE(assigned.getFinalGradeVid() == original.getFinalGradeVid());
    REQUIRE(assigned.getFinalGradeMed() == original.getFinalGradeMed());
    REQUIRE(assigned.getGrades() == original.getGrades());
}

TEST_CASE("Move Assignment Operator transfers ownership of attributes properly", "[Studentas]") {
    Studentas original;
    original.setName("Jonas");
    original.setSurname("Jonaitis");
    original.addGrade(10);
    original.setEgz(9);
    original.calculate();

    Studentas movedTo;
    movedTo = std::move(original);

    REQUIRE(movedTo.getName() == "Jonas");
    REQUIRE(movedTo.getSurname() == "Jonaitis");
    REQUIRE(movedTo.getEgz() == 9);
    REQUIRE(original.getName().empty()); 
}
