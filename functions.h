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

    void readStudentData(int choice);  // nauja f.
    void readName();
    void calculate();
    static void generateFile(int range, int homeworkCount);
    static void howToSort(char &choice1, char &choice2);
    static void sorting(list<Studentas> &stud, char choice1, char choice2);
    static void printToFile(list<Studentas> &stud, int maxNameLength, int maxSurnameLength);
    static void printToFile(list<Studentas> &stud, int maxNameLength, int maxSurnameLength, string fileName);
    static void numberInputProtection(string &input);
    static void charInputProtection(string &input);
    static bool isNumber(string &str);
    static bool isString(string &str);
};

#endif