#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "functions.h"
using namespace std;

int main() {
    clock_t start = clock();
    vector<studentaiStruct> stud;
    srand(time(nullptr));
    int maxVardoIlgis = 6, maxPavardesIlgis = 7;
    string input;
    int meniuPasirinkimas;
    while (true) {
        studentaiStruct studentas;
        studentas.ndSuma = 0;

        cout << "Meniu. Pasirinkite viena is galimu variantu:\n"
             << "1. Studento duomenis ivesti rankiniu budu.\n"
             << "2. Ivesti studento varda/pavarde rankiniu budu, o pazymius sugeneruoti atsitiktiniu budu.\n"
             << "3. Studento varda, pavarde, pazymius sugeneruoti atsitiktiniu budu\n"
             << "4. Nuskaityti studentu duomenis is failo.\n"
             << "5. Sugeneruoti studentu duomenu faila.\n"
             << "6. Baigti darba, rodyti rezultatus.\n"
             << "Iveskite pasirinkima: \n";
        cin >> input;
        cout << endl;

        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 6) {
            cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 6:" << endl;
            cin >> input;
        }
        meniuPasirinkimas = stoi(input);
        if (meniuPasirinkimas == 6)
            break;

        if (meniuPasirinkimas == 1 || meniuPasirinkimas == 2)
            vardoIvedimas(studentas);

        if (meniuPasirinkimas == 1) {
            int i = 0;
            while (true) {
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
        } else if (meniuPasirinkimas == 2) {
            studentas.nd.resize(10);
            for (int i = 0; i < 10; i++) {
                studentas.nd[i] = rand() % 10 + 1;
                studentas.ndSuma += studentas.nd[i];
            }
            studentas.egzas = rand() % 10 + 1;
            skaiciavimai(studentas);
            stud.push_back(studentas);
            cout << "Studento pazymiai sugeneruoti atsitiktinai.\n \n";
        } else if (meniuPasirinkimas == 3) {
            cout << "Kiek studentu sugeneruoti?" << endl;
            cin >> input;
            while (!isNumber(input) || stoi(input) < 1) {
                cout << "Neteisingas pasirinkimas. Iveskite skaiciu didesni uz 0:" << endl;
                cin >> input;
            }

            int kiek = stoi(input);
            for (int i = 0; i < kiek; i++) {
                studentas.vardas = "Vardas" + to_string(stud.size() + 1);
                studentas.pavarde = "Pavarde" + to_string(stud.size() + 1);
                studentas.nd.resize(10);
                for (int i = 0; i < 10; i++) {
                    studentas.nd[i] = rand() % 10 + 1;
                    studentas.ndSuma += studentas.nd[i];
                }
                studentas.egzas = rand() % 10 + 1;
                skaiciavimai(studentas);
                stud.push_back(studentas);
            }
            cout << "Studento duomenys sugeneruoti atsitiktinai. \n \n";
        } else if (meniuPasirinkimas == 4) {
            cout << "Nuskaitomi studentu duomenys is failo...\n";
            clock_t start2 = clock();

            ifstream in("kursiokai.txt");
            try {
                if (!in)
                    throw runtime_error("Failas 'kursiokai.txt' nerastas.");
            } catch (const runtime_error &e) {
                cout << e.what() << endl;
                continue;
            }

            string vardas, pavarde, line;
            getline(in, line);
            while (in.peek() != EOF) {
                studentaiStruct studentas;
                in >> studentas.vardas >> studentas.pavarde;
                studentas.ndSuma = 0;
                int pazymys;
                while (in >> pazymys) {
                    studentas.nd.push_back(pazymys);
                    studentas.ndSuma += pazymys;
                    if (in.peek() == '\n')
                        break;
                }
                if (!studentas.nd.empty()) {
                    studentas.egzas = studentas.nd.back();
                    studentas.ndSuma -= studentas.egzas;
                    studentas.nd.pop_back();
                    skaiciavimai(studentas);
                }
                stud.push_back(studentas);
                maxVardoIlgis = max(maxVardoIlgis, int(studentas.vardas.length()));
                maxPavardesIlgis = max(maxPavardesIlgis, int(studentas.pavarde.length()));
            }

            in.close();
            clock_t end2 = clock();
            double laikas2 = double(end2 - start2) / CLOCKS_PER_SEC;
            cout << "Studentu duomenys nuskaityti is failo per " << laikas2 << " sekundziu.\n\n";
        } else if (meniuPasirinkimas == 5) {
            cout << "Ar norite nurodyti studentu kieki - 1 \n"
                 << "Ar norite sugeneruoti 5 failus (1'000 / 10'000 / 100'000 / 1'000'000 / 10'000'000 dydzio) - 2\n"
                 << "Iveskite pasirinkima (1 arba 2): \n";
            cin >> input;
            while (input != "1" && input != "2") {
                cout << "Neteisingas pasirinkimas. Iveskite 1 arba 2:" << endl;
                cin >> input;
            }

            int pasirinkimas = stoi(input);
            if (pasirinkimas == 1) {
                cout << "Iveskite studentu kieki (nuo 1 iki 10000000):" << endl;
                cin >> input;
                while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10000000) {
                    cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 10'000'000:" << endl;
                    cin >> input;
                }
                int kiekis = stoi(input);

                cout << "Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << endl;
                cin >> input;
                while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
                    cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << endl;
                    cin >> input;
                }
                int pazymiuKiekis = stoi(input);

                generuotiFaila(kiekis, pazymiuKiekis);

            } else if (pasirinkimas == 2) {
                cout << "Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << endl;
                cin >> input;
                while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
                    cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << endl;
                    cin >> input;
                }
                int pazymiuKiekis = stoi(input);
                clock_t start3 = clock();
                generuotiFaila(1000, pazymiuKiekis);
                generuotiFaila(10000, pazymiuKiekis);
                generuotiFaila(100000, pazymiuKiekis);
                generuotiFaila(1000000, pazymiuKiekis);
                generuotiFaila(10000000, pazymiuKiekis);
                cout << "Failai sugeneruoti per " << double(clock() - start3) / CLOCKS_PER_SEC << " sekundziu.\n\n";
            }
        }

        if (meniuPasirinkimas > 0 && meniuPasirinkimas < 5) {
            maxVardoIlgis = max(maxVardoIlgis, int(studentas.vardas.length()));
            maxPavardesIlgis = max(maxPavardesIlgis, int(studentas.pavarde.length()));
        }
    }

    clock_t end = clock();
    double laikas = double(end - start) / CLOCKS_PER_SEC;
    isvedimas(stud, maxVardoIlgis, maxPavardesIlgis);
    cout << "Programa uztruko: " << laikas << " sekundziu." << endl;
    return 0;
}
