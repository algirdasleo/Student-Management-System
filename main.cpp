#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

struct studentaiStruct {
    string vardas, pavarde;
    int n; 
    double* T; 
    double ndSuma, egzas, mediana, galutinisVid, galutinisMed;
};

bool isNumber(string &str) {
    for (char c : str)
        if (!isdigit(c) && c != '.')
            return false;
    return true;
}

bool isString(string &str) {
    for (char c : str)
        if (!isalpha(c))
            return false;
    return true;
}

int main() {
    int mokSk;
    string input;
    cout << "Iveskite mokiniu skaiciu:" << endl;
    cin >> input;
    while (!isNumber(input)) {
        cout << "Iveskite skaiciu, ne raides ar simbolius:" << endl;
        cin >> input;
    }
    mokSk = stoi(input);

    studentaiStruct* st = new studentaiStruct[mokSk]; 

    int maxVardoIlgis = 5;    
    int maxPavardesIlgis = 6; 

    for (int i = 0; i < mokSk; i++) {
        st[i].ndSuma = 0;

        cout << "Iveskite mokinio varda:" << endl;
        cin >> input;
        while (!isString(input)) {
            cout << "Ivestas ne vardas. Iveskite varda:" << endl;
            cin >> input;
        }
        st[i].vardas = input;

        cout << "Iveskite mokinio pavarde:" << endl;
        cin >> input;
        while (!isString(input)) {
            cout << "Ivesta ne pavarde. Iveskite pavarde:" << endl;
            cin >> input;
        }
        st[i].pavarde = input;

        maxVardoIlgis = max(maxVardoIlgis, int(st[i].vardas.length()));
        maxPavardesIlgis = max(maxPavardesIlgis, int(st[i].pavarde.length()));

        cout << "Iveskite namu darbu kieki:" << endl;
        cin >> input;
        while (!isNumber(input) || stoi(input) < 1) {
            cout << "Iveskite teigiama skaiciu:" << endl;
            cin >> input;
        }
        st[i].n = stoi(input);
        
        st[i].T = new double[st[i].n];

        for (int j = 0; j < st[i].n; j++) {
            cout << "Iveskite " << j + 1 << " namu darbo rezultata:" << endl;
            cin >> input;
            while (!isNumber(input) || stod(input) < 1 || stod(input) > 10) {
                cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
                cin >> input;
            }
            st[i].T[j] = stod(input);
            st[i].ndSuma += st[i].T[j];
        }

        sort(st[i].T, st[i].T + st[i].n);

        if (st[i].n % 2 == 0)
            st[i].mediana = (st[i].T[st[i].n / 2] + st[i].T[st[i].n / 2 - 1]) / 2.0;
        else
            st[i].mediana = st[i].T[st[i].n / 2];

        cout << "Iveskite egzamino rezultata:" << endl;
        cin >> input;
        while (!isNumber(input) || stod(input) < 1 || stod(input) > 10) {
            cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
            cin >> input;
        }
        st[i].egzas = stod(input);

        st[i].galutinisVid = 0.4 * (st[i].ndSuma / st[i].n) + 0.6 * st[i].egzas;
        st[i].galutinisMed = 0.4 * st[i].mediana + 0.6 * st[i].egzas;
    }

    cout << left << setw(maxPavardesIlgis + 2) << "Pavarde" << setw(maxVardoIlgis + 2) << "Vardas"
         << setw(17) << "Galutinis(Vid.)" << setw(17) << "Galutinis(Med.)" << endl;
    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < mokSk; i++) {
        cout << left << setw(maxPavardesIlgis + 2) << st[i].pavarde << setw(maxVardoIlgis + 2) << st[i].vardas
             << setw(17) << fixed << setprecision(2) << st[i].galutinisVid
             << setw(17) << fixed << setprecision(2) << st[i].galutinisMed << endl;

        delete[] st[i].T;
    }

    delete[] st;

    return 0;
}

