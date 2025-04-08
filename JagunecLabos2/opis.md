# Upravljanje Potrošnjom Energije Mikrokontrolera uz Korištenje Sleep Modova

## 1. Opis sustava
Sustav koristi Arduino mikrokontroler za upravljanje energijom putem različitih sleep modova. Glavna funkcionalnost sustava uključuje smanjenje potrošnje energije korištenjem **sleep mode-a** Power-down, a sustav je konfiguriran da izlazi iz sleep moda na temelju dva prekida: vanjskog prekida (tipka) i timer prekida. Korištenje sleep modova omogućuje mikrokontroleru da uštedi energiju kada nije aktivan, dok prekidi omogućuju mikrokontroleru da se probudi i izvrši zadatke poput treptanja LED diode. Sustav također koristi **LowPower** biblioteku za upravljanje sleep modovima i **TimerOne** biblioteku za upravljanje vremenskim prekidima.

## 2. Funkcionalnosti

### 2.1. Rukovanje prekidima tipkala
Sustav koristi **vanjski prekid** na tipki za buđenje mikrokontrolera iz sleep moda. Tipka je povezana na **pin 2** i koristi **FALLING** rub za aktiviranje prekida. Kada se tipka pritisne, mikrokontroler izlazi iz sleep moda i trepće **LED diodom** tri puta. Tipka se koristi za buđenje mikrokontrolera iz spavanja kako bi izvršio osnovnu funkcionalnost (treptanje LED diode).

### 2.2. Rukovanje prekidom tajmera
**Tajmer (Timer1)** generira prekid svakih 10 sekundi. Kad se tajmer aktivira, mikrokontroler izlazi iz sleep moda i trepće LED diodom tri puta. Tajmer prekid omogućuje automatsko buđenje mikrokontrolera nakon unaprijed definiranog vremenskog intervala (10 sekundi), čime se optimizira energetska učinkovitost sustava.

### 2.3. Rukovanje sleep modovima
Mikrokontroler koristi **LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF)** kako bi prešao u **Power-down mode** kad nije aktivan. U ovom modu, mikrokontroler smanjuje potrošnju energije isključujući većinu perifernih uređaja (uključujući ADC i BOD). Nakon što se dogodi prekid (bilo putem tipke ili tajmera), mikrokontroler izlazi iz sleep moda i izvršava osnovnu funkciju (treptanje LED diode).

### 2.4. Izlazak iz sleep moda
Postoje dva glavna načina za izlazak iz sleep moda:
- **Prekidi tipke (vanjski prekid)**: Kada korisnik pritisne tipku povezanu na pin 2, mikrokontroler izlazi iz sleep moda i trepće LED diodom.
- **Tajmer (Timer1 interrupt)**: Mikrokontroler se također može probuditi automatski nakon određenog vremenskog intervala (10 sekundi) koristeći tajmer prekid.

### 2.5. Optimizacija potrošnje energije
Mikrokontroler koristi **LowPower** biblioteku za prijelaz u sleep modove i upravljanje potrošnjom energije. Korištenje **sleep mode-a** kao što je Power-down omogućuje značajno smanjenje potrošnje energije kada sustav nije aktivan. Korištenje prekida (tipka i tajmer) omogućava sustavu da bude aktivan samo kada je potrebno, čime se povećava energetska učinkovitost.

### 2.6. Realizacija i testiranje rada sustava
Sustav je realiziran na **Arduino platformi** i testiran u stvarnim uvjetima kako bi se osiguralo da se sustav učinkovito prebacuje u sleep mode i izlazi iz njega na temelju prekida. Testiranja uključuju provjeru vremena odziva pri aktiviranju prekida te mjerenje potrošnje energije u različitim sleep modovima. Potrošnja energije sustava je testirana pomoću multimetra ili mjerača potrošnje energije.

## 3. Funkcionalni zahtjevi

| ID   | Opis                                                                 |
|------|----------------------------------------------------------------------|
| **FR-1** | Sustav mora omogućiti detekciju pritiska tipke za buđenje mikrokontrolera. |
| **FR-2** | Prekid tipke mora omogućiti buđenje mikrokontrolera i treptanje LED diode. |
| **FR-3** | Sustav mora koristiti **LowPower** biblioteku za prijelaz u sleep mode i smanjenje potrošnje energije. |
| **FR-4** | Timer prekid mora automatski probuditi mikrokontroler svakih 10 sekundi. |
| **FR-5** | Mikrokontroler mora koristiti **Power-down** mod za maksimalno smanjenje potrošnje energije. |
| **FR-6** | Mikrokontroler mora reagirati na prekid tipke i izlaziti iz sleep moda kako bi trepćao LED diodom. |
| **FR-7** | Potrošnja energije mora biti testirana u različitim sleep modovima i uspoređena s aktivnim režimom. |
| **FR-8** | Prekid tajmera mora imati prednost u odnosu na vanjski prekid tipke. |
| **FR-9** | Potrošnja energije mora biti minimizirana u svim fazama rada sustava (aktivnom i sleep modu). |
| **FR-10** | Svaka funkcionalnost u sustavu mora biti testirana za ispravno reagiranje na prekide i sleep modove. |

## 4. Zaključak
Ovaj sustav optimizira potrošnju energije mikrokontrolera pomoću sleep modova i prekida. Mikrokontroler se prebaci u **Power-down** mod kada nije aktivan, čime se smanjuje potrošnja energije, dok prekidi omogućuju probuditi sustav kada je potrebno izvršiti zadatak (npr. treptanje LED diode). Korištenje **LowPower** i **TimerOne** biblioteka omogućuje učinkovito upravljanje energijom u sustavu.
