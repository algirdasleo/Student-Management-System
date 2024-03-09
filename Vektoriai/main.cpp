#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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

        cout << "\nMeniu. Pasirinkite viena is galimu variantu:\n"
             << "1. Studento duomenis ivesti rankiniu budu.\n"
             << "2. Ivesti studento varda/pavarde rankiniu budu, o pazymius sugeneruoti atsitiktiniu budu.\n"
             << "3. Studento varda, pavarde, pazymius sugeneruoti atsitiktiniu budu\n"
             << "4. Nuskaityti studentu duomenis is failo.\n"
             << "5. Sugeneruoti studentu duomenu faila.\n"
             << "6. Baigti darba (rodyti rezultatus).\n\n"
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

        if (meniuPasirinkimas == 1) {
            cout << "1. STUDENTO DUOMENU IVEDIMAS\n";
            vardoIvedimas(studentas);
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
            cout << "2. VARDO, PAVARDES IVEDIMAS. PAZYMIU GENERAVIMAS. \n";
            vardoIvedimas(studentas);
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
            cout << "3. DUOMENU GENERAVIMAS\n";
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
            ifstream in;
            cout << "4. DUOMENU NUSKAITYMAS. \n";
            while (true) {
                cout << "Iveskite tikslu file pavadinima (pvz. 'kursiokai.txt'):" << endl;
                cin >> input;

                in.open(input);

                if (!in) {
                    cout << "Failas '" << input << "' nerastas. Bandykite dar karta." << endl;
                    in.clear();
                } else {
                    break;
                }
            }
            vector<studentaiStruct> failoStud;
            cout << "Ar zinote kiek studentu yra faile? (y / n)" << endl;
            cin >> input;
            charInputProtection(input);
            if (input == "y") {
                cout << "Iveskite studentu kieki:" << endl;
                cin >> input;
                while (!isNumber(input) || stoi(input) < 1) {
                    cout << "Neteisingas pasirinkimas. Iveskite skaiciu didesni uz 0:" << endl;
                    cin >> input;
                }
                int kiek = stoi(input);
                stud.reserve(kiek);
            }

            cout << "Nuskaitomi studentu duomenys is failo...\n";
            clock_t start2 = clock();
            string line;
            getline(in, line);
            while (getline(in, line)) {
                istringstream iss(line);
                studentaiStruct studentas;
                iss >> studentas.vardas >> studentas.pavarde;
                studentas.ndSuma = 0;
                int pazymys;
                while (iss >> pazymys) {
                    studentas.nd.push_back(pazymys);
                    studentas.ndSuma += pazymys;
                    if (iss.peek() == '\n') break;
                }
                if (!studentas.nd.empty()) {
                    studentas.egzas = studentas.nd.back();
                    studentas.nd.pop_back();
                    studentas.ndSuma -= studentas.egzas;
                    skaiciavimai(studentas);
                }
                maxVardoIlgis = max(maxVardoIlgis, int(studentas.vardas.length()));
                maxPavardesIlgis = max(maxPavardesIlgis, int(studentas.pavarde.length()));
                failoStud.push_back(move(studentas));
            }
            in.close();
            clock_t end2 = clock();
            double laikas2 = double(end2 - start2) / CLOCKS_PER_SEC;
            cout << "Studentu duomenys nuskaityti is failo per " << laikas2 << " sekundziu.\n\n";

            if (!stud.empty()) {
                cout << "Ar norite prideti savo anksciau ivestu ar generuotu studentu duomenis? (y / n)" << endl;
                cin >> input;
                charInputProtection(input);
                if (input == "y") {
                    for (auto &studentas : stud) {
                        failoStud.push_back(studentas);
                    }
                    stud.clear();
                }
            }

            cout << "Ar norite rusiuoti studentus i islaikiusius ir neislaikiusius? (y / n)" << endl;
            cin >> input;
            charInputProtection(input);
            if (input == "y") {
                clock_t start4 = clock();
                /* 1 STRATEGIJA
                vector<studentaiStruct> islaike, neislaike;
                for (auto &studentas : failoStud) {
                    if (studentas.galutinisVid >= 5 && studentas.galutinisMed >= 5)
                        islaike.push_back(studentas);
                    else
                        neislaike.push_back(studentas);
                }
                cout << "Studentai islaikyti ir neislaikyti surusiuoti per " << double(clock() - start4) / CLOCKS_PER_SEC << " sekundziu.\n\n";
                char pasirinkimas, rusiavimas;
                kaipRusiuoti(pasirinkimas, rusiavimas);
                isvedimoSortinimas(islaike, pasirinkimas, rusiavimas);
                isvedimoSortinimas(neislaike, pasirinkimas, rusiavimas);
                clock_t start5 = clock();
                isvedimas(islaike, maxVardoIlgis, maxPavardesIlgis, "islaike.txt");
                isvedimas(neislaike, maxVardoIlgis, maxPavardesIlgis, "neislaike.txt");
                */
                // 2 STRATEGIJA
                vector<studentaiStruct> neislaike;
                auto it = failoStud.begin();
                while (it != failoStud.end()) {
                    if (it->galutinisVid < 5 && it->galutinisMed < 5) {
                        neislaike.push_back(std::move(*it));
                        it = failoStud.erase(it);
                    } else {
                        ++it;
                    }
                }
                cout << "Studentai islaikyti ir neislaikyti surusiuoti per " << double(clock() - start4) / CLOCKS_PER_SEC << " sekundziu.\n\n";
                char pasirinkimas, rusiavimas;
                kaipRusiuoti(pasirinkimas, rusiavimas);
                isvedimoSortinimas(failoStud, pasirinkimas, rusiavimas);
                isvedimoSortinimas(neislaike, pasirinkimas, rusiavimas);
                clock_t start5 = clock();
                isvedimas(failoStud, maxVardoIlgis, maxPavardesIlgis, "islaike.txt");
                isvedimas(neislaike, maxVardoIlgis, maxPavardesIlgis, "neislaike.txt");
                cout << "Rezultatai isvesti i failus per " << double(clock() - start5) / CLOCKS_PER_SEC << " sekundziu.\n\n";
            } else {
                char pasirinkimas, rusiavimas;
                kaipRusiuoti(pasirinkimas, rusiavimas);
                isvedimoSortinimas(failoStud, pasirinkimas, rusiavimas);
                clock_t start6 = clock();
                isvedimas(failoStud, maxVardoIlgis, maxPavardesIlgis);
                cout << "Rezultatai isvesti i faila 'rezultatas.txt' per " << double(clock() - start6) / CLOCKS_PER_SEC << " sekundziu.\n\n";
            }

        } else if (meniuPasirinkimas == 5) {
            cout << "5. DUOMENU GENERAVIMAS\n";
            cout << "1 - Nurodyti studentu kieki \n"
                 << "2 - Sugeneruoti 5 failus (1'000 / 10'000 / 100'000 / 1'000'000 / 10'000'000 dydzio)\n"
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
    if (!stud.empty())
        isvedimas(stud, maxVardoIlgis, maxPavardesIlgis);
    cout << "Programa uztruko: " << laikas << " sekundziu." << endl;
    return 0;
}
