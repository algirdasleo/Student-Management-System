#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct studentaiStruct {
    string vardas, pavarde;
    vector<int> nd;
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
};
vector<studentaiStruct> stud;

int main() {
    srand(time(nullptr));
    int maxVardoIlgis = 6, maxPavardesIlgis = 7; 

    while (true) {
        studentaiStruct studentas;
        studentas.ndSuma = 0;

        cout << "Iveskite savo varda:" << endl;
        cin >> studentas.vardas;
        cout << "Iveskite savo pavarde:" << endl;
        cin >> studentas.pavarde;

        int vardoIlgis = studentas.vardas.length();
        int pavardesIlgis = studentas.pavarde.length();
        maxVardoIlgis = max(maxVardoIlgis, vardoIlgis);
        maxPavardesIlgis = max(maxPavardesIlgis, pavardesIlgis);

        char pasirinkimas;
        int i = 0;
        while (true) {
            int ndRezultatas;
            cout << "Iveskite " << i + 1 << " namu darbo rezultata:" << endl;
            cin >> ndRezultatas;
            studentas.nd.push_back(ndRezultatas);
            studentas.ndSuma += ndRezultatas;
            cout << "Ar norite ivesti dar viena namu darbo rezultata? (y/n)" << endl;
            cin >> pasirinkimas;
            pasirinkimas = tolower(pasirinkimas);
            if (pasirinkimas == 'n')
                break;
            i++;
        }
        sort(studentas.nd.begin(), studentas.nd.end());

        int ndKiekis = studentas.nd.size();
        if (ndKiekis % 2 == 0)
            studentas.mediana = (studentas.nd[ndKiekis / 2] + studentas.nd[(ndKiekis / 2) - 1]) / 2.0;
        else
            studentas.mediana = studentas.nd[ndKiekis / 2];

        cout << "Iveskite egzamino rezultata:" << endl;
        cin >> studentas.egzas;

        studentas.galutinisVid = 0.4 * (studentas.ndSuma / ndKiekis) + 0.6 * studentas.egzas;
        studentas.galutinisMed = 0.4 * studentas.mediana + 0.6 * studentas.egzas;

        stud.push_back(studentas);

        cout << "Ar norite ivesti dar vieno mokinio duomenis? (y/n)" << endl;
        cin >> pasirinkimas;
        pasirinkimas = tolower(pasirinkimas);
        if (pasirinkimas == 'n')
            break;
    }

    cout << left 
         << setw(maxPavardesIlgis + 2) << "Pavarde" 
         << setw(maxVardoIlgis + 2) << "Vardas" 
         << setw(17) << "Galutinis(Vid.)" 
         << setw(15) << "Galutinis(Med.)" << endl; 

    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl; 
    cout << setfill(' ');

    for (const auto& student : stud) {
        cout << setw(maxPavardesIlgis + 2) << student.pavarde
             << setw(maxVardoIlgis + 2) << student.vardas
             << setw(17) << fixed << setprecision(2) << student.galutinisVid
             << setw(15) << fixed << setprecision(2) << student.galutinisMed << endl;
    }

    return 0;
}
