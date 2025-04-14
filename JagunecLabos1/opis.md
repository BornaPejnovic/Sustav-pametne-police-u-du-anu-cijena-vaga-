# Upravljanje Ulaznim Senzorima i Periodičkim Aktivnostima uz Korištenje Timer Prekida

## 1. Opis sustava  
Ovaj sustav koristi Arduino mikrokontroler za upravljanje ulaznim uređajima (dvije tipke, senzor pokreta i potenciometar) te omogućuje periodičko očitavanje analogne vrijednosti pomoću tajmerskog prekida. Sustav koristi **TimerOne biblioteku** za upravljanje prekidima tajmera, dok se ulazni signali detektiraju putem vanjskih prekida. Sustav periodički očitava vrijednost potenciometra i bljeska LED diodom, a uz to reagira i na korisničke ulaze (tipke i senzor kretanja).  
Cilj je omogućiti interaktivno upravljanje i periodičku obradu podataka u stvarnom vremenu.

---

## 2. Funkcionalnosti

### 2.1. Rukovanje prekidima tipkala  
Sustav koristi dva digitalna ulaza za detekciju pritiska tipkala.  
- Tipkalo 1 je spojeno na pin **2**.  
- Tipkalo 2 je spojeno na pin **3**.  

Oba ulaza koriste vanjske prekide (FALLING rub). Kada korisnik pritisne jedno od tipkala, u prekidnoj rutini se postavlja odgovarajući flag (`button1Pressed`, `button2Pressed`), a u glavnoj petlji se ispisuje poruka putem serijske komunikacije.

### 2.2. Rukovanje senzorom pokreta  
Na digitalni pin **18** spojen je senzor pokreta. Kada senzor detektira prisutnost (LOW signal), aktivira se prekidna rutina `motionSensorISR`, koja postavlja `motionDetected` flag.  
U `loop()` funkciji se zatim ispisuje poruka da je kretanje detektirano.

### 2.3. Rukovanje tajmer prekidom  
TimerOne generira prekid svake sekunde (1 Hz). Pri aktivaciji tajmera:  
- Očitava se vrijednost s potenciometra spojenog na analogni pin A0.  
- Stanje LED diode na pinu 13 se mijenja (bljeskanje).  
- Podaci se ispisuju u serijski monitor.  

Prekidni signal postavlja `timerFlag`, koji se zatim obrađuje u `loop()` funkciji.

### 2.4. Očitavanje potenciometra  
Potenciometar je spojen na analogni pin A0. Vrijednost se očitava svakih 1 sekundu, što omogućuje kontinuirano praćenje njegovog položaja. Očitavanje se pokreće iz tajmerskog prekida.

---

## 3. Funkcionalni zahtjevi

| ID    | Opis                                                                 |
|-------|----------------------------------------------------------------------|
| FR-1  | Sustav mora detektirati pritisak tipke 1 (prekid na pinu 2).        |
| FR-2  | Sustav mora detektirati pritisak tipke 2 (prekid na pinu 3).        |
| FR-3  | Sustav mora reagirati na senzor pokreta spojen na pin 18.           |
| FR-4  | Sustav mora generirati tajmer prekid svake 1 sekunde.               |
| FR-5  | U svakom tajmerskom prekidu, mora se očitati vrijednost potenciometra. |
| FR-6  | LED dioda mora bljeskati prilikom svakog tajmerskog prekida.        |
| FR-7  | Sustav mora ispisivati poruke u serijski monitor za svaki ulazni događaj. |
| FR-8  | Svaki flag (`button1Pressed`, `button2Pressed`, `motionDetected`, `timerFlag`) mora se ispravno postaviti i resetirati. |

---

## 4. Zaključak  
Sustav omogućuje pouzdano praćenje ulaznih signala i periodičko izvršavanje zadataka pomoću tajmera. Korištenje **prekida** omogućuje promptnu reakciju na događaje bez potrebe za stalnim nadziranjem unutar glavne petlje, čime se povećava efikasnost sustava. Uz to, TimerOne omogućuje točno tempirano izvršavanje zadataka, kao što su očitavanje analogne vrijednosti i upravljanje LED diodom. Sustav je fleksibilan i može se lako proširiti s dodatnim senzorima ili funkcionalnostima.
