#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct studentaiStruct
{
    string vardas, pavarde;
    vector<int> nd;
    double ndSuma, egzas, galutinisVid, mediana, galutinisMed;
};

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
void skaiciavimai(studentaiStruct &studentas)
{
    int ndKiekis = studentas.nd.size();
    sort(studentas.nd.begin(), studentas.nd.end());
    if (ndKiekis % 2 == 0)
        studentas.mediana = (studentas.nd[ndKiekis / 2] + studentas.nd[(ndKiekis / 2) - 1]) / 2.0;
    else
        studentas.mediana = studentas.nd[ndKiekis / 2];
    studentas.galutinisVid = 0.4 * (studentas.ndSuma / ndKiekis) + 0.6 * studentas.egzas;
    studentas.galutinisMed = 0.4 * studentas.mediana + 0.6 * studentas.egzas;
}

void vardoIvedimas(studentaiStruct &studentas)
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

void isvedimas(vector<studentaiStruct> &stud, int maxVardoIlgis, int maxPavardesIlgis)
{
    cout << left
         << setw(maxPavardesIlgis + 2) << "Pavarde"
         << setw(maxVardoIlgis + 2) << "Vardas"
         << setw(17) << "Galutinis(Vid.)"
         << setw(15) << "Galutinis(Med.)" << endl;

    cout << setfill('-') << setw(maxPavardesIlgis + maxVardoIlgis + 34) << "-" << endl;
    cout << setfill(' ');

    for (const auto &student : stud)
    {
        cout << setw(maxPavardesIlgis + 2) << student.pavarde
             << setw(maxVardoIlgis + 2) << student.vardas
             << setw(17) << fixed << setprecision(2) << student.galutinisVid
             << setw(15) << fixed << setprecision(2) << student.galutinisMed << endl;
    }
}

int main()
{
    vector<studentaiStruct> stud;
    srand(time(nullptr));
    int maxVardoIlgis = 6, maxPavardesIlgis = 7;
    string input;
    int meniuPasirinkimas;
    while (true)
    {
        studentaiStruct studentas;
        studentas.ndSuma = 0;

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

        if (meniuPasirinkimas == 1 || meniuPasirinkimas == 2)
            vardoIvedimas(studentas);

        if (meniuPasirinkimas == 1)
        {
            int i = 0;
            while (true)
            {
                cout << "Iveskite " << i + 1 << " namu darbo rezultata (1 - 10):" << endl;
                cin >> input;
                numberInputProtection(input);
                studentas.nd.push_back(stoi(input));
                studentas.ndSuma += stoi(input);
                cout << "Ar norite ivesti dar viena namu darbo rezultata? (y / n)" << endl;
                cin >> input;
                charInputProtection(input);
                if (input == "n")
                    break;
                i++;
            }
            cout << "Iveskite egzamino rezultata (1 - 10):" << endl;
            cin >> input;
            numberInputProtection(input);
            studentas.egzas = stoi(input);
            skaiciavimai(studentas);
            stud.push_back(studentas);
        }
        else if (meniuPasirinkimas == 2)
        {
            studentas.nd.resize(10);
            for (int i = 0; i < 10; i++)
            {
                studentas.nd[i] = rand() % 10 + 1;
                studentas.ndSuma += studentas.nd[i];
            }
            studentas.egzas = rand() % 10 + 1;
            skaiciavimai(studentas);
            stud.push_back(studentas);
            cout << "Studento pazymiai sugeneruoti atsitiktinai.\n \n";
        }
        else if (meniuPasirinkimas == 3)
        {
            studentas.vardas = "Vardas" + to_string(stud.size() + 1);
            studentas.pavarde = "Pavarde" + to_string(stud.size() + 1);
            studentas.nd.resize(10);
            for (int i = 0; i < 10; i++)
            {
                studentas.nd[i] = rand() % 10 + 1;
                studentas.ndSuma += studentas.nd[i];
            }
            studentas.egzas = rand() % 10 + 1;
            skaiciavimai(studentas);
            stud.push_back(studentas);
            cout << "Studento duomenys sugeneruoti atsitiktinai. \n \n";
        }
        maxVardoIlgis = max(maxVardoIlgis, int(studentas.vardas.length()));
        maxPavardesIlgis = max(maxPavardesIlgis, int(studentas.pavarde.length()));
    }

    isvedimas(stud, maxVardoIlgis, maxPavardesIlgis);
    return 0;
}
