#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

class Studentas;  // Forward declaration

class StudentasManager {  // Class for managing students, reading from file, sorting, printing to file
private:
    std::list<Studentas> studentList;
    int maxNameLength, maxSurnameLength;

public:
    struct OutputHelper {
        const Studentas &student;
        int maxNameLength, maxSurnameLength;
        OutputHelper(const Studentas &s, int maxName = 0, int maxSurname = 0) : student(s), maxNameLength(maxName), maxSurnameLength(maxSurname) {}
    };

    friend std::ostream &operator<<(std::ostream &out, const OutputHelper &helper);

    StudentasManager();
    ~StudentasManager();

    size_t getStudentListSize();
    void addStudent(Studentas &student);
    void generateRandomStudents(int count);
    void readFromFile(std::string fileName);
    void setMaxNameLength(int length);
    void setMaxSurnameLength(int length);
    int getMaxNameLength();
    int getMaxSurnameLength();
    void sortIntoGroups(std::list<Studentas> &neislaike);
    void sortStudents(char choice1, char choice2);
    void sortStudents(char choice1, char choice2, std::list<Studentas> &neislaike);
    void groupAndPrint();
    void noGroupPrint();
    void printToFile();                      // Print to a default file name Rezultatas.txt
    void printToFile(std::string fileName);  // Print to a custom file name
    void printToFile(std::string fileName, std::list<Studentas> &neislaike);
};

class Studentas {  // Class for student data
protected:
    std::string vardas, pavarde;

private:
    std::list<int> ndPazymiai;
    double egzPazymys, galBalasVid, galBalasMed;

public:
    Studentas();
    ~Studentas();

    friend std::ostream &operator<<(std::ostream &out, const StudentasManager::OutputHelper &helper);  // OutputHelper can access private members of Studentas
    Studentas(const Studentas &stud);
    Studentas &operator=(const Studentas &stud);
    Studentas(Studentas &&stud) noexcept;
    Studentas &operator=(Studentas &&stud) noexcept;

    friend std::istream &operator>>(std::istream &in, Studentas &stud);
    friend class StudentasManager;

    void setName(std::string name);
    std::string getName();
    void setSurname(std::string surname);
    std::string getSurname();
    void addGrade(int grade);
    void setEgz(int grade);
    void readName();
    void calculate();
    void testStudentasClass();  // Testing Rule of Five for Studentas class
};

// Derived classes for different ways of reading student data

class ReadStudentas {
public:
    virtual std::istream &read(std::istream &is, StudentasManager &manager, Studentas &student) = 0;
};

class ManualStudentas : public ReadStudentas {
public:
    std::istream &read(std::istream &is, StudentasManager &manager, Studentas &student) override;

private:
    void readName(std::istream &is, Studentas &student);
    void getUserGradeInput(std::istream &is, Studentas &student);
};

class SemiAutoStudentas : public ReadStudentas {
public:
    std::istream &read(std::istream &is, StudentasManager &manager, Studentas &student) override;

private:
    void readName(std::istream &is, Studentas &student);
    void generateGrades(Studentas &st);
};

class AutoStudentas : public ReadStudentas {
public:
    std::istream &read(std::istream &is, StudentasManager &manager, Studentas &student) override;

private:
    void enterFileName(std::istream &is, StudentasManager &manager, Studentas &student);
};

class FileStudentas : public ReadStudentas {
public:
    std::istream &read(std::istream &is, StudentasManager &manager, Studentas &student) override;

private:
    std::string enterFileName(std::istream &is);
};


void numberInputProtection(std::string &input);
void charInputProtection(std::string &input);
bool isNumber(std::string &str);
bool isString(std::string &str);
void howToSort(char &choice1, char &choice2);
void generateFile(int range, int homeworkCount);
int getMenuChoice();
void getUserGradeInput(Studentas &st);
void enterFileName(std::ifstream &in, std::string &fileName);
void rangeStudentGenerator();
void fiveFileGenerator();

#endif