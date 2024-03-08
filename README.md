Ši programa yra studentų duomenų valdymo sistema, kuri leidžia vartotojui įvesti studentų duomenis įvairiais būdais ir pateikti jų galutinius įvertinimus. Pagrindinės programos funkcijos:

    1.  Duomenų Įvedimas: Vartotojas gali įvesti studentų duomenis rankiniu būdu, generuoti juos atsitiktinai, arba nuskaityti iš failo.

    2.  Įvertinimų Skaičiavimas: Programa apskaičiuoja studentų galutinius įvertinimus pagal jų namų darbų ir egzaminų rezultatus naudojant vidurkį ar medianą.

    3.  Duomenų Išvedimas: Galiausiai, vartotojas gali pasirinkti duomenų rikiavimo būdą ir programa pateikia surikiuotą studentų sąrašą su jų vardais, pavardėmis ir galutiniais įvertinimais.

Programos meniu siūlo penkias pagrindines pasirinkimo galimybes, kiekviena iš jų leidžia vartotojui įvesti arba gauti studentų duomenis skirtingais būdais:

    1.  Studento duomenų įvedimas rankiniu būdu: Ši funkcija leidžia vartotojui įvesti visus studento duomenis, įskaitant vardą, pavardę, namų darbų rezultatus ir egzamino įvertinimą, rankiniu būdu.

    2.  Įvedimas rankiniu būdu su atsitiktiniais pažymiais: Šioje funkcijoje vartotojas įveda studento vardą ir pavardę, o programa automatiškai generuoja namų darbų ir egzamino įvertinimus.

    3.  Visiškai atsitiktinis studentų duomenų generavimas: Ši funkcija leidžia programai automatiškai sugeneruoti visus studento duomenis, įskaitant vardą, pavardę ir visus įvertinimus.

    4.  Duomenų nuskaitymas iš failo: Ši funkcija leidžia vartotojui nuskaityti studentų duomenis iš iš anksto paruošto tekstinio failo, pavyzdžiui, „kursiokai.txt“.

    5.  Baigti darbą ir rodyti rezultatus: Pasirinkus šią funkciją, programa leidžia vartotojui pasirinkti, kaip nori rikiuoti galutinius duomenis (pagal vardą, pavardę, galutinį įvertinimą ir pan.) ir pateikia galutinę ataskaitą su visais studentų įrašais, jų vardais, pavardėmis ir galutiniais įvertinimais.

---------------------
    Spartos palyginimas.

    | Užduočių atlikimas (s)  | 1000 | 10000 | 100000 | 1000000 | 10000000 |
    |-------------------------|------|-------|--------|---------|----------|
    | Deque                   |      |       |        |         |          |
    | Failų nuskaitymas       | 0.02 | 0.036 | 0.298  | 2.95    | 10.732   |
    | Skirstymas į grupes     |  0   | 0.015 |  0.167 |  1.867  | 56.521   |
    | Rūšiavimas didėjimo t.  | 0.011| 0.053 |  1.1   |  12.6   | 96.79    |
    |-------------------------|------|-------|--------|---------|----------|
    | Vector                  |      |       |        |         |          |
    | Failų nuskaitymas       | 0.01 |  0.03 |  0.26  |  2.55   |  25.99   |
    | Skirstymas į grupes     |  0   |  0.01 |  0.035 |  0.329  |  3.766   |
    | Rūšiavimas didėjimo t.  |  0   | 0.083 |  0.185 |  2.84   |  32.94   |
    |-------------------------|------|-------|--------|---------|----------|
    | List                    |      |       |        |         |          |
    | Failų nuskaitymas       |  0   | 0.024 |  0.278 |  2.763  |  28.461  |
    | Skirstymas į grupes     |  0   |  0.01 |  0.101 |  0.915  |  18.026  |
    | Rūšiavimas didėjimo t.  |  0   |  0.002|  0.051 |  0.569  |  8.465   |

