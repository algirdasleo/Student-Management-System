#include "functions.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
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

void generateFile(int range, int homeworkCount) {
    int tarpuIlgis = to_string(range).length();
    int maxVardoIlgis = 6 + tarpuIlgis, maxPavardesIlgis = 7 + tarpuIlgis;
    string input;
    cout << "Generuojamas failas su " << range << " studentu duomenimis...\n";
    clock_t start3 = clock();
    ofstream out("kursiokai" + to_string(range) + ".txt");
    out << left;
    out << setw(maxVardoIlgis + 3) << "Vardas"
        << setw(maxPavardesIlgis + 3) << "Pavarde";
    for (int i = 1; i <= homeworkCount; i++) out << setw(5) << "ND" + to_string(i);
    out << setw(4) << " Egzaminas"
        << "\n";

    for (int i = 1; i <= range; i++) {
        out << setw(maxVardoIlgis + 3) << "Vardas" + to_string(i)
            << setw(maxPavardesIlgis + 3) << "Pavarde" + to_string(i);
        for (int j = 1; j < homeworkCount; j++) out << setw(5) << to_string(rand() % 10 + 1);
        if (homeworkCount > 0) out << setw(6) << to_string(rand() % 10 + 1);

        out << setw(2) << to_string(rand() % 10 + 1) << "\n";
    }
    out.close();
    cout << "Failas 'kursiokai" << range << ".txt' sugeneruotas per " << (clock() - start3) / (double)CLOCKS_PER_SEC << " s.\n";
}

void howToSort(char &choice1, char &choice2) {
    string input;
    cout << "Pagal ka norite surusiuoti studentus? (v - vardas, p - pavarde, g - galutinis (vidurkis), m - galutinis (mediana))" << endl;
    cin >> input;
    while (input.length() > 1 || (input != "v" && input != "p" && input != "g" && input != "m")) {
        cout << "Neteisingas pasirinkimas. Iveskite 'v', 'p', 'g' arba 'm':" << endl;
        cin >> input;
    }
    choice1 = input[0];
    cout << "Kaip norite surusiuoti? (d - didejimo tvarka, m - mazejimo tvarka)" << endl;
    cin >> input;
    while (input.length() > 1 || (input != "d" && input != "m")) {
        cout << "Neteisingas pasirinkimas. Iveskite 'd' arba 'm':" << endl;
        cin >> input;
    }
    choice2 = input[0];
}

void Studentas::setName(string name) {
    this->vardas = name;
}

string Studentas::getName() {
    return this->vardas;
}

string Studentas::getSurname() {
    return this->pavarde;
}

void Studentas::setSurname(string surname) {
    this->pavarde = surname;
}

void Studentas::addGrade(int grade) {
    this->ndPazymiai.push_back(grade);
}

void Studentas::setEgz(int grade) {
    this->egzPazymys = grade;
}

void Studentas::calculate() {
    int ndrange = distance(this->ndPazymiai.begin(), this->ndPazymiai.end());
    this->ndPazymiai.sort();
    auto mid = next(this->ndPazymiai.begin(), ndrange / 2);
    if (ndrange % 2 == 0) {
        auto midPrev = prev(mid, 1);
        this->galBalasMed = (*mid + *midPrev) / 2.0;
    } else {
        this->galBalasMed = *mid;
    }
    double sum = accumulate(this->ndPazymiai.begin(), this->ndPazymiai.end(), 0.0);
    this->galBalasVid = 0.4 * (sum / ndrange) + 0.6 * this->egzPazymys;
}

void Studentas::readName() {
    string input;

    while (true) {
        cout << "Iveskite studento varda:" << endl;
        cin >> input;
        try {
            if (!isString(input)) {
                throw invalid_argument("Ivestas ne vardas. Iveskite varda:");
            }
            this->vardas = input;
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
            this->pavarde = input;
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }
}

void Studentas::printToFile(list<Studentas> &stud, int maxVardoIlgis, int maxPavardesIlgis) {
    string input;
    cout << "Ar norite surusiuoti studentus? (y / n)" << endl;
    cin >> input;
    charInputProtection(input);
    char pasirinkimas, rusiavimas;
    howToSort(pasirinkimas, rusiavimas);
    sorting(stud, pasirinkimas, rusiavimas);
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
            << setw(17) << fixed << setprecision(2) << student.galBalasVid
            << setw(15) << fixed << setprecision(2) << student.galBalasMed << endl;
    }
    out.close();
    cout << "\nRezultatai isvesti i faila 'rezultatas.txt'.\n";
}

void Studentas::printToFile(list<Studentas> &stud, int maxNameLength, int maxSurnameLength, string fileName) {
    ofstream out(fileName);
    out << left
        << setw(maxSurnameLength + 2) << "Pavarde"
        << setw(maxNameLength + 2) << "Vardas"
        << setw(17) << "Galutinis(Vid.)"
        << setw(15) << "Galutinis(Med.)" << endl;

    out << setfill('-') << setw(maxSurnameLength + maxNameLength + 34) << "-" << endl;
    out << setfill(' ');

    for (const auto &student : stud) {
        out << setw(maxSurnameLength + 2) << student.pavarde
            << setw(maxNameLength + 2) << student.vardas
            << setw(17) << fixed << setprecision(2) << student.galBalasVid
            << setw(15) << fixed << setprecision(2) << student.galBalasMed << endl;
    }
    out.close();
    cout << "\nRezultatai isvesti i faila '" << fileName << "'.\n";
}

void Studentas::sorting(list<Studentas> &stud, char pasirinkimas, char input) {
    clock_t _start = clock();
    if (pasirinkimas == 'v') {
        if (input == 'd')
            stud.sort([](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
        else
            stud.sort([](const Studentas &a, const Studentas &b) { return a.vardas > b.vardas; });
    } else if (pasirinkimas == 'p') {
        if (input == 'd')
            stud.sort([](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
        else
            stud.sort([](const Studentas &a, const Studentas &b) { return a.pavarde > b.pavarde; });
    } else if (pasirinkimas == 'g') {
        if (input == 'd')
            stud.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid < b.galBalasVid; });
        else
            stud.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid > b.galBalasVid; });
    } else if (pasirinkimas == 'm') {
        if (input == 'd')
            stud.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed < b.galBalasMed; });
        else
            stud.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed > b.galBalasMed; });
    }
    cout << "Surusiuota per " << (clock() - _start) / (double)CLOCKS_PER_SEC << " s.\n";
};

void Studentas::readFromFile(list<Studentas> &failoStud, string fileName, int &maxNameLength, int &maxSurnameLength) {
    cout << "Nuskaitomi duomenys is failo '" << fileName << "'.\n";
    clock_t start = clock();
    ifstream in(fileName);
    string line;
    getline(in, line);
    string vardas, pavarde, pazymys;
    int pazymysInt;
    while (getline(in, line)) {
        istringstream iss(line);
        iss >> vardas >> pavarde;
        Studentas student;
        student.setName(vardas);
        student.setSurname(pavarde);
        while (iss >> pazymys) {
            pazymysInt = stoi(pazymys);
            if (pazymysInt < 1 || pazymysInt > 10) {
                cout << "Neteisingas pazymys: " << pazymysInt << ". Pazymys turi buti nuo 1 iki 10. Praleidziamas pazymys.\n";
                continue;
            }
            student.addGrade(pazymysInt);
        }
        if (!student.ndPazymiai.empty()) {
            student.setEgz(student.ndPazymiai.back());
            student.ndPazymiai.pop_back();
            student.calculate();
        }
        if (vardas.length() > maxNameLength) maxNameLength = vardas.length();
        if (pavarde.length() > maxSurnameLength) maxSurnameLength = pavarde.length();
        failoStud.push_back(student);
    }
    in.close();

    cout << "Duomenys nuskaityti is failo per " << (clock() - start) / (double)CLOCKS_PER_SEC << " s.\n";
}

void Studentas::sortIntoGroups(list<Studentas> &stud, list<Studentas> &neislaike) {
    clock_t start = clock();
    auto it = stud.begin();
    while (it != stud.end()) {
        if (it->galBalasVid < 5 && it->galBalasMed < 5) {
            neislaike.splice(neislaike.end(), stud, it++);
        } else {
            ++it;
        }
    }
    cout << "Studentai islaikyti ir neislaikyti surusiuoti per " << double(clock() - start) / CLOCKS_PER_SEC << " sekundziu.\n\n";
}