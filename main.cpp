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

int main() {
    try {
        std::cout << "Testing students class.\n";
        testStudentasClass();
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    clock_t start = clock();
    StudentasManager manager;
    while (true) {
        int meniuPasirinkimas;
        std::string input;
        std::cout << "\nMeniu. Pasirinkite viena is galimu variantu:\n"
                  << "1. Studento duomenis ivesti rankiniu budu.\n"
                  << "2. Ivesti studento varda/pavarde rankiniu budu, o pazymius sugeneruoti atsitiktiniu budu.\n"
                  << "3. Studento varda, pavarde, pazymius sugeneruoti atsitiktiniu budu\n"
                  << "4. Nuskaityti studentu duomenis is failo.\n"
                  << "5. Sugeneruoti studentu duomenu faila.\n"
                  << "6. Baigti darba.\n\n"
                  << "|- Iveskite pasirinkima:\n";
        std::cin >> input;
        std::cout << std::endl;

        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 6) {
            std::cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 6:" << std::endl;
            std::cin >> input;
        }

        int exit;
        meniuPasirinkimas = stoi(input);
        if (meniuPasirinkimas == 6)
            break;
        exit = (meniuPasirinkimas == 6);

        Studentas st;
        srand(time(nullptr));
        if (!exit) {
            switch (meniuPasirinkimas) {
                // Read student data
                case 1: {
                    std::cout << "1. STUDENTO DUOMENU IVEDIMAS\n";
                    st.readName();
                    int i = 0;
                    while (true) {
                        std::cout << "Iveskite " << i + 1 << " namu darbo rezultata (1 - 10):" << std::endl;
                        std::cin >> input;
                        numberInputProtection(input);
                        st.addGrade(stoi(input));
                        std::cout << "Ar norite ivesti dar viena namu darbo rezultata? (y / n)" << std::endl;
                        std::cin >> input;
                        charInputProtection(input);
                        if (input == "n")
                            break;
                        i++;
                    }
                    std::cout << "Iveskite egzamino rezultata (1 - 10):" << std::endl;
                    std::cin >> input;
                    numberInputProtection(input);
                    st.setEgz(stoi(input));
                    st.calculate();
                    manager.addStudent(st);
                    break;
                }
                // Generate student grades
                case 2: {
                    std::cout << "2. VARDO, PAVARDES IVEDIMAS. PAZYMIU GENERAVIMAS. \n";
                    st.readName();
                    for (int i = 0; i < 10; i++) {
                        int random_grade = rand() % 10 + 1;
                        st.addGrade(random_grade);
                    }
                    st.setEgz(rand() % 10 + 1);
                    st.calculate();
                    manager.addStudent(st);
                    std::cout << "Studento pazymiai sugeneruoti atsitiktinai.\n \n";
                    break;
                }
                // Generate student data
                case 3: {
                    std::cout << "3. STUDENTU DUOMENU GENERAVIMAS\n";
                    std::cout << "Kiek studentu sugeneruoti?" << std::endl;
                    std::cin >> input;
                    while (!isNumber(input) || stoi(input) < 1) {
                        std::cout << "Neteisingas pasirinkimas. Iveskite skaiciu didesni uz 0:" << std::endl;
                        std::cin >> input;
                    }

                    int kiek = stoi(input);
                    for (int i = 0; i < kiek; i++) {
                        int size = manager.getStudentListSize();
                        st.setName("Vardas" + std::to_string(size + 1));
                        st.setSurname("Pavarde" + std::to_string(size + 1));
                        for (int i = 0; i < 10; i++)
                            st.addGrade(rand() % 10 + 1);

                        st.setEgz(rand() % 10 + 1);
                        st.calculate();
                        manager.addStudent(st);                   }
                    std::cout << "Studento duomenys sugeneruoti atsitiktinai. \n \n";
                    break;
                }
                // Read data from file
                case 4: {
                    std::ifstream in;
                    std::cout << "4. DUOMENU NUSKAITYMAS. \n";
                    while (true) {
                        std::cout << "Iveskite tikslu file pavadinima (pvz. 'kursiokai.txt'):" << std::endl;
                        std::cin >> input;

                        in.open(input);

                        if (!in) {
                            std::cout << "Failas '" << input << "' nerastas. Bandykite dar karta." << std::endl;
                            in.clear();
                        } else {
                            break;
                        }
                    }
                    manager.readFromFile(input);

                    std::cout << "\nAr norite RUSIUOTI studentus i ISLAIKIUSIUS ir NEISLAIKIUSIUS? (y / n)" << std::endl;
                    std::cin >> input;
                    charInputProtection(input);
                    if (input == "y") {
                        clock_t start4 = clock();
                        std::list<Studentas> neislaike;
                        manager.sortIntoGroups(neislaike);

                        char pasirinkimas, rusiavimas;
                        howToSort(pasirinkimas, rusiavimas);
                        manager.sortStudents(pasirinkimas, rusiavimas, neislaike);
                        clock_t start5 = clock();
                        manager.printToFile("islaike.txt");
                        manager.printToFile("neislaike.txt", neislaike);

                        std::cout << "\nRezultatai isvesti i failus per " << double(clock() - start5) / CLOCKS_PER_SEC << " sekundziu.\n\n";
                    } else { 
                        char pasirinkimas, rusiavimas;
                        howToSort(pasirinkimas, rusiavimas);
                        manager.sortStudents(pasirinkimas, rusiavimas);
                        clock_t start6 = clock();
                        manager.printToFile();
                        std::cout << "Rezultatai isvesti i faila 'rezultatas.txt' per " << double(clock() - start6) / CLOCKS_PER_SEC << " sekundziu.\n\n";
                    }

                    break;
                }
                // Generate data files
                case 5: {
                    std::cout << "5. FAILU GENERAVIMAS\n";
                    std::cout << "1 - Nurodyti studentu kieki \n"
                              << "2 - Sugeneruoti 5 failus (1'000 / 10'000 / 100'000 / 1'000'000 / 10'000'000 dydzio)\n"
                              << "Iveskite pasirinkima (1 arba 2): \n";
                    std::cin >> input;
                    while (input != "1" && input != "2") {
                        std::cout << "Neteisingas pasirinkimas. Iveskite 1 arba 2:" << std::endl;
                        std::cin >> input;
                    }

                    int pasirinkimas = stoi(input);
                    if (pasirinkimas == 1) {
                        std::cout << "Iveskite studentu kieki (nuo 1 iki 10000000):" << std::endl;
                        std::cin >> input;
                        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10000000) {
                            std::cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 10'000'000:" << std::endl;
                            std::cin >> input;
                        }
                        int kiekis = stoi(input);

                        std::cout << "Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << std::endl;
                        std::cin >> input;
                        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
                            std::cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << std::endl;
                            std::cin >> input;
                        }
                        int pazymiuKiekis = stoi(input);

                        generateFile(kiekis, pazymiuKiekis);

                    } else if (pasirinkimas == 2) {
                        std::cout << "Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << std::endl;
                        std::cin >> input;
                        while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
                            std::cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << std::endl;
                            std::cin >> input;
                        }
                        int pazymiuKiekis = stoi(input);
                        clock_t start3 = clock();
                        generateFile(1000, pazymiuKiekis);
                        generateFile(10000, pazymiuKiekis);
                        generateFile(100000, pazymiuKiekis);
                        generateFile(1000000, pazymiuKiekis);
                        generateFile(10000000, pazymiuKiekis);
                        std::cout << "Failai sugeneruoti per " << double(clock() - start3) / CLOCKS_PER_SEC << " sekundziu.\n\n";
                    }
                    break;
                }
            }
        }
    }
    if (manager.getStudentListSize() == 0) {
        std::cout << "Programa baige darba." << std::endl;
        return 0;
    }
        std::cout << "Programa uztruko: " << double(clock() - start) / CLOCKS_PER_SEC << " sekundziu." << std::endl;

    return 0;
}
