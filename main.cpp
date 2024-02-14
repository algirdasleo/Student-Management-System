#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

struct studentaiStruct
{
    string vardas, pavarde;
    int n;     // namu darbu kiekis
    int T[10]; // namu darbu rezultatai
    double ndSuma, egzas, mediana, galutinisVid, galutinisMed;
} st[100]; // studentu struct masyvas

bool isNumber(string &str)
{
    for (char c : str)
        if (!isdigit(c))
            return false;
    return true;
}

bool isString(string &str)
{
    for (char c : str)
        if (!isalpha(c))
            return false;
    return true;
}

main()
{
    string input;
    int mokSk; // mokiniu skaicius
    cout << "Iveskite mokiniu skaiciu:" << endl;
    cin >> input;
    while (!isNumber(input))
    {
        cout << "Iveskite mokiniu skaiciu nuo 1 iki 100:" << endl;
        cin >> input;
    }
    mokSk = stoi(input);

    int maxVardoIlgis = 5;    // minimalus vardo ilgis
    int maxPavardesIlgis = 6; // minimalus pavardes ilgis

    for (int i = 0; i < mokSk; i++)
    {                     // ciklas, kuris kartojasi mokSk kartu, kur mokSk - mokiniu skaicius
        st[i].ndSuma = 0; // namu darbu pazymiu suma pradzioje lygi 0

        cout << "Iveskite mokinio varda:" << endl;
        cin >> input;
        while (!isString(input))
        {
            cout << "Ivestas ne vardas. Iveskite varda:" << endl;
            cin >> input;
        }
        st[i].vardas = input;
        cout << "Iveskite mokinio pavarde:" << endl;
        cin >> input;
        while (!isString(input))
        {
            cout << "Ivesta ne pavarde. Iveskite pavarde:" << endl;
            cin >> input;
        }
        st[i].pavarde = input;
        int vardoIlgis = st[i].vardas.length();
        int pavardesIlgis = st[i].pavarde.length();
        maxVardoIlgis = max(maxVardoIlgis, vardoIlgis);          // nustatomas maksimalus vardo ilgis
        maxPavardesIlgis = max(maxPavardesIlgis, pavardesIlgis); // nustatomas maksimalus pavardes ilgis

        cout << "Iveskite namu darbu kieki: (max: 10 nd.)" << endl;
        cin >> input;

        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10)
        {
            cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
            cin >> input;
        }
        st[i].n = stoi(input);

        for (int j = 0; j < st[i].n; j++)
        { // ciklas, kuris kartojasi n kartu, kur n - namu darbu kiekis
            cout << "Iveskite " << j + 1 << " namu darbo rezultata:" << endl;
            cin >> input;
            while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10)
            {
                cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
                cin >> input;
            }
            st[i].T[j] = stoi(input);
            st[i].ndSuma += st[i].T[j]; // pridedamas namu darbo rezultatas prie namu darbu pazymiu sumos
        }
        sort(st[i].T, st[i].T + st[i].n); // norint rasti mediana - reikia sortinti namu darbu rezultatus.
        // sortinamas nuo pradzios iki pradzios + studento namu darbu kiekio, kadangi fiksuotas T dydis - 10.

        if (st[i].n % 2 == 0) // jei namu darbu kiekis yra lyginis, tai mediana yra dvieju viduriniu skaiciu vidurkis
            st[i].mediana = (st[i].T[(st[i].n / 2)] + st[i].T[(st[i].n / 2) - 1]) / 2.0;
        else // jei namu darbu kiekis yra nelyginis, tai mediana yra vidurinis skaicius
            st[i].mediana = st[i].T[st[i].n / 2];

        cout << "Iveskite egzamino rezultata:" << endl;
        cin >> input;
        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10)
        {
            cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
            cin >> input;
        }
        st[i].egzas = stoi(input);

        st[i].galutinisVid = 0.4 * (st[i].ndSuma / st[i].n) + 0.6 * st[i].egzas; // galutinio pazymio skaiciavimas pagal vidurki
        st[i].galutinisMed = 0.4 * st[i].mediana + 0.6 * st[i].egzas;            // galutinio pazymio skaiciavimas pagal mediana
    }
    // isvedimas
    cout << left                                    // kairysis teksto lygiavimas
         << setw(maxPavardesIlgis + 2) << "Pavarde" // pavardei priskiriama maxPavardesIlgis + 2 vietos.
         << setw(maxVardoIlgis + 2) << "Vardas"     // vardui priskiriama maxVardoIlgis + 2 vietos.
         << setw(17) << "Galutinis(Vid.)"           // Galutinis(Vid.) uzima 15 simboliu + 2 = 17.
         << setw(17) << "Galutinis(Med.)" << endl;  // Galutinis(Med.) uzima 15 simboliu + 2 = 17.

    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl; // linija, kuri atskiria pavadinimus nuo duomenu
    cout << setfill(' ');                                                               // grazinamas defaultinis setfill simbolis

    for (int i = 0; i < mokSk; i++)
    {
        cout << left
             << setw(maxPavardesIlgis + 2) << st[i].pavarde                         // pavardei priskiriama maxPavardesIlgis + 2 vietos.
             << setw(maxVardoIlgis + 2) << st[i].vardas                             // vardui priskiriama maxVardoIlgis + 2 vietos.
             << setw(17) << fixed << setprecision(2) << st[i].galutinisVid          // galutinio vidurkio isvedimas su 2 skaiciais po kablelio
             << setw(15) << fixed << setprecision(2) << st[i].galutinisMed << endl; // galutinio vidurkio (naudojantis mediana) pazymio isvedimas su 2 skaiciais po kablelio
    }
    return 0;
}
