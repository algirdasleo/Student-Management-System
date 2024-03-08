#include "functions.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
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
        cout << "Iveskite studento varda:" << endl;
        cin >> input;
        try {
            if (!isString(input)) {
                throw invalid_argument("Ivestas ne vardas. Iveskite varda:");
            }
            studentas.vardas = input;
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        cout << "Iveskite studento pavarde:" << endl;
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

void kaipRusiuoti(char &p1, char &p2) {
    while (true) {
        cout << "Kaip noretumete surusiuoti studentus? (pagal: v - varda, p - pavarde, g - galutini bala(vidurkis), m - galutini bala(mediana)):" << endl;
        cin >> p1;
        try {
            if (p1 != 'v' && p1 != 'p' && p1 != 'g' && p1 != 'm') {
                throw invalid_argument("Neteisingas pasirinkimas. Iveskite 'v', 'p', 'g' arba 'm':");
            }
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        cout << "Surusiuoti didejancia ar mazejancia tvarka? (d - didejancia, m - mazejancia)" << endl;
        cin >> p2;
        try {
            if (p2 != 'd' && p2 != 'm') {
                throw invalid_argument("Neteisingas pasirinkimas. Iveskite 'd' arba 'm':");
            }
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
}

void isvedimas(deque<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis) {
    string input;
    cout << "Ar norite surusiuoti studentus? (y / n)" << endl;
    cin >> input;
    charInputProtection(input);
    char pasirinkimas, rusiavimas;
    kaipRusiuoti(pasirinkimas, rusiavimas);
    isvedimoSortinimas(stud, pasirinkimas, rusiavimas);
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

void isvedimas(deque<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis, string pavadinimas) {
    ofstream out(pavadinimas);
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
    cout << "\nRezultatai isvesti i faila '" << pavadinimas << "'.\n";
}

void isvedimoSortinimas(deque<studentaiStruct> &stud, char pasirinkimas, char input) {
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
};

void generuotiFaila(int kiekis, int pazymiuKiekis) {
    int tarpuIlgis = to_string(kiekis).length();
    int maxVardoIlgis = 6 + tarpuIlgis, maxPavardesIlgis = 7 + tarpuIlgis;
    string input;
    cout << "Generuojamas failas su " << kiekis << " studentu duomenimis...\n";
    clock_t start3 = clock();
    ofstream out("kursiokai" + to_string(kiekis) + ".txt");
    out << left;
    out << setw(maxVardoIlgis + 3) << "Vardas"
        << setw(maxPavardesIlgis + 3) << "Pavarde";
    for (int i = 1; i <= pazymiuKiekis; i++) out << setw(5) << "ND" + to_string(i);
    out << setw(4) << " Egzaminas"
        << "\n";

    for (int i = 1; i <= kiekis; i++) {
        out << setw(maxVardoIlgis + 3) << "Vardas" + to_string(i)
            << setw(maxPavardesIlgis + 3) << "Pavarde" + to_string(i);
        for (int j = 1; j < pazymiuKiekis; j++) out << setw(5) << to_string(rand() % 10 + 1);
        if (pazymiuKiekis > 0) out << setw(6) << to_string(rand() % 10 + 1);

        out << setw(2) << to_string(rand() % 10 + 1) << "\n";
    }
    out.close();
    cout << "Failas 'kursiokai" << kiekis << ".txt' sugeneruotas per " << (clock() - start3) / (double)CLOCKS_PER_SEC << " s.\n";
}