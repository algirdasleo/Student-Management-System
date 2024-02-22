#include "functions.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isNumber(string &str) {
    for (char c : str)
        if (!isdigit(c))
            return false;
    return true;
}

bool isString(string &str) {
    for (char c : str)
        if (!isalpha(c))
            return false;
    return true;
}
void skaiciavimai(studentaiStruct &studentas) {
    int ndKiekis = studentas.nd.size();
    sort(studentas.nd.begin(), studentas.nd.end());
    if (ndKiekis % 2 == 0)
        studentas.mediana = (studentas.nd[ndKiekis / 2] + studentas.nd[(ndKiekis / 2) - 1]) / 2.0;
    else
        studentas.mediana = studentas.nd[ndKiekis / 2];
    studentas.galutinisVid = 0.4 * (studentas.ndSuma / ndKiekis) + 0.6 * studentas.egzas;
    studentas.galutinisMed = 0.4 * studentas.mediana + 0.6 * studentas.egzas;
}

void vardoIvedimas(studentaiStruct &studentas) {
    string input;

    cout << "Iveskite studento varda:" << endl;
    cin >> input;
    while (!isString(input)) {
        cout << "Ivestas ne vardas. Iveskite varda:" << endl;
        cin >> input;
    }
    studentas.vardas = input;
    cout << "Iveskite studento pavarde:" << endl;
    cin >> input;
    while (!isString(input)) {
        cout << "Ivesta ne pavarde. Iveskite pavarde:" << endl;
        cin >> input;
    }
    studentas.pavarde = input;
}

void numberInputProtection(string &input) {
    while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10) {
        cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
        cin >> input;
    }
}

void charInputProtection(string &input) {
    while (input.length() > 1 || (input != "n" && input != "y")) {
        cout << "Neteisingas pasirinkimas. Iveskite 'y' arba 'n':" << endl;
        cin >> input;
    }
}

void isvedimas(vector<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis) {
    char pasirinkimas;
    cout << "Kaip noretumete surusiuoti studentus? (pagal: v - varda, p - pavarde, g - galutini bala(vidurkis), m - galutini bala(mediana)):" << endl;
    cin >> pasirinkimas;
    while (pasirinkimas != 'v' && pasirinkimas != 'p' && pasirinkimas != 'g' && pasirinkimas != 'm') {
        cout << "Neteisingas pasirinkimas. Iveskite 'v', 'p', 'g' arba 'm':" << endl;
        cin >> pasirinkimas;
    }
    cout << "Surusiuoti didejancia ar mazejancia tvarka? (d - didejancia, m - mazejancia)" << endl;

    char input;
    cin >> input;
    while (input != 'd' && input != 'm') {
        cout << "Neteisingas pasirinkimas. Iveskite 'd' arba 'm':" << endl;
        cin >> input;
    }

    if (pasirinkimas == 'v') {
        if (input == 'd')
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.vardas < b.vardas; });
        else
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.vardas > b.vardas; });
    } else if (pasirinkimas == 'p') {
        if (input == 'd')
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.pavarde < b.pavarde; });
        else
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.pavarde > b.pavarde; });
    } else if (pasirinkimas == 'g') {
        if (input == 'd')
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.galutinisVid < b.galutinisVid; });
        else
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.galutinisVid > b.galutinisVid; });
    } else if (pasirinkimas == 'm') {
        if (input == 'd')
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.galutinisMed < b.galutinisMed; });
        else
            sort(stud.begin(), stud.end(), [](const studentaiStruct &a, const studentaiStruct &b) { return a.galutinisMed > b.galutinisMed; });
    }

    ofstream out("rezultatas.txt");
    out << left
        << setw(maxPavardesIlgis + 2) << "Pavarde"
        << setw(maxVardoIlgis + 2) << "Vardas"
        << setw(17) << "Galutinis(Vid.)"
        << setw(15) << "Galutinis(Med.)" << endl;

    out << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl;
    out << setfill(' ');

    for (const auto &student : stud) {
        out << setw(maxPavardesIlgis + 2) << student.pavarde
            << setw(maxVardoIlgis + 2) << student.vardas
            << setw(17) << fixed << setprecision(2) << student.galutinisVid
            << setw(15) << fixed << setprecision(2) << student.galutinisMed << endl;
    }
    out.close();
    cout << "\nRezultatai isvesti i faila 'rezultatas.txt'.\n";
}
