#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct studentaiStruct {
    string vardas, pavarde;
    int n;   // namu darbu kiekis
    int *T;  // namu darbu rezultatai
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
    studentaiStruct() : n(0), T(new int[1]), ndSuma(0), egzas(0), galutinisVid(0), mediana(0), galutinisMed(0) {}
};

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

void ivedimas(studentaiStruct &studentas) {
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
    while (input.length() > 1 && input != "n" && input != "y") {
        cout << "Neteisingas pasirinkimas. Iveskite 'y' arba 'n':" << endl;
        cin >> input;
    }
}

void skaiciavimai(studentaiStruct &studentas) {
    sort(studentas.T, studentas.T + studentas.n);
    if (studentas.n % 2 == 0)
        studentas.mediana = (studentas.T[studentas.n / 2] + studentas.T[(studentas.n / 2) - 1]) / 2.0;
    else
        studentas.mediana = studentas.T[studentas.n / 2];

    studentas.galutinisVid = 0.4 * (studentas.ndSuma / studentas.n) + 0.6 * studentas.egzas;
    studentas.galutinisMed = 0.4 * studentas.mediana + 0.6 * studentas.egzas;
}

void generavimas(studentaiStruct &studentas) {
    studentas.n = 10;
    studentas.T = new int[studentas.n];
    studentas.ndSuma = 0;
    for (int i = 0; i < studentas.n; i++) {
        studentas.T[i] = rand() % 10 + 1;
        studentas.ndSuma += studentas.T[i];
    }
    studentas.egzas = rand() % 10 + 1;
}

void isvedimas(studentaiStruct *students, int mokSk, int maxVardoIlgis, int maxPavardesIlgis) {
    cout << left
         << setw(maxPavardesIlgis + 2) << "Pavarde"
         << setw(maxVardoIlgis + 2) << "Vardas"
         << setw(17) << "Galutinis(Vid.)"
         << setw(15) << "Galutinis(Med.)" << endl;

    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < mokSk; i++) {
        cout << left
             << setw(maxPavardesIlgis + 2) << students[i].pavarde
             << setw(maxVardoIlgis + 2) << students[i].vardas
             << setw(17) << fixed << setprecision(2) << students[i].galutinisVid
             << setw(15) << fixed << setprecision(2) << students[i].galutinisMed << endl;
    }
}

int main() {
    srand(time(nullptr));
    int mokSk = 0;
    studentaiStruct *students = nullptr;
    string input;
    int meniuPasirinkimas;
    int maxVardoIlgis = 5, maxPavardesIlgis = 7;

    while (true) {
        cout << "Meniu. Pasirinkite viena is galimu variantu:\n"
             << "1. Studento duomenis ivesti rankiniu budu.\n"
             << "2. Ivesti studento varda/pavarde rankiniu budu, o pazymius sugeneruoti atsitiktiniu budu.\n"
             << "3. Studento varda, pavarde, pazymius sugeneruoti atsitiktiniu budu\n"
             << "4. Baigti darba, rodyti rezultatus.\n"
             << "Iveskite pasirinkima: ";
        cin >> input;

        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 4) {
            cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 4: ";
            cin >> input;
        }
        meniuPasirinkimas = stoi(input);

        if (meniuPasirinkimas == 4) break;

        studentaiStruct studentas;

        if (meniuPasirinkimas == 1 || meniuPasirinkimas == 2) ivedimas(studentas);

        if (meniuPasirinkimas == 1) {
            studentas.T = new int[10];
            int allocatedSize = 10;
            cout << "Iveskite namu darbu rezultatus (-1, kad sustabdyti ivedima):" << endl;
            while (true) {
                int score;
                cin >> score;
                if (score == -1) break;
                if (studentas.n == allocatedSize) {
                    int *temp = new int[allocatedSize * 2];
                    for (int i = 0; i < allocatedSize; i++) {
                        temp[i] = studentas.T[i];
                    }
                    delete[] studentas.T;
                    studentas.T = temp;
                    allocatedSize *= 2;
                }
                studentas.T[studentas.n++] = score;
                studentas.ndSuma += score;
            }
            cout << "Iveskite egzamino rezultata: ";
            cin >> studentas.egzas;
        } else if (meniuPasirinkimas == 2) {
            generavimas(studentas);
        } else if (meniuPasirinkimas == 3) {
            numberInputProtection(input);
            int randomNum = rand() % 100 + 1;
            studentas.vardas = "Vardas" + to_string(randomNum);
            studentas.pavarde = "Pavarde" + to_string(randomNum);
            generavimas(studentas);
        }

        maxVardoIlgis = max(maxVardoIlgis, (int)studentas.vardas.length());
        maxPavardesIlgis = max(maxPavardesIlgis, (int)studentas.pavarde.length());
        skaiciavimai(studentas);

        studentaiStruct *newArray = new studentaiStruct[mokSk + 1];
        for (int i = 0; i < mokSk; i++) {
            newArray[i] = students[i];
        }
        newArray[mokSk++] = studentas;
        delete[] students;
        students = newArray;
    }

    isvedimas(students, mokSk, maxVardoIlgis, maxPavardesIlgis);

    for (int i = 0; i < mokSk; i++) {
        delete[] students[i].T;
    }
    delete[] students;

    return 0;
}