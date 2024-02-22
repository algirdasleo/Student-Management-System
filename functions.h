#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct studentaiStruct {
    string vardas, pavarde;
    vector<int> nd;
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
};

bool isNumber(std::string &str);
bool isString(std::string &str);
void skaiciavimai(studentaiStruct &studentas);
void vardoIvedimas(studentaiStruct &studentas);
void numberInputProtection(std::string &input);
void charInputProtection(std::string &input);
void isvedimas(std::vector<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis);

#endif