#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
using namespace std;

class Studentas {
private:
    string vardas, pavarde;
    list<int> ndPazymiai;
    double egzPazymys, galBalasVid, galBalasMed;
    int maxNameLength, maxSurnameLength;

public:
    Studentas();
    ~Studentas();

    // Rule of Five
    Studentas(const Studentas &stud);
    Studentas &operator=(const Studentas &stud);
    Studentas(Studentas &&stud) noexcept;
    Studentas &operator=(Studentas &&stud) noexcept;

    friend ostream &operator<<(ostream &out, const Studentas &stud);

    void setName(string name);
    string getName();
    void setSurname(string surname);
    string getSurname();
    void addGrade(int grade);
    void setEgz(int grade);
    void readName();
    void calculate();
    void readFromFile(list<Studentas> &failoStud, string fileName, int &maxNameLength, int &maxSurnameLength);
    void sortIntoGroups(list<Studentas> &stud, list<Studentas> &neislaike);
    static void sorting(list<Studentas> &stud, char choice1, char choice2);
    static void printToFile(list<Studentas> &stud, int maxNameLength, int maxSurnameLength);
    static void printToFile(list<Studentas> &stud, int maxNameLength, int maxSurnameLength, string fileName);
};
void testStudentasClass();  // Testing Rule of Five for Studentas class

void numberInputProtection(string &input);
void charInputProtection(string &input);
bool isNumber(string &str);
bool isString(string &str);
void howToSort(char &choice1, char &choice2);
void generateFile(int range, int homeworkCount);

#endif