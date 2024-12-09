#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//maksimim‰‰r‰t huoneita
const int MAX_YHDENHENGEN = 20;
const int MAX_KAHDENHENGEN = 20;

//taulukot viedyille huoneille
int yksiHengenHuoneet[MAX_YHDENHENGEN] = { 0 }; 
int kaksiHengenHuoneet[MAX_KAHDENHENGEN] = { 0 }; 

//taulukot varauksille
vector<string> varaajat;       
vector<int> varausnumerot;     
vector<int> huonenumerot;       
vector<int> yott;               
vector<double> loppusumma;     

//tarkistetaan onko vapaita huoneita. Jos vapaa huone lˆytyy annetaan se varaukseen
int vapaahuone(int huone) {
    if (huone == 1) { //yhden hengen huone
        for (int i = 0; i < MAX_YHDENHENGEN; i++) {
            if (yksiHengenHuoneet[i] == 0) { //etsit‰‰n vapaa huone
                yksiHengenHuoneet[i] = 1; //varataan huone
                return i + 1; //palauttaa huoneen numeron (1-indeksoituna)
            }
        }
    }
    else if (huone == 2) { //kahden hengen huone (sama logiikka kun yhden hengen huoneissa)
        for (int i = 0; i < MAX_KAHDENHENGEN; i++) {
            if (kaksiHengenHuoneet[i] == 0) { 
                kaksiHengenHuoneet[i] = 1; 
                return i + 1;
            }
        }
    }
    return -1; // Palauttaa -1, jos huoneita ei ole vapaana
}

//luodaan satunnainen varausnumero v‰lilt‰ 10000-99999. Numero ei voi olla sama kun aiemmalla varauksella
int luoVarausnumero(vector<int>& varatutNumerot) {
    int numero;
    bool numeroVapaa = false;

    // arvotaan numero kunnes lˆytyy vapaa
    while (!numeroVapaa) {
        numero = rand() % 90000 + 10000; //nNumero v‰lilt‰ 10000ñ99999
        // tarkistetaan onko numero varattu
        if (find(varatutNumerot.begin(), varatutNumerot.end(), numero) == varatutNumerot.end()) {
            numeroVapaa = true; // numero on vapaa
            varatutNumerot.push_back(numero); // tallennetaan k‰ytetty numero
        }
    }
    return numero;
}

//luodaan varaus ja tallennetaan se. 
void varaus(vector<int>& varatutNumerot) {

    string varaaja;
    int huone, yot, varausnumero, huonenumero;
    double hinta, alennus, alepros, lopsum;

    //kysyt‰‰n varauksen tiedot
    cout << "Ilmoita tarvittavat tiedot" << endl;
    cout << "Varaajan nimi: ";
    cin.ignore();
    getline(cin, varaaja);
    cout << "Yhden tai kahden hengen huone (1 tai 2): ";
    cin >> huone;
    if(huone == 1 || huone == 2){ //virheilmoitusta varten (jos k‰ytt‰j‰ ei anna 1 tai 2)
    cout << "Oiden maara: ";
    cin >> yot;

    huonenumero = vapaahuone(huone); //luodaan huonenumero aliohjelmalla

    //kalkuloidaan huoneen hinta riippuen onko se yhden vai kahden hengen huone
    if(huonenumero !=-1){ 

    if (huone == 1) {
        hinta = 100.0;
    }
    else if (huone == 2) {
        hinta = 200.0;
    }
    else {
        cout << "Virheellinen huonetyyppi!" << endl;
        return;
    }

    //lasketaan kokonaishinta ennen alennusta
    double alkuperhinta = hinta * yot;

    //arvotaan alennusprosentti
    int satunnaisluku = rand() % 3;
    alepros = satunnaisluku * 10;

    //lasketaan alennus ja loppusumma
    alennus = alkuperhinta * (alepros / 100.0);
    lopsum = alkuperhinta - alennus;

    varausnumero = luoVarausnumero(varatutNumerot); //luodaan varausnumero aliohjelmalla

    //tallennetaan varaus vektoreihin
    varaajat.push_back(varaaja);
    varausnumerot.push_back(varausnumero);
    huonenumerot.push_back(huonenumero);
    yott.push_back(yot);
    loppusumma.push_back(lopsum);

    //tulostetaan lasku
    cout << "\n~~~~~ Hotelli Kultajoutsen - Lasku ~~~~~" << endl;
    cout << "Nimi: " << varaaja << endl;
    cout << "Huonetyyppi: " << (huone == 1 ? "1 hengen huone" : "2 hengen huone") << endl;
    cout << "Oiden maara: " << yot << endl;
    cout << "Varausnumero: " << varausnumero << endl;
    cout << "Huonenumero: " << huonenumero << endl;
    cout << "Loppusumma: " << lopsum << " euroa" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else {
        cout << "Kaikki huoneet ovat varattuja";
    }
    }
    else {
        cout << "Virheellinen huonetyyppi! Valitse joko 1 tai 2." << endl;
        return;
    }
}

//t‰ll‰ aliohjelmalla voidaan tarkastella olemassa olevia varauksia.
void tarkistaVaraus() {

    //kaksi eri vaihtoehtoa varauksen etsimiseen
    int valinta;
    cout << "Haluatko etsia varauksen? (1: varausnumerolla, 2: varaajan nimella): ";
    cin >> valinta;

    //haku varausnumerolla
    if (valinta == 1) {
        int numero;
        cout << "Anna varausnumero: ";
        cin >> numero;

        //etsit‰‰n vektoreista varauksen tiedot
        for (size_t i = 0; i < varausnumerot.size(); i++) { 
            if (varausnumerot[i] == numero) {
                cout << "\nVaraus loytyi!" << endl;
                cout << "Varaajan nimi: " << varaajat[i] << endl;
                cout << "Huonenumero: " << huonenumerot[i] << endl;
                cout << "Oiden maara: " << yott[i] << endl;
                cout << "Loppusumma: " << loppusumma[i] << " euroa" << endl;
                return;
            }
        }
        cout << "Varausta ei lˆytynyt annetulla numerolla." << endl;

    }
    else if (valinta == 2) { //haku nimell‰
        string nimi;
        cin.ignore();
        cout << "Anna varaajan nimi: ";
        getline(cin, nimi);

        //etsit‰‰n vektoreista varauksen tiedot
        for (size_t i = 0; i < varaajat.size(); i++) {
            if (varaajat[i] == nimi) {
                cout << "\nVaraus loytyi!" << endl;
                cout << "Varaajan nimi: " << varaajat[i] << endl;
                cout << "Huonenumero: " << huonenumerot[i] << endl;
                cout << "Oiden maara: " << yott[i] << endl;
                cout << "Loppusumma: " << loppusumma[i] << " euroa" << endl;
                return;
            }
        }
        cout << "Varausta ei loytynyt annetulla nimella." << endl;

    }
    else {
        cout << "Virheellinen valinta!" << endl;
    }
}

//p‰‰ohjelma (eli p‰‰valikko)
int main() {

    vector<int> varatutNumerot; //k‰ytetyt varausnumerot
    int valinta;
    srand(time(0)); 

    //tulostetaan p‰‰valikko
    while (true){

    cout << endl;
    cout << "~~~~~ Hotelli Kultajoutsen ~~~~~" << endl;
    cout << "1. Luo varaus" << endl;
    cout << "2. Tarkista varaus" << endl;
    cout << "3. Poistu" << endl;
    cout << "Valitse vaihtoehto (1-3): ";
    cin >> valinta;

    //tehd‰‰n toiminto jonka k‰ytt‰j‰ haluaa aliohjelmien avulla. lis‰ksi jokaisen toiminnon p‰‰tteeksi kysyt‰‰n haluaako k‰ytt‰j‰ palata p‰‰valikkoon
    if (valinta == 1) {
        cout << endl;
        varaus(varatutNumerot);

        char jatka;
        cout << "\nHaluatko palata valikkoon? (k/e): ";
        cin >> jatka;

        if (jatka == 'k' || jatka == 'K') {
            continue;
            
        }
        else if (jatka == 'e' || jatka == 'E') {
            cout << "Ohjelma suljetaan." << endl;
            break;
        }
        else {
            cout << "Virheellinen syote! Palataan valikkoon." << endl;
            continue;
            
        }

    }
    else if (valinta == 2) {
        cout << endl;
        tarkistaVaraus();

        char jatka;
        cout << "\nHaluatko palata valikkoon? (k/e): ";
        cin >> jatka;

        if (jatka == 'k' || jatka == 'K') {
            continue;

        }
        else if (jatka == 'e' || jatka == 'E') {
            cout << "Ohjelma suljetaan." << endl;
            break;
        }
        else {
            cout << "Virhe! Palataan valikkoon." << endl;
            continue;

        }
    }
    else if (valinta == 3) {
        cout << "Ohjelma suljetaan." << endl;
        break;
    }
    else {
        cout << "valinta virheellinen";
        
    }
    cout << endl;
    }

    return 0;

}

//tyˆ on 4-5 pisteen tyˆ. Ainoa tapa miten ohjelma voi kaatua on jos syˆtteeksi antaa v‰‰r‰nlaisen arvon esim jos ˆiden m‰‰r‰ksi laittaa vaikka kirjaimen. 