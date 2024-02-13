#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
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

void ivedimas(studentaiStruct &studentas)
{
    cout << "Iveskite studento varda:" << endl;
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde:" << endl;
    cin >> studentas.pavarde;
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
    int meniuPasirinkimas;
    while (true)
    {
        cout << "Meniu. Pasirinkite viena is galimu variantu:\n"
             << "1. Studento duomenis ivesti rankiniu budu.\n"
             << "2. Ivesti studento varda/pavarde rankiniu budu, o pazymius sugeneruoti atsitiktiniu budu.\n"
             << "3. Studento varda, pavarde, pazymius sugeneruoti atsitiktiniu budu\n"
             << "4. Baigti darba, rodyti rezultatus.\n"
             << "Iveskite pasirinkima: \n";
        cin >> meniuPasirinkimas;

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
                cout << "Iveskite " << studentas.n + 1 << " namu darbo rezultata: " << endl;
                cin >> studentas.T[studentas.n];
                studentas.ndSuma += studentas.T[studentas.n];
                studentas.n++;

                char pasirinkimas;
                if (studentas.n < 10)
                {
                    cout << "Ar norite ivesti dar viena namu darbo rezultata? (y/n) (max 10)" << endl;
                    cin >> pasirinkimas;
                    pasirinkimas = tolower(pasirinkimas);
                    if (pasirinkimas == 'n')
                        break;
                }
            }
            cout << "Iveskite egzamino rezultata:" << endl;
            cin >> studentas.egzas;
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
