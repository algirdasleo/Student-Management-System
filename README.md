# Studentų Duomenų Valdymo Sistema

Ši programa yra studentų duomenų valdymo sistema, kuri leidžia vartotojui įvesti studentų duomenis įvairiais būdais ir pateikti jų galutinius įvertinimus. **Pagrindinės programos funkcijos:**

1. **Duomenų Įvedimas:** Vartotojas gali įvesti studentų duomenis rankiniu būdu, generuoti juos atsitiktinai, arba nuskaityti iš failo.
2. **Įvertinimų Skaičiavimas:** Programa apskaičiuoja studentų galutinius įvertinimus pagal jų namų darbų ir egzaminų rezultatus naudojant vidurkį ar medianą.
3. **Duomenų Išvedimas:** Galiausiai, vartotojas gali pasirinkti duomenų rikiavimo būdą ir programa pateikia surikiuotą studentų sąrašą su jų vardais, pavardėmis ir galutiniais įvertinimais.

---

Programos meniu siūlo penkias pagrindines pasirinkimo galimybes, kiekviena iš jų leidžia vartotojui įvesti arba gauti studentų duomenis skirtingais būdais:

1. **Studento duomenų įvedimas rankiniu būdu:** Ši funkcija leidžia vartotojui įvesti visus studento duomenis, įskaitant vardą, pavardę, namų darbų rezultatus ir egzamino įvertinimą, rankiniu būdu.
2. **Įvedimas rankiniu būdu su atsitiktiniais pažymiais:** Šioje funkcijoje vartotojas įveda studento vardą ir pavardę, o programa automatiškai generuoja namų darbų ir egzamino įvertinimus.
3. **Visiškai atsitiktinis studentų duomenų generavimas:** Ši funkcija leidžia programai automatiškai sugeneruoti visus studento duomenis, įskaitant vardą, pavardę ir visus įvertinimus.
4. **Duomenų nuskaitymas iš failo:** Ši funkcija leidžia vartotojui nuskaityti studentų duomenis iš iš anksto paruošto tekstinio failo, pavyzdžiui, „kursiokai.txt“.
5. **Baigti darbą ir rodyti rezultatus:** Pasirinkus šią funkciją, programa leidžia vartotojui pasirinkti, kaip nori rikiuoti galutinius duomenis (pagal vardą, pavardę, galutinį įvertinimą ir pan.) ir pateikia galutinę ataskaitą su visais studentų įrašais, jų vardais, pavardėmis ir galutiniais įvertinimais.

---

**Kaip diegti šią programą?**

- Prieš paleidžiant programą, ją reikia sukompiliuoti su komanda terminale: `make build`.
- Norint paleisti programą, reikia parašyti komandą: `make run`.
- Norint išvalyti sukurtą paleisties failą, reikią parašyti komandą: `make clean`.

---

 ** NewVector klasės 5 atsitiktinių funkcijų apžvalga: (V3.0) ** 

- **  **

### `push_back(const T& value)`

- **Description:** Adds an element to the end of the vector.
- **Usage Example:**
  ```cpp
  NewVector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  ```

---

**Testavimas (V2.0):**

Programoje yra įdiegti unit testai naudojant Catch2 testų framework su kuria yra tikrinamas programos funkcionalumas.

Norėdami paleisti testus, jūs turite įvykdyti **šiuos žingsnius**:

- Kompiliuokite testavimo failus naudojant `make test`, kuris sukuria testų vykdymo failą ir jį paleidžia.

**Testų apžvalga:**

- **Konstruktorių testai:** Patikrina, ar objektai teisingai sukuriami naudojant konstruktorius.
- **Copy ir Move operacijų testai:** Užtikrina, kad objektų kopijavimas ir perkėlimas veiktų teisingai ir duomenys nebūtų prarasti.
- **Funkcionalumo testai:** Tikrina pagrindines programos funkcijas, tokias kaip studentų duomenų įvedimas, skaičiavimas ir rūšiavimas.

---

**Pasirinktiniai duomenų įvedimo būdai (V1.2):**

- **Rankinis duomenų įvedimas (ManualStudentas::read):**
  - Šis metodas leidžia vartotojui rankiniu būdu įvesti studento vardą, pavardę ir pažymius.
  - Vartotojas taip pat gali nuspręsti, kiek namų darbų pažymių nori įvesti.

- **Pusiau-automatinis duomenų įvedimas (SemiAutoStudentas::read):**
  - Vartotojas įveda studento vardą ir pavardę rankiniu būdu.
  - Namų darbų pažymiai ir egzamino rezultatas sugeneruojami automatiškai naudojant atsitiktinius skaičius.

- **Automatinis duomenų įvedimas (AutoStudentas::read):**
  - Visi studento duomenys, įskaitant vardą, pavardę ir visus pažymius, generuojami automatiškai.
  - Vartotojas nurodo, kiek studentų duomenų nori sugeneruoti.

- **Duomenų įvedimas iš failo (FileStudentas::read):**
  - Šis metodas skaito studentų duomenis iš nurodyto tekstinio failo.
  - Vartotojas turi įvesti failo pavadinimą, iš kurio bus skaitoma.

**Išvesties Metodai**

- **Išvestis į ekraną:**
  - **StudentasManager::print** metodas išveda visų studentų duomenis tiesiogiai į konsolės langą.
    Išvedami duomenys: vardas, pavardė, galutinis balas (vidurkis ir mediana).

- **Išvestis į failą (StudentasManager::printToFile):**
  - Šis metodas išveda visų studentų duomenis į nurodytą tekstinių failą.
    Failo pavadinimas gali būti pasirinktas vartotojo. Jeigu jis nenurodomas, naudojamas numatytasis pavadinimas "rezultatai.txt".
    Išvedami duomenys: vardas, pavardė, galutinis balas (vidurkis ir mediana), taip pat galima atskirti studentus, kurie išlaikė arba ne.

---

**Spartos palyginimas (V1.1):**

**Pasirinkau optimaliausią duomenų struktūrą darbui su studentais: List.**

| Užduočių atlikimas (s) | 1000000 | 10000000 |
|------------------------|---------|----------|
| Klasė (List)           |         |          |
| Failų nuskaitymas      |  4.02   |  37.653  | <= 35% lėčiau
| Skirstymas į grupes    |  0.062  |  0.565   | <= 15% greičiau
| Rūšiavimas didėjimo t. |  0.568  |  6.94    | <= 6% greičiau
|------------------------|---------|----------|
| Struktūra (List)       |         |          |
| Failų nuskaitymas      |  2.916  |  27.902  |
| Skirstymas į grupes    |  0.074  |  0.666   |
| Rūšiavimas didėjimo t. |  0.715  |  7.35    |
|------------------------|---------|----------|

**Kompiliatoriaus optimizavimo lygio analizė:**

| Užduočių atlikimas (s) | 1000000 | 10000000 |
|------------------------|---------|----------|
| 01                     |         |          |
| Failų nuskaitymas      |  3.767  |  40.186  |
| Skirstymas į grupes    |  0.069  |  0.7     |
| Rūšiavimas didėjimo t. |  0.58   |  7.406   |
|------------------------|---------|----------|
| 02                     |         |          |
| Failų nuskaitymas      |  4.102  |  38.536  |
| Skirstymas į grupes    |  0.062  |  0.65    |
| Rūšiavimas didėjimo t. |  0.557  |  7.466   |
|------------------------|---------|----------|
| 03                     |         |          |
| Failų nuskaitymas      |  4.707  |  37.686  | <= 6.2% greičiau už 01
| Skirstymas į grupes    |  0.067  |  0.608   | <= 13% greičiau už 01
| Rūšiavimas didėjimo t. |  0.564  |  7.05    | <= 5% greičiau už 01
|------------------------|---------|----------|

---

**Spartos palyginimas (V1.0):**

| Užduočių atlikimas (s)  | 1000   | 10000  | 100000 | 1000000 | 10000000 |
|-------------------------|--------|--------|--------|---------|----------|
| **Deque**               |        |        |        |         |          |
| Failų nuskaitymas       | 0.02   | 0.036  | 0.298  | 2.95    | 10.732   |
| Skirstymas į grupes     | 0      | 0.015  | 0.167  | 1.867   | 56.521   |
| Rūšiavimas didėjimo t.  | 0.011  | 0.053  | 1.1    | 12.6    | 96.79    |
|-------------------------|--------|--------|--------|---------|----------|
| **Vector**              |        |        |        |         |          |
| Failų nuskaitymas       | 0.01   | 0.03   | 0.26   | 2.55    | 25.99    |
| Skirstymas į grupes     | 0      | 0.01   | 0.035  | 0.329   | 3.766    |
| Rūšiavimas didėjimo t.  | 0      | 0.083  | 0.185  | 2.84    | 32.94    |
|-------------------------|--------|--------|--------|---------|----------|
| **List**                |        |        |        |         |          |
| Failų nuskaitymas       | 0      | 0.024  | 0.278  | 2.763   | 28.461   |
| Skirstymas į grupes     | 0      | 0.01   | 0.101  | 0.915   | 18.026   |
| Rūšiavimas didėjimo t.  | 0      | 0.002  | 0.051  | 0.569   | 8.465    |
|-------------------------|--------|--------|--------|---------|----------|

**Strategijų palyginimas:**

- **1 strategija** - Bendro studentai konteinerio rūšiavimas į du naujus to paties tipo konteinerius.
- **2 strategija** - Bendro studentų konteinerio skaidymas (rūšiavimas) panaudojant tik vieną naują konteinerį: "neišlaikę".
- **3 strategija** - Bendro studentų konteinerio skaidymas, naudojant 1 ar 2 strategiją ir įtraukiant "efektyvius" darbo su konteineriais metodus.

| Studentų rušiavimas (s) | 1000   | 10000  | 100000 | 1000000 | 10000000 |
|-------------------------|--------|--------|--------|---------|----------|
| **1 strategija**        |        |        |        |         |          |
| Deque                   | 0      | 0.015  | 0.167  | 1.867   | 56.521   |
| Vector                  | 0      | 0.01   | 0.035  | 0.329   | 3.766    |
| List                    | 0      | 0.01   | 0.101  | 0.915   | 18.026   |
|-------------------------|--------|--------|--------|---------|----------|
| **2 strategija**        |        |        |        |         |          |
| Deque                   | 0.012  | 1.285  | 139.783| ...     | ...      |
| Vector                  | 0.019  | 1.64   | 160.687| ...     | ...      |
| List                    | 0      | 0      | 0.052  | 0.695   | 9.214    |
|-------------------------|--------|--------|--------|---------|----------|
| **3 strategija**        |        |        |        |         |          |
| Deque                   | 0      | 0      | 0.098  | 0.817   | 31.702   |
| Vector                  | 0      | 0.01   | 0.003  | 0.125   | 1.253    |
| List                    | 0      | 0      | 0.011  | 0.081   | 1.072    |
|-------------------------|--------|--------|--------|---------|----------|

---

**Versijų aprašymas:**

- **V0.1** - Sukurta pradinė programos versija.
- **V0.2** - Galima nuskaityti iš failo, galima rūšiuoti pagal duomenis.
- **V0.3** - Perkeliamos funkcijos į external failą, išimčių valdymas.
- **V0.4** - Galima kurti testavimo failus, rušiavimas į dvi grupes.
- **V1.1** - Studentas struktūros pagrindu sukurta klasė Studentas, modifikuotos funkcijos
- **V1.2** - Pridėtas "Rule of Five" ir įvesties, išvesties operatoriai.
- **V1.5** - Nauja bazinė klasė "Zmogus", o klasė "Studentas" jos išvestinė (derived) klasė.
- **V2.0** - Dokumentacija naudojantis Doxygen. Unit Testing naudojantis Catch2.
