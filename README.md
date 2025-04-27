# Pametna polica – Sustav za praćenje zaliha pomoću Arduina

## Opis projekta  
Ovaj projekt je rezultat timskog rada u sklopu projektnog zadatka kolegija **Razvoj ugrađenih sustava** na **Tehničkom veleučilištu u Zagrebu**.

Cilj projekta je izraditi prototip **pametne police** koji pomoću Arduina i senzora prati stanje zaliha proizvoda u stvarnom vremenu, te obavještava zaposlenike kada je potrebno nadopuniti proizvode.  
Motivacija za ovaj projekt bila je poboljšanje učinkovitosti maloprodajnih sustava, smanjenje ljudskih pogrešaka i omogućavanje brže reakcije na niske zalihe, sve koristeći cjenovno pristupačne komponente.

---

## Funkcijski zahtjevi  

- Uređaj mora mjeriti masu predmeta pomoću senzora HX711.
- Uređaj mora prikazivati trenutačnu masu na LCD zaslonu.
- Uređaj mora slati obavijesti ESP-01 modulu ako masa padne ispod zadane granice.
- Uređaj mora signalizirati kritične situacije paljenjem LED-ice.	

---

## Tehnologije  

- **Arduino Mega** – mikrokontroler za upravljanje komponentama  
- **HX711 + Load Cell** – za mjerenje težine proizvoda na polici  
- **ESP-01** – Wi-Fi modul za komunikaciju  
- **LED indikator** – vizualno upozorenje o niskim zalihama  
- **RFID modul** (opcijski) – za identifikaciju proizvoda  
- **C/C++ (Arduino IDE)** – programski jezik za upravljanje komponentama  

---

## Članovi tima  

| Ime i prezime         | GitHub profil                                     |
|-----------------------|---------------------------------------------------|
| Kristijan Jagunec     | [@kjagunec](https://github.com/kjagunec)          |
| Borna Pejnović        | [@BornaPejnovic](https://github.com/BornaPejnovic)|

---

## Wokwi

[Link na projekt](https://wokwi.com/projects/428142158967422977)

---

