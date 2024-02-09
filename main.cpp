#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

struct studentaiStruct {
    string vardas, pavarde;
    int n; // namu darbu kiekis
    int T[10]; // namu darbu rezultatai
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
} st[100]; // studentu struct masyvas

int main() {
    int mokSk;

    int maxVardoIlgis = 6, maxPavardesIlgis = 7; 

    char pasirinkimas = 'y';
    int i = 0;
    while (pasirinkimas == 'y') {
        st[i].ndSuma = 0;

        cout << "Iveskite savo varda:" << endl;
        cin >> st[i].vardas;
        cout << "Iveskite savo pavarde:" << endl;
        cin >> st[i].pavarde;

        int vardoIlgis = st[i].vardas.length();
        int pavardesIlgis = st[i].pavarde.length();
        maxVardoIlgis = max(maxVardoIlgis, vardoIlgis);
        maxPavardesIlgis = max(maxPavardesIlgis, pavardesIlgis);

        cout << "Iveskite namu darbu kieki: (max: 10 nd.)" << endl;
        cin >> st[i].n;

        for (int j = 0; j < st[i].n; j++) {
            cout << "Iveskite " << j + 1 << " namu darbo rezultata:" << endl;
            cin >> st[i].T[j];
            st[i].ndSuma += st[i].T[j];
        }
        sort(st[i].T, st[i].T + st[i].n);

        if (st[i].n % 2 == 0)
            st[i].mediana = (st[i].T[(st[i].n / 2)] + st[i].T[(st[i].n / 2) - 1]) / 2.0;
        else
            st[i].mediana = st[i].T[st[i].n / 2];

        cout << "Iveskite egzamino rezultata:" << endl;
        cin >> st[i].egzas;

        st[i].galutinisVid = 0.4 * (st[i].ndSuma / st[i].n) + 0.6 * st[i].egzas;
        st[i].galutinisMed = 0.4 * st[i].mediana + 0.6 * st[i].egzas;

        cout << "Ar norite ivesti dar vieno mokinio duomenis? (y/n)" << endl;
        cin >> pasirinkimas;
        pasirinkimas = tolower(pasirinkimas);
        mokSk++;
        i++;
    }

    cout << left 
         << setw(maxPavardesIlgis + 2) << "Pavarde" 
         << setw(maxVardoIlgis + 2) << "Vardas" 
         << setw(17) << "Galutinis(Vid.)" 
         << setw(15) << "Galutinis(Med.)" << endl; 

    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl; 
    cout << setfill(' ');

    for (int i = 0; i < mokSk; i++) {
        cout << left 
             << setw(maxPavardesIlgis + 2) << st[i].pavarde
             << setw(maxVardoIlgis + 2) << st[i].vardas
             << setw(17) << fixed << setprecision(2) << st[i].galutinisVid
             << setw(15) << fixed << setprecision(2) << st[i].galutinisMed << endl;
    }
    return 0;
}
