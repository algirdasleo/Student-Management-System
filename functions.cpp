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

    while (true) {
        cout << "Įveskite studento vardą:" << endl;
        cin >> input;
        try {
            if (!isString(input)) {
                throw invalid_argument("Įvestas ne vardas. Įveskite vardą:");
            }
            studentas.vardas = input;
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        cout << "Įveskite studento pavardę:" << endl;
        cin >> input;
        try {
            if (!isString(input)) {
                throw invalid_argument("Ivesta ne pavarde. Iveskite pavarde:");
            }
            studentas.pavarde = input;
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
}

void numberInputProtection(string &input) {
    try {
        if (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10) {
            throw invalid_argument("Iveskite skaiciu nuo 1 iki 10:");
        }
    } catch (const invalid_argument &e) {
        cout << e.what() << endl;
        cin >> input;
        numberInputProtection(input);
    }
}

void charInputProtection(string &input) {
    try {
        if (input.length() > 1 || (input != "n" && input != "y")) {
            throw invalid_argument("Neteisingas pasirinkimas. Iveskite 'y' arba 'n':");
        }
    } catch (const invalid_argument &e) {
        cout << e.what() << endl;
        cin >> input;
        charInputProtection(input);
    }
}

void isvedimas(vector<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis) {
    char pasirinkimas;
    while (true) {
        cout << "Kaip noretumete surusiuoti studentus? (pagal: v - varda, p - pavarde, g - galutini bala(vidurkis), m - galutini bala(mediana)):" << endl;
        cin >> pasirinkimas;
        try {
            if (pasirinkimas != 'v' && pasirinkimas != 'p' && pasirinkimas != 'g' && pasirinkimas != 'm') {
                throw invalid_argument("Neteisingas pasirinkimas. Iveskite 'v', 'p', 'g' arba 'm':");
            }
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    char input;
    while (true) {
        cout << "Surusiuoti didejancia ar mazejancia tvarka? (d - didejancia, m - mažejancia)" << endl;
        cin >> input;
        try {
            if (input != 'd' && input != 'm') {
                throw invalid_argument("Neteisingas pasirinkimas. Iveskite 'd' arba 'm':");
            }
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
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
