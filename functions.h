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

bool isNumber(string &str);
bool isString(string &str);
void skaiciavimai(studentaiStruct &studentas);
void vardoIvedimas(studentaiStruct &studentas);
void numberInputProtection(string &input);
void charInputProtection(string &input);
void isvedimas(vector<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis);

void generuotiFaila(int kiekis, int pazymiuKiekis);

#endif