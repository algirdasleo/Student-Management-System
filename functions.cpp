#include "functions.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <sstream>
#include <string>

// Defining constructors and destructors.

Studentas::Studentas() : egzPazymys(0), galBalasVid(0), galBalasMed(0) {}

StudentasManager::StudentasManager() : maxNameLength(0), maxSurnameLength(0) {}

Studentas::~Studentas() {}

StudentasManager::~StudentasManager() {}

// Copy and Move constructors and assignment operators.

Studentas::Studentas(const Studentas &stud) : vardas(stud.vardas), pavarde(stud.pavarde), ndPazymiai(stud.ndPazymiai), egzPazymys(stud.egzPazymys), galBalasVid(stud.galBalasVid), galBalasMed(stud.galBalasMed) {}

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
// prilygint stud egzpazymys ir galbalus = 0
Studentas::Studentas(Studentas &&stud) noexcept : vardas(std::move(stud.vardas)), pavarde(std::move(stud.pavarde)), ndPazymiai(std::move(stud.ndPazymiai)), egzPazymys(stud.egzPazymys), galBalasVid(stud.galBalasVid), galBalasMed(stud.galBalasMed) {
    stud.egzPazymys = 0;
    stud.galBalasVid = 0;
    stud.galBalasMed = 0;
}

Studentas &Studentas::operator=(Studentas &&stud) noexcept {
    if (this != &stud) {
        vardas = std::move(stud.vardas);
        pavarde = std::move(stud.pavarde);
        ndPazymiai = std::move(stud.ndPazymiai);
        egzPazymys = stud.egzPazymys;
        stud.egzPazymys = 0;
        galBalasVid = stud.galBalasVid;
        stud.galBalasVid = 0;
        galBalasMed = stud.galBalasMed;
        stud.galBalasMed = 0;
    }
    return *this;
}

// Operator overloading for output stream

std::ostream &operator<<(std::ostream &out, const StudentasManager::OutputHelper &helper) {
    out << std::setw(helper.maxSurnameLength + 7) << helper.student.pavarde
        << std::setw(helper.maxNameLength + 7) << helper.student.vardas
        << std::setw(17) << std::fixed << std::setprecision(2) << helper.student.galBalasVid
        << std::setw(15) << std::fixed << std::setprecision(2) << helper.student.galBalasMed << std::endl;
    return out;
}

// Derived classes for different ways of reading student data

std::istream &ReadStudentas::read(std::istream &is, StudentasManager &manager, Studentas &student) {
    return is;
}

std::istream &ManualStudentas::read(std::istream &is, StudentasManager &manager, Studentas &student) {
    readName(is, student);
    getUserGradeInput(is, student);
    return is;
}

void ManualStudentas::readName(std::istream &is, Studentas &student) {
    std::string input;
    while (true) {
        std::cout << "Iveskite studento varda:" << std::endl;
        std::cin >> input;
        try {
            if (!isString(input)) {
                throw std::invalid_argument("Ivestas ne vardas. Iveskite varda:");
            }
            student.setName(input);
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
            student.setSurname(input);
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }
}
void ManualStudentas::getUserGradeInput(std::istream &is, Studentas &student) {
    int i = 0;
    std::string input;
    while (true) {
        std::cout << "Iveskite " << i + 1 << " namu darbo rezultata (1 - 10):" << std::endl;
        std::cin >> input;
        numberInputProtection(input);
        student.addGrade(stoi(input));
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
    student.setEgz(stoi(input));
    student.calculate();
}

std::istream &SemiAutoStudentas::read(std::istream &is, StudentasManager &manager, Studentas &student) {
    readName(is, student);
    generateGrades(student);
    return is;
}

void SemiAutoStudentas::readName(std::istream &is, Studentas &student) {
    std::string input;
    while (true) {
        std::cout << "Iveskite studento varda:" << std::endl;
        std::cin >> input;
        try {
            if (!isString(input)) {
                throw std::invalid_argument("Ivestas ne vardas. Iveskite varda:");
            }
            student.setName(input);
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
            student.setSurname(input);
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }
}
void SemiAutoStudentas::generateGrades(Studentas &student) {
    for (int i = 0; i < 10; i++) {
        int random_grade = rand() % 10 + 1;
        student.addGrade(random_grade);
    }
    student.setEgz(rand() % 10 + 1);
    student.calculate();
}

std::istream &AutoStudentas::read(std::istream &is, StudentasManager &manager, Studentas &student) {
    std::string input;
    std::cout << "Kiek studentu sugeneruoti?" << std::endl;
    std::cin >> input;
    while (!isNumber(input) || stoi(input) < 1) {
        std::cout << "Neteisingas pasirinkimas. Iveskite skaiciu didesni uz 0:" << std::endl;
        std::cin >> input;
    }
    manager.generateRandomStudents(stoi(input));
    return is;
}

std::istream &FileStudentas::read(std::istream &is, StudentasManager &manager, Studentas &student) {
    std::string fileName = enterFileName(is);
    manager.readFromFile(fileName);
    return is;
}

std::string FileStudentas::enterFileName(std::istream &is) {
    std::ifstream in;
    std::string fileName;
    while (true) {
        std::cout << "Iveskite tikslu file pavadinima (pvz. 'kursiokai.txt'):" << std::endl;
        std::cin >> fileName;
        in.open(fileName);
        if (!in) {
            std::cout << "Failas '" << fileName << "' nerastas. Bandykite dar karta." << std::endl;
            in.clear();
        } else {
            break;
        }
    }
    in.close();
    return fileName;
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

void StudentasManager::addStudent(Studentas &student) {
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
    std::cout << "|- Neislaikiusiu studentu kiekis: " << neislaike.size() << "\n";
    std::cout << "|- Islaikiusiu studentu kiekis: " << studentList.size() << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Studentai suskirstyti per " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";
}

void StudentasManager::generateRandomStudents(int count) {
    int number = getStudentListSize();
    if (number == 0) {
        number = 1;
    }
    while (count-- > 0) {
        Studentas student;
        student.setName("Vardas" + std::to_string(number));
        student.setSurname("Pavarde" + std::to_string(number));
        for (int i = 0; i < 10; i++)
            student.addGrade(rand() % 10 + 1);

        student.setEgz(rand() % 10 + 1);
        student.calculate();
        addStudent(student);
        number++;
    }
}
void StudentasManager::groupAndPrint() {
    std::list<Studentas> neislaike;
    this->sortIntoGroups(neislaike);
    char pasirinkimas, rusiavimas;
    howToSort(pasirinkimas, rusiavimas);
    this->sortStudents(pasirinkimas, rusiavimas, neislaike);
    auto start5 = std::chrono::high_resolution_clock::now();
    this->printToFile("islaike.txt");
    this->printToFile("neislaike.txt", neislaike);
    std::cout << "Rezultatai isvesti i failus 'islaike.txt' ir 'neislaike.txt' per "
              << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start5).count() / 1000.0 << " sekundziu.\n\n";
}

void StudentasManager::noGroupPrint() {
    char pasirinkimas, rusiavimas;
    howToSort(pasirinkimas, rusiavimas);
    this->sortStudents(pasirinkimas, rusiavimas);
    auto start6 = std::chrono::high_resolution_clock::now();
    this->printToFile();
    std::cout << "Rezultatai isvesti i faila 'Rezultatas.txt' per "
              << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start6).count() / 1000.0 << " sekundziu.\n\n";
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

// Testing Rule of Five for Studentas class
void Studentas::testStudentasClass() {
    Studentas stud1;
    stud1.setName("Jonas");
    stud1.setSurname("Jonaitis");
    stud1.addGrade(8);
    stud1.setEgz(9);
    stud1.calculate();

    std::cout << "Default constructor test: PASSED.\n";
    // Copy Constructor TEST
    std::cout << "Copy constructor test. Stud before copying: \n";
    std::cout << "Name: " << stud1.getName() << std::endl;
    std::cout << "Surname: " << stud1.getSurname() << std::endl;
    std::cout << "ND grades: ";
    for (int grade : stud1.ndPazymiai) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
    std::cout << "Egzamino pazymys: " << stud1.egzPazymys << std::endl;
    std::cout << "Galutinis balas (vidurkis): " << stud1.galBalasVid << std::endl;

    Studentas stud2(stud1);

    std::cout << "Copy constructor test. Stud after copying: \n";
    std::cout << "Name: " << stud2.getName() << std::endl;
    std::cout << "Surname: " << stud2.getSurname() << std::endl;
    std::cout << "ND grades: ";
    for (int grade : stud2.ndPazymiai) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
    std::cout << "Egzamino pazymys: " << stud2.egzPazymys << std::endl;
    std::cout << "Galutinis balas (vidurkis): " << stud2.galBalasVid << std::endl;
    std::cout << "Galutinis balas (mediana): " << stud2.galBalasMed << std::endl;

    // Move Constructor TEST

    std::cout << "Move constructor test. Stud before moving: \n";
    std::cout << "Name: " << stud1.getName() << std::endl;
    std::cout << "Surname: " << stud1.getSurname() << std::endl;
    std::cout << "ND grades: ";
    for (int grade : stud1.ndPazymiai)
        std::cout << grade << " ";
    std::cout << std::endl;
    std::cout << "Egzamino pazymys: " << stud1.egzPazymys << std::endl;
    std::cout << "Galutinis balas (vidurkis): " << stud1.galBalasVid << std::endl;
    std::cout << "Galutinis balas (mediana): " << stud1.galBalasMed << std::endl;

    Studentas stud3(std::move(stud1));

    std::cout << "Move constructor test. Stud after moving: \n";
    std::cout << "Name: " << stud3.getName() << std::endl;
    std::cout << "Surname: " << stud3.getSurname() << std::endl;
    std::cout << "ND grades: ";
    for (int grade : stud3.ndPazymiai) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
    std::cout << "Egzamino pazymys: " << stud3.egzPazymys << std::endl;
    std::cout << "Galutinis balas (vidurkis): " << stud3.galBalasVid << std::endl;
    std::cout << "Galutinis balas (mediana): " << stud3.galBalasMed << std::endl;

    std::cout << "Previous student after moving: \n";
    std::cout << "Name: " << stud1.getName() << std::endl;
    std::cout << "Surname: " << stud1.getSurname() << std::endl;
    std::cout << "ND grades: ";
    for (int grade : stud1.ndPazymiai) 
        std::cout << grade << " ";
    std::cout << std::endl;
    std::cout << "Egzamino pazymys: " << stud1.egzPazymys << std::endl;
    std::cout << "Galutinis balas (vidurkis): " << stud1.galBalasVid << std::endl;
    std::cout << "Galutinis balas (mediana): " << stud1.galBalasMed << std::endl;

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
            throw std::invalid_argument("\n|- Iveskite skaiciu nuo 1 iki 10:");
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
            throw std::invalid_argument("\n|- Neteisingas pasirinkimas. Iveskite 'y' arba 'n':");
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
        std::cout << "\n|- Neteisingas pasirinkimas. Iveskite 'v', 'p', 'g' arba 'm':" << std::endl;
        std::cin >> input;
    }
    choice1 = input[0];
    std::cout << "\n|- Kaip norite surusiuoti? (d - didejimo tvarka, m - mazejimo tvarka)  " << std::endl;
    std::cin >> input;
    while (input.length() > 1 || (input != "d" && input != "m")) {
        std::cout << "\n|- Neteisingas pasirinkimas. Iveskite 'd' arba 'm':" << std::endl;
        std::cin >> input;
    }
    choice2 = input[0];
}
int getMenuChoice() {
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
        std::cout << "\n|- Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 6:" << std::endl;
        std::cin >> input;
    }
    return stoi(input);
}

void rangeStudentGenerator() {
    std::string input;
    std::cout << "\n|- Iveskite studentu kieki (nuo 1 iki 10000000):" << std::endl;
    std::cin >> input;
    while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 10000000) {
        std::cout << "\n|- Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 10'000'000:" << std::endl;
        std::cin >> input;
    }
    int kiekis = stoi(input);

    std::cout << "\n|- Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << std::endl;
    std::cin >> input;
    while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
        std::cout << "|- Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << std::endl;
        std::cin >> input;
    }
    int pazymiuKiekis = stoi(input);
    generateFile(kiekis, pazymiuKiekis);
}

void fiveFileGenerator() {
    std::string input;
    std::cout << "\n|- Kiek namu darbu pazymiu kiekvienam studentui sugeneruoti? (nuo 1 iki 20):" << std::endl;
    std::cin >> input;
    while (!isNumber(input) || stoi(input) < 1 || stoi(input) > 20) {
        std::cout << "\n|- Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 20:" << std::endl;
        std::cin >> input;
    }
    int pazymiuKiekis = stoi(input);
    auto start3 = std::chrono::high_resolution_clock::now();
    generateFile(1000, pazymiuKiekis);
    generateFile(10000, pazymiuKiekis);
    generateFile(100000, pazymiuKiekis);
    generateFile(1000000, pazymiuKiekis);
    generateFile(10000000, pazymiuKiekis);
    std::cout << "Failai sugeneruoti per "
              << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start3).count() / 1000.0 << " sekundziu.\n\n";
}