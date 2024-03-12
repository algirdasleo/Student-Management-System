#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "functions.h"
using namespace std;

int main() {
    clock_t start = clock();
    list<Studentas> studList;
    srand(time(nullptr));
    int maxVardoIlgis = 6, maxPavardesIlgis = 7;
    string input;
    int meniuPasirinkimas;
    while (true) {
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

        Studentas st;

        if (meniuPasirinkimas == 1) {
            cout << "1. STUDENTO DUOMENU IVEDIMAS\n";
            st.readName();
            int i = 0;
            while (true) {
                cout << "Iveskite " << i + 1 << " namu darbo rezultata (1 - 10):" << endl;
                cin >> input;
                numberInputProtection(input);
                st.addGrade(stoi(input));
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
            st.setEgz(stoi(input));
            st.calculate();
            studList.push_back(st);
        } else if (meniuPasirinkimas == 2) {
            cout << "2. VARDO, PAVARDES IVEDIMAS. PAZYMIU GENERAVIMAS. \n";
            st.readName();
            for (int i = 0; i < 10; i++) {
                int random_grade = rand() % 10 + 1;
                st.addGrade(random_grade);
            }
            st.setEgz(rand() % 10 + 1);
            st.calculate();
            studList.push_back(st);
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
                st.setName("Vardas" + to_string(studList.size() + 1));
                st.setSurname("Pavarde" + to_string(studList.size() + 1));
                for (int i = 0; i < 10; i++)
                    st.addGrade(rand() % 10 + 1);

                st.setEgz(rand() % 10 + 1);
                st.calculate();
                studList.push_back(st);
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
            list<Studentas> failoStud;
            st.readFromFile(failoStud, input, maxVardoIlgis, maxPavardesIlgis);

            if (!studList.empty()) {
                cout << "Ar norite prideti savo anksciau ivestu ar generuotu studentu duomenis? (y / n)" << endl;
                cin >> input;
                charInputProtection(input);
                if (input == "y") {
                    for (auto &st : studList) {
                        failoStud.push_back(st);
                    }
                    studList.clear();
                }
            }

            cout << "Ar norite rusiuoti studentus i islaikiusius ir neislaikiusius? (y / n)" << endl;
            cin >> input;
            charInputProtection(input);
            if (input == "y") {
                clock_t start4 = clock();
                list<Studentas> neislaike;
                st.sortIntoGroups(failoStud, neislaike);

                char pasirinkimas, rusiavimas;
                howToSort(pasirinkimas, rusiavimas);
                Studentas::sorting(failoStud, pasirinkimas, rusiavimas);
                Studentas::sorting(neislaike, pasirinkimas, rusiavimas);
                clock_t start5 = clock();
                Studentas::printToFile(failoStud, maxVardoIlgis, maxPavardesIlgis, "islaike.txt");
                Studentas::printToFile(neislaike, maxVardoIlgis, maxPavardesIlgis, "neislaike.txt");

                cout << "Rezultatai isvesti i failus per " << double(clock() - start5) / CLOCKS_PER_SEC << " sekundziu.\n\n";
            } else {
                char pasirinkimas, rusiavimas;
                howToSort(pasirinkimas, rusiavimas);
                Studentas::sorting(failoStud, pasirinkimas, rusiavimas);
                clock_t start6 = clock();
                Studentas::printToFile(failoStud, maxVardoIlgis, maxPavardesIlgis);
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

                generateFile(kiekis, pazymiuKiekis);

            } else if (pasirinkimas == 2) {
                cout << "Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << endl;
                cin >> input;
                while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
                    cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << endl;
                    cin >> input;
                }
                int pazymiuKiekis = stoi(input);
                clock_t start3 = clock();
                generateFile(1000, pazymiuKiekis);
                generateFile(10000, pazymiuKiekis);
                generateFile(100000, pazymiuKiekis);
                generateFile(1000000, pazymiuKiekis);
                generateFile(10000000, pazymiuKiekis);
                cout << "Failai sugeneruoti per " << double(clock() - start3) / CLOCKS_PER_SEC << " sekundziu.\n\n";
            }
        }

        if (meniuPasirinkimas > 0 && meniuPasirinkimas < 5) {
            string vardas = st.getName();
            string pavarde = st.getSurname();
            maxVardoIlgis = max(maxVardoIlgis, int(vardas.length()));
            maxPavardesIlgis = max(maxPavardesIlgis, int(pavarde.length()));
        }
    }
    if (!studList.empty())
        Studentas::printToFile(studList, maxVardoIlgis, maxPavardesIlgis);
    cout << "Programa uztruko: " << clock() - start << " sekundziu." << endl;
    return 0;
}
