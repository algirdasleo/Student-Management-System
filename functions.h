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

class Studentas{
private:
    string vardas, pavarde;
    list<int> ndPazymiai;
    double egzPazymys, galBalasVid, galBalasMed;
public:
    Studentas() : ndPazymiai(), egzPazymys(0), galBalasVid(0), galBalasMed(0) {}

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
    void numberInputProtection(string &input);
    void charInputProtection(string &input);
    bool isNumber(string &str);
    bool isString(string &str);
    void howToSort(char &choice1, char &choice2);
    void generateFile(int range, int homeworkCount);

#endif