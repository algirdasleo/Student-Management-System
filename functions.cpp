#include "functions.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <chrono>

// Defining constructors and destructors.

Studentas::Studentas() : egzPazymys(0), galBalasVid(0), galBalasMed(0) {}

StudentasManager::StudentasManager() : maxNameLength(0), maxSurnameLength(0) {}

Studentas::~Studentas() {}

StudentasManager::~StudentasManager() {}

// Copy and Move constructors and assignment operators.

Studentas::Studentas(const Studentas &stud) : vardas(stud.vardas), pavarde(stud.pavarde), ndPazymiai(stud.ndPazymiai), egzPazymys(stud.egzPazymys), galBalasVid(stud.galBalasVid), galBalasMed(stud.galBalasMed) {}

std::istream &operator>>(std::istream &in, Studentas &stud) {
    std::string input;
    while (true) {
        std::cout << "Iveskite studento varda:" << std::endl;
        in >> input;
        try {
            if (!isString(input)) {
                throw std::invalid_argument("Ivestas ne vardas. Iveskite varda:");
            }
            stud.setName(input);
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        std::cout << "Iveskite studento pavarde:" << std::endl;
        in >> input;
        try {
            if (!isString(input)) {
                throw std::invalid_argument("Ivesta ne pavarde. Iveskite pavarde:");
            }
            stud.setSurname(input);
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return in;
}

Studentas &Studentas::operator=(const Studentas &stud) {
    if (this != &stud) {
        vardas = stud.vardas;
        pavarde = stud.pavarde;
        ndPazymiai = stud.ndPazymiai;
        egzPazymys = stud.egzPazymys;
        galBalasVid = stud.galBalasVid;
        galBalasMed = stud.galBalasMed;
    }
    return *this;
}

Studentas::Studentas(Studentas &&stud) noexcept : vardas(std::move(stud.vardas)), pavarde(std::move(stud.pavarde)), ndPazymiai(std::move(stud.ndPazymiai)), egzPazymys(stud.egzPazymys), galBalasVid(stud.galBalasVid), galBalasMed(stud.galBalasMed) {}

Studentas &Studentas::operator=(Studentas &&stud) noexcept {
    if (this != &stud) {
        vardas = std::move(stud.vardas);
        pavarde = std::move(stud.pavarde);
        ndPazymiai = std::move(stud.ndPazymiai);
        egzPazymys = stud.egzPazymys;
        galBalasVid = stud.galBalasVid;
        galBalasMed = stud.galBalasMed;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const StudentasManager::OutputHelper &helper) {
    out << std::setw(helper.maxSurnameLength + 7) << helper.student.pavarde
        << std::setw(helper.maxNameLength + 7) << helper.student.vardas
        << std::setw(17) << std::fixed << std::setprecision(2) << helper.student.galBalasVid
        << std::setw(15) << std::fixed << std::setprecision(2) << helper.student.galBalasMed << std::endl;
    return out;
}

// StudentasManager class functions

size_t StudentasManager::getStudentListSize() {
    return studentList.size();
}

void StudentasManager::setMaxNameLength(int length) {
    this->maxNameLength = length;
}

void StudentasManager::setMaxSurnameLength(int length) {
    this->maxSurnameLength = length;
}

int StudentasManager::getMaxNameLength() {
    return this->maxNameLength;
}

int StudentasManager::getMaxSurnameLength() {
    return this->maxSurnameLength;
}

void StudentasManager::addStudent(Studentas student) {
    if (student.getName().length() > maxNameLength)
        maxNameLength = student.getName().length();
    

    if (student.getSurname().length() > maxSurnameLength)
        maxSurnameLength = student.getSurname().length();

    studentList.push_back(student);
}

void StudentasManager::printToFile() {
    if (studentList.empty()) {
        std::cout << "Studentu duomenu nerasta.\n";
        return;
    }

    std::string input;
    std::cout << "|- Ar norite surusiuoti studentus? (y / n) " << std::endl;
    std::cin >> input;
    charInputProtection(input);
    if (input == "y") {
        char pasirinkimas, rusiavimas;
        howToSort(pasirinkimas, rusiavimas);
        sortStudents(pasirinkimas, rusiavimas);
    }
    std::ofstream out("rezultatas.txt");
    out << std::left
        << std::setw(maxNameLength + 7) << "Pavarde"
        << std::setw(maxSurnameLength + 7) << "Vardas"
        << std::setw(17) << "Galutinis(Vid.)"
        << std::setw(15) << "Galutinis(Med.)" << std::endl;

    out << std::setfill('-') << std::setw(maxNameLength + maxSurnameLength + 45) << "-" << std::endl;
    out << std::setfill(' ');

    for (const auto &student : studentList) {
        out << OutputHelper(student, maxNameLength, maxSurnameLength);  // Naudojamas operatorius << ir OutputHelper struktura
    }
    out.close();
    std::cout << "\nRezultatai isvesti i faila 'rezultatas.txt'.\n";
    studentList.clear();
}

void StudentasManager::printToFile(std::string fileName) {
    if (studentList.empty()) {
        std::cout << "\nStudentu duomenu nerasta.\n";
        return;
    }

    std::ofstream out(fileName);

    out << "ISLAIKUSIU STUDENTU SARASAS.\n\n";

    out << std::left
        << std::setw(maxSurnameLength + 7) << "Pavarde"
        << std::setw(maxNameLength + 7) << "Vardas"
        << std::setw(17) << "Galutinis(Vid.)"
        << std::setw(15) << "Galutinis(Med.)" << std::endl;

    out << std::setfill('-') << std::setw(maxSurnameLength + maxNameLength + 45) << "-" << std::endl;
    out << std::setfill(' ');

    for (const auto &student : studentList) {
        out << OutputHelper(student, maxNameLength, maxSurnameLength);  // Naudojamas operatorius << ir OutputHelper struktura
    }
    out.close();
    std::cout << "\nRezultatai isvesti i faila '" << fileName << "'.\n";
    studentList.clear();
}

void StudentasManager::printToFile(std::string fileName, std::list<Studentas> &neislaike) {
    if (neislaike.empty()) {
        std::cout << "\nNeislaikiusiu nerasta.\n";
        return;
    }

    std::ofstream out(fileName);
    out << "NEISLAIKUSIU STUDENTU SARASAS.\n\n";

    out << std::left
        << std::setw(maxSurnameLength + 7) << "Pavarde"
        << std::setw(maxNameLength + 7) << "Vardas"
        << std::setw(17) << "Galutinis(Vid.)"
        << std::setw(15) << "Galutinis(Med.)" << std::endl;

    out << std::setfill('-') << std::setw(maxSurnameLength + maxNameLength + 45) << "-" << std::endl;
    out << std::setfill(' ');

    for (const auto &student : neislaike) {
        out << OutputHelper(student, maxNameLength, maxSurnameLength);  // Naudojamas operatorius << ir OutputHelper struktura
    }
    out.close();
    std::cout << "Rezultatai isvesti i faila '" << fileName << "'.\n";
    neislaike.clear();
}

void StudentasManager::sortStudents(char pasirinkimas, char input) {
    auto start = std::chrono::high_resolution_clock::now();
    if (pasirinkimas == 'v') {
        if (input == 'd')
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
        else
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.vardas > b.vardas; });
    } else if (pasirinkimas == 'p') {
        if (input == 'd')
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
        else
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.pavarde > b.pavarde; });
    } else if (pasirinkimas == 'g') {
        if (input == 'd')
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid < b.galBalasVid; });
        else
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid > b.galBalasVid; });
    } else if (pasirinkimas == 'm') {
        if (input == 'd')
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed < b.galBalasMed; });
        else
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed > b.galBalasMed; });
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nSurusiuota per " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";
}

void StudentasManager::sortStudents(char pasirinkimas, char input, std::list<Studentas> &neislaike) {
    auto start = std::chrono::high_resolution_clock::now();
    if (pasirinkimas == 'v') {
        if (input == 'd') {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.vardas < b.vardas; });
        } else {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.vardas > b.vardas; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.vardas > b.vardas; });
        }
    } else if (pasirinkimas == 'p') {
        if (input == 'd') {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.pavarde < b.pavarde; });
        } else {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.pavarde > b.pavarde; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.pavarde > b.pavarde; });
        }
    } else if (pasirinkimas == 'g') {
        if (input == 'd') {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid < b.galBalasVid; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid < b.galBalasVid; });
        } else {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid > b.galBalasVid; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.galBalasVid > b.galBalasVid; });
        }
    } else if (pasirinkimas == 'm') {
        if (input == 'd') {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed < b.galBalasMed; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed < b.galBalasMed; });
        } else {
            studentList.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed > b.galBalasMed; });
            neislaike.sort([](const Studentas &a, const Studentas &b) { return a.galBalasMed > b.galBalasMed; });
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nSurusiuota per " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";
}

void StudentasManager::readFromFile(std::string fileName) {
    std::cout << "Nuskaitomi duomenys is failo '" << fileName << "'.\n";
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream in(fileName);
    std::string line;
    getline(in, line);
    std::string vardas, pavarde, pazymys;
    int pazymysInt;
    while (getline(in, line)) {
        std::istringstream iss(line);
        iss >> vardas >> pavarde;
        Studentas student;
        student.setName(vardas);
        student.setSurname(pavarde);
        while (iss >> pazymys) {
            pazymysInt = stoi(pazymys);
            if (pazymysInt < 1 || pazymysInt > 10) {
                std::cout << "Neteisingas pazymys: " << pazymysInt << ". Pazymys turi buti nuo 1 iki 10. Praleidziamas pazymys.\n";
                continue;
            }
            student.addGrade(pazymysInt);
        }
        if (!student.ndPazymiai.empty()) {
            student.setEgz(student.ndPazymiai.back());
            student.ndPazymiai.pop_back();
            student.calculate();
        }
        addStudent(student);
    }
    setMaxNameLength(maxNameLength);
    setMaxSurnameLength(maxSurnameLength);
    in.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Duomenys nuskaityti per " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";
}

void StudentasManager::sortIntoGroups(std::list<Studentas> &neislaike) {
    auto start = std::chrono::high_resolution_clock::now();
    auto it = studentList.begin();
    while (it != studentList.end()) {
        if (it->galBalasVid < 5 || it->galBalasMed < 5) {
            neislaike.splice(neislaike.end(), studentList, it++);
        } else {
            ++it;
        }
    }
    std::cout << "Neislaikiusiu studentu kiekis: " << neislaike.size() << "\n";
    std::cout << "Islaikiusiu studentu kiekis: " << studentList.size() << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Studentai suskirstyti per " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";
}

// Studentas class functions

void Studentas::setName(std::string name) {
    this->vardas = name;
}

std::string Studentas::getName() {
    return this->vardas;
}

std::string Studentas::getSurname() {
    return this->pavarde;
}

void Studentas::setSurname(std::string surname) {
    this->pavarde = surname;
}

void Studentas::addGrade(int grade) {
    this->ndPazymiai.push_back(grade);
}

void Studentas::setEgz(int grade) {
    this->egzPazymys = grade;
}

void Studentas::calculate() {
    int ndrange = distance(this->ndPazymiai.begin(), this->ndPazymiai.end());
    this->ndPazymiai.sort();
    auto mid = next(this->ndPazymiai.begin(), ndrange / 2);
    if (ndrange % 2 == 0) {
        auto midPrev = prev(mid, 1);
        this->galBalasMed = (*mid + *midPrev) / 2.0;
    } else {
        this->galBalasMed = *mid;
    }
    double sum = accumulate(this->ndPazymiai.begin(), this->ndPazymiai.end(), 0.0);
    this->galBalasVid = 0.4 * (sum / ndrange) + 0.6 * this->egzPazymys;
}

void Studentas::readName() {
    std::string input;

    while (true) {
        std::cout << "Iveskite studento varda:" << std::endl;
        std::cin >> input;
        try {
            if (!isString(input)) {
                throw std::invalid_argument("Ivestas ne vardas. Iveskite varda:");
            }
            this->vardas = input;
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        std::cout << "Iveskite studento pavarde:" << std::endl;
        std::cin >> input;
        try {
            if (!isString(input)) {
                throw std::invalid_argument("Ivesta ne pavarde. Iveskite pavarde:");
            }
            this->pavarde = input;
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

// Testing Rule of Five for Studentas class

void testStudentasClass() {
    Studentas stud1;
    stud1.setName("Jonas");
    stud1.setSurname("Jonaitis");
    stud1.addGrade(8);
    stud1.setEgz(9);
    stud1.calculate();

    // Default Constructor TEST
    if (stud1.getName() != "Jonas") {
        throw std::runtime_error("Default constructor test FAILED: setName() or getName()");
    }
    std::cout << "Default constructor test: PASSED.\n";

    // Copy Constructor TEST
    Studentas stud2 = stud1;
    if (stud2.getName() != "Jonas") {
        throw std::runtime_error("Copy constructor test failed.");
    }
    std::cout << "Copy constructor test: PASSED.\n";

    // Move Constructor TEST
    Studentas stud3 = std::move(stud1);
    if (stud3.getName() != "Jonas" || !stud1.getName().empty()) {
        throw std::runtime_error("Move constructor test failed.");
    }
    std::cout << "Move constructor test: PASSED.\n";

    // Copy Assignment Operator TEST
    Studentas stud4;
    stud4 = stud2;
    if (stud4.getName() != "Jonas") {
        throw std::runtime_error("Copy assignment operator test failed.");
    }
    std::cout << "Copy assignment operator test: PASSED.\n";

    // Move Assignment Operator TEST
    Studentas stud5;
    stud5 = std::move(stud2);
    if (stud5.getName() != "Jonas" || !stud2.getName().empty()) {
        throw std::runtime_error("Move assignment operator test failed.");
    }
    std::cout << "Move assignment operator test: PASSED.\n";
}

// Other functions

bool isNumber(std::string &str) {
    for (char c : str)
        if (!isdigit(c))
            return false;
    return true;
}

bool isString(std::string &str) {
    for (char c : str)
        if (!isalpha(c))
            return false;
    return true;
}

void numberInputProtection(std::string &input) {
    try {
        if (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10) {
            throw std::invalid_argument("Iveskite skaiciu nuo 1 iki 10:");
        }
    } catch (const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        std::cin >> input;
        numberInputProtection(input);
    }
}

void charInputProtection(std::string &input) {
    try {
        if (input.length() > 1 || (input != "n" && input != "y")) {
            throw std::invalid_argument("\nNeteisingas pasirinkimas. Iveskite 'y' arba 'n':");
        }
    } catch (const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        std::cin >> input;
        charInputProtection(input);
    }
}

void generateFile(int range, int homeworkCount) {
    int tarpuIlgis = std::to_string(range).length();
    int maxVardoIlgis = 6 + tarpuIlgis, maxPavardesIlgis = 7 + tarpuIlgis;
    std::string input;
    std::cout << "Generuojamas failas su " << range << " studentu duomenimis...\n";
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream out("kursiokai" + std::to_string(range) + ".txt");
    out << std::left;
    out << std::setw(maxVardoIlgis + 3) << "Vardas"
        << std::setw(maxPavardesIlgis + 3) << "Pavarde";
    for (int i = 1; i <= homeworkCount; i++) out << std::setw(5) << "ND" + std::to_string(i);
    out << std::setw(4) << " Egzaminas"
        << "\n";

    for (int i = 1; i <= range; i++) {
        out << std::setw(maxVardoIlgis + 3) << "Vardas" + std::to_string(i)
            << std::setw(maxPavardesIlgis + 3) << "Pavarde" + std::to_string(i);
        for (int j = 1; j < homeworkCount; j++) out << std::setw(5) << std::to_string(rand() % 10 + 1);
        if (homeworkCount > 0) out << std::setw(6) << std::to_string(rand() % 10 + 1);

        out << std::setw(2) << std::to_string(rand() % 10 + 1) << "\n";
    }
    out.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Failas 'kursiokai" << range << ".txt' sukurtas per " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";
}

void howToSort(char &choice1, char &choice2) {
    std::string input;
    std::cout << "|- Pagal ka norite surusiuoti studentus? (v - vardas, p - pavarde, g - galutinis (vidurkis), m - galutinis (mediana)) " << std::endl;
    std::cin >> input;
    while (input.length() > 1 || (input != "v" && input != "p" && input != "g" && input != "m")) {
        std::cout << "Neteisingas pasirinkimas. Iveskite 'v', 'p', 'g' arba 'm':" << std::endl;
        std::cin >> input;
    }
    choice1 = input[0];
    std::cout << "\n|- Kaip norite surusiuoti? (d - didejimo tvarka, m - mazejimo tvarka)  " << std::endl;
    std::cin >> input;
    while (input.length() > 1 || (input != "d" && input != "m")) {
        std::cout << "Neteisingas pasirinkimas. Iveskite 'd' arba 'm':" << std::endl;
        std::cin >> input;
    }
    choice2 = input[0];
}
