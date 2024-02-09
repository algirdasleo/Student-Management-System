#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


struct studentaiStruct{
    string vardas, pavarde;
    int n;
    int T[10];
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
}Studentai[100];


int main()
{
    int mokSk;
    cout << "Iveskite mokiniu skaiciu:" << endl;
    cin >> mokSk;

    for (int i = 0; i < mokSk; i++){
        Studentai[i].ndSuma = 0;

        cout << "Iveskite savo varda:" << endl;
        cin >> Studentai[i].vardas;
        cout << "Iveskite savo pavarde:" << endl;
        cin >> Studentai[i].pavarde;
        cout << "Iveskite namu darbu kieki: (max: 10 nd.)" << endl;
        cin >> Studentai[i].n;

        int pazymys;
        for (int j = 0; j < Studentai[i].n; j++){
            cout << "Iveskite " << j+1 << " namu darbo rezultata:" << endl;
            cin >> pazymys;
            Studentai[i].ndSuma += pazymys;
            Studentai[i].T[j] = pazymys;
        }
        sort(begin(Studentai[i].T), begin(Studentai[i].T) + Studentai[i].n);

        if (Studentai[i].n%2 == 0)
            Studentai[i].mediana = (Studentai[i].T[(Studentai[i].n / 2)] + Studentai[i].T[(Studentai[i].n / 2) -1]) / 2;
        else
            Studentai[i].mediana = Studentai[i].T[Studentai[i].n / 2];

        cout << "Iveskite egzamino rezultata:" << endl;
        cin >> Studentai[i].egzas;

        Studentai[i].galutinisVid = 0.4 * (Studentai[i].ndSuma / Studentai[i].n) + 0.6* Studentai[i].egzas;
        Studentai[i].galutinisMed = 0.4 * Studentai[i].mediana + 0.6 * Studentai[i].egzas;
    }

    cout << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis(Vid.)" << setw(20) << "Galutinis(Med.)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (int i = 0; i < mokSk; i++){
        cout << Studentai[i].pavarde << setw(18) << Studentai[i].vardas << setw(20) << Studentai[i].galutinisVid << setw(20) << Studentai[i].galutinisMed << endl;
    }


    return 0;
}
