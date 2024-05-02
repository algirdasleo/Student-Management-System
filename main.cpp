#include <algorithm>
#include <chrono>
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

    // Test the Studentas class
    Studentas st;
    try {
        std::cout << "Testing students class.\n";
        st.testStudentasClass();
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    StudentasManager manager;
    while (true) {
        int meniuPasirinkimas = getMenuChoice();
        if (meniuPasirinkimas == 6)
            break;

        srand(time(nullptr));
        if (meniuPasirinkimas != 6) {
            std::string input;
            switch (meniuPasirinkimas) {
                
                    // Read student data

                case 1: {
                    std::cout << "1. STUDENTO DUOMENU IVEDIMAS\n";
                    ManualStudentas manualInput;
                    Studentas st;
                    manualInput.read(std::cin, manager, st);
                    manager.addStudent(st);
                    std::cout << "\nStudentas pridetas.\n";
                    break;
                }

                    // Generate student grades

                case 2: {
                    std::cout << "2. VARDO, PAVARDES IVEDIMAS. PAZYMIU GENERAVIMAS. \n";
                    SemiAutoStudentas semiAutoInput;
                    Studentas st;
                    semiAutoInput.read(std::cin, manager, st);
                    manager.addStudent(st);
                    std::cout << "Studentas su atsitiktiniais pazymiais pridetas.\n";
                    break;
                }

                    // Generate student data

                case 3: {
                    std::cout << "3. STUDENTU DUOMENU GENERAVIMAS\n";
                    AutoStudentas autoInput;
                    Studentas st;
                    autoInput.read(std::cin, manager, st);
                    std::cout << "Studentu duomenys sugeneruoti atsitiktinai. \n \n";
                    break;
                }

                    // Read data from file

                case 4: {
                    std::ifstream in;
                    std::cout << "4. DUOMENU NUSKAITYMAS. \n";
                    FileStudentas fileInput;
                    Studentas st;
                    fileInput.read(in, manager, st);
                    std::cout << "\nAr norite RUSIUOTI studentus i ISLAIKIUSIUS ir NEISLAIKIUSIUS? (y / n)" << std::endl;
                    std::cin >> input;
                    charInputProtection(input);
                    if (input == "y") {
                        manager.groupAndPrint();
                    } else {
                        manager.noGroupPrint();
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
                        rangeStudentGenerator();
                    } else if (pasirinkimas == 2) {
                        fiveFileGenerator();
                    }
                    break;
                }
            }
        }
    }

    // If there are no students, the program ends

    if (manager.getStudentListSize() == 0) {
        std::cout << "Programa baige darba." << std::endl;
        return 0;
    }

    //  If there are students, the program asks if the user wants to group them

    if (manager.getStudentListSize() != 0)
        manager.printToFile();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Programa baige darba per "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " sekundziu.\n";
    return 0;
}
