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

struct studentaiStruct {
    string vardas, pavarde;
    list<int> nd;
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
};

bool isNumber(string &str);
bool isString(string &str);
void skaiciavimai(studentaiStruct &studentas);
void vardoIvedimas(studentaiStruct &studentas);
void numberInputProtection(string &input);
void charInputProtection(string &input);
void kaipRusiuoti(char &p1, char &p2);
void isvedimas(list<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis);
void isvedimas(list<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis, string pavadinimas);
void isvedimoSortinimas(list<studentaiStruct> &stud, char pasirinkimas, char input);

void generuotiFaila(int kiekis, int pazymiuKiekis);

#endif