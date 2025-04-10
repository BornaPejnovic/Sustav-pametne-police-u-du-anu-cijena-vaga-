# Pametna polica – Sustav za praćenje zaliha pomoću Arduina

## Opis projekta  
Ovaj projekt je rezultat timskog rada u sklopu projektnog zadatka kolegija **Razvoj ugrađenih sustava** na **Tehničkom veleučilištu u Zagrebu**.

Cilj projekta je izraditi prototip **pametne police** koji pomoću Arduina i senzora prati stanje zaliha proizvoda u stvarnom vremenu, te obavještava zaposlenike kada je potrebno nadopuniti proizvode.  
Motivacija za ovaj projekt bila je poboljšanje učinkovitosti maloprodajnih sustava, smanjenje ljudskih pogrešaka i omogućavanje brže reakcije na niske zalihe, sve koristeći cjenovno pristupačne komponente.

---

## Funkcijski zahtjevi  

- Sustav mora očitavati masu proizvoda pomoću senzora težine (HX711 + vaga).
- Kada količina proizvoda padne ispod definiranog minimuma, mora se aktivirati LED indikator ili zvučni signal.
- Sustav mora u stvarnom vremenu slati podatke putem Wi-Fi modula (ESP8266) na centralno računalo ili mobilni uređaj.
- (Opcionalno) RFID čitač može identificirati točne proizvode na polici.
- Sustav mora biti pouzdan i jednostavan za korištenje i nadogradnju.

---

## Tehnologije  

- **Arduino Uno/Nano** – mikrokontroler za upravljanje komponentama  
- **HX711 + Load Cell** – za mjerenje težine proizvoda na polici  
- **ESP8266** – Wi-Fi modul za komunikaciju  
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

