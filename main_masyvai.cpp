#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

struct studentaiStruct
{
    string vardas, pavarde;
    int n;     // namu darbu kiekis
    int T[10]; // namu darbu rezultatai
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
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

void ivedimas(studentaiStruct &studentas)
{
    string input;
    cout << "Iveskite studento varda:" << endl;
    cin >> input;
    while (!isString(input))
    {
        cout << "Ivestas ne vardas. Iveskite varda:" << endl;
        cin >> input;
    }
    studentas.vardas = input;
    cout << "Iveskite studento pavarde:" << endl;
    cin >> input;
    while (!isString(input))
    {
        cout << "Ivesta ne pavarde. Iveskite pavarde:" << endl;
        cin >> input;
    }
    studentas.pavarde = input;
}

void numberInputProtection(string &input)
{
    while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10)
    {
        cout << "Iveskite skaiciu nuo 1 - 10:" << endl;
        cin >> input;
    }
}

void charInputProtection(string &input)
{
    while (input.length() > 1 && input != "n" && input != "y")
    {
        cout << "Neteisingas pasirinkimas. Iveskite 'y' arba 'n':" << endl;
        cin >> input;
    }
}

void skaiciavimai(studentaiStruct &studentas)
{
    sort(studentas.T, studentas.T + studentas.n);
    if (studentas.n % 2 == 0)
        studentas.mediana = (studentas.T[studentas.n / 2] + studentas.T[(studentas.n / 2) - 1]) / 2.0;
    else
        studentas.mediana = studentas.T[studentas.n / 2];

    studentas.galutinisVid = 0.4 * (studentas.ndSuma / studentas.n) + 0.6 * studentas.egzas;
    studentas.galutinisMed = 0.4 * studentas.mediana + 0.6 * studentas.egzas;
}

void generavimas(studentaiStruct &studentas)
{
    studentas.n = 10;
    for (int i = 0; i < studentas.n; i++)
    {
        studentas.T[i] = rand() % 10 + 1;
        studentas.ndSuma += studentas.T[i];
    }
    studentas.egzas = rand() % 10 + 1;
}

void isvedimas(studentaiStruct &studentas, int mokSk, int maxVardoIlgis, int maxPavardesIlgis)
{
    cout << left
         << setw(maxPavardesIlgis + 2) << "Pavarde"
         << setw(maxVardoIlgis + 2) << "Vardas"
         << setw(17) << "Galutinis(Vid.)"
         << setw(15) << "Galutinis(Med.)" << endl;

    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < mokSk; i++)
    {
        cout << left
             << setw(maxPavardesIlgis + 2) << st[i].pavarde
             << setw(maxVardoIlgis + 2) << st[i].vardas
             << setw(17) << fixed << setprecision(2) << st[i].galutinisVid
             << setw(15) << fixed << setprecision(2) << st[i].galutinisMed << endl;
    }
}

int main()
{
    srand(time(nullptr));
    int mokSk = 0, maxVardoIlgis = 6, maxPavardesIlgis = 7;
    string input;
    int meniuPasirinkimas;
    while (true)
    {
        cout << "Meniu. Pasirinkite viena is galimu variantu:\n"
             << "1. Studento duomenis ivesti rankiniu budu.\n"
             << "2. Ivesti studento varda/pavarde rankiniu budu, o pazymius sugeneruoti atsitiktiniu budu.\n"
             << "3. Studento varda, pavarde, pazymius sugeneruoti atsitiktiniu budu\n"
             << "4. Baigti darba, rodyti rezultatus.\n"
             << "Iveskite pasirinkima: \n";
        cin >> input;

        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 4)
        {
            cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 4:" << endl;
            cin >> input;
        }
        meniuPasirinkimas = stoi(input);
        if (meniuPasirinkimas == 4)
            break;

        studentaiStruct &studentas = st[mokSk];
        studentas.ndSuma = 0;
        studentas.n = 0;

        if (meniuPasirinkimas == 1 || meniuPasirinkimas == 2)
            ivedimas(studentas);

        if (meniuPasirinkimas == 1)
        {
            while (true && studentas.n < 10)
            {
                cout << "Iveskite " << studentas.n + 1 << " namu darbo rezultata (1 - 10): " << endl;
                cin >> input;
                numberInputProtection(input);

                studentas.T[studentas.n] = stoi(input);
                studentas.ndSuma += studentas.T[studentas.n];
                studentas.n++;

                if (studentas.n < 10)
                {
                    cout << "Ar norite ivesti dar viena namu darbo rezultata? (max 10) (y/n) " << endl;
                    cin >> input;
                    charInputProtection(input);
                    if (input == "n")
                        break;
                }
            }
            cout << "Iveskite egzamino rezultata (1-10):" << endl;
            cin >> input;
            numberInputProtection(input);

            studentas.egzas = stoi(input);
        }
        if (meniuPasirinkimas == 2)
        {
            generavimas(studentas);
            cout << "Studento pazymiai sugeneruoti atsitiktinai.\n \n";
        }
        else if (meniuPasirinkimas == 3)
        {
            studentas.vardas = "Vardas" + to_string(mokSk + 1);
            studentas.pavarde = "Pavarde" + to_string(mokSk + 1);

            generavimas(studentas);
            cout << "Studento duomenys sugeneruoti atsitiktinai. \n \n";
        }

        maxVardoIlgis = max(maxVardoIlgis, int(studentas.vardas.length()));
        maxPavardesIlgis = max(maxPavardesIlgis, int(studentas.pavarde.length()));
        skaiciavimai(studentas);
        mokSk++;
    }

    isvedimas(st[0], mokSk, maxVardoIlgis, maxPavardesIlgis);
    return 0;
}
