#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <vector>
#include <set>
#include <ctime>
#include <filesystem>

using std::cout, std::cin, std::string, std::vector, std::bitset, std::set;

/**
 *@class Haslo - klasa przechowujaca informacje o jednym hasle
 */
class Haslo{
    string nazwa;
    string zawartosc;
    string kategoria;
    string serwis;
    string login;
public:
    Haslo(string nazwa, string zawartosc, string kategoria, string serwis, string login):
        nazwa(nazwa), zawartosc(zawartosc), kategoria(kategoria), serwis(serwis), login(login){};

    /**
    *wyswietla wszystkie pola klasy
    */
    void wyswietl(){
        cout << "\nnazwa: " << nazwa << "\nhaslo: " << zawartosc << "\nkategoria: " << kategoria << "\nserwis: " << serwis << "\nlogin: " << login << "\n";
    }
    const string &getNazwa() const {
        return nazwa;
    }
    const string &getZawartosc() const {
        return zawartosc;
    }
    const string &getKategoria() const {
        return kategoria;
    }
    const string &getSerwis() const {
        return serwis;
    }
    const string &getLogin() const {
        return login;
    }
    void setNazwa(const string &nazwa) {
        Haslo::nazwa = nazwa;
    }

    void setZawartosc(const string &zawartosc) {
        Haslo::zawartosc = zawartosc;
    }

    void setKategoria(const string &kategoria) {
        Haslo::kategoria = kategoria;
    }

    void setSerwis(const string &serwis) {
        Haslo::serwis = serwis;
    }

    void setLogin(const string &login) {
        Haslo::login = login;
    }
};

/**
 *  @fn pyta uzytkownika o szczegoly i na ich podstawie generuje haslo
 */
void generuj_haslo(string &haslo){
    int ilosc_znakow = -1;
    cout << "GENERATOR HASEL\n"
            "Podaj ilosc znakow: ";
    while(ilosc_znakow <= 0){
        cin >> ilosc_znakow;
        if(ilosc_znakow <= 0)
            cout << "\nPodaj poprawna dugosc hasla: ";
    }
    cout << '\n';

    string wielkie;
    bool czyWielkie = false;
    while(wielkie.empty()) {
        cout << "Czy maja wystepowac wielkie litery? (zatwierdz 'tak')\n";
        cin >> wielkie;
        if(wielkie == "tak")
            czyWielkie = true;
        cout << "\n";
    }

    string male;
    bool czyMale = false;
    while(male.empty()) {
        cout << "Czy maja wystepowac male litery? (zatwierdz 'tak')\n";
        cin >> male;
        if(male == "tak")
            czyMale = true;
        cout << "\n";
    }

    string znaki;
    bool czyZnaki = false;
    while(znaki.empty()) {
        cout << "Czy maja wystepowac znaki specjalne? (zatwierdz 'tak')\n";
        cin >> znaki;
        if(znaki == "tak")
            czyZnaki = true;
        cout << "\n";
    }
    cin.ignore();

    string baza = "0123456789";
    znaki = "!@#$%^&*";
    male = "abcdefghijklmnopqrstuvwxyz";
    wielkie = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if(czyZnaki)
        baza += znaki;
    if(czyMale)
        baza += male;
    if(czyWielkie)
        baza += wielkie;

    haslo.clear();
    int random;
    for(int i = 0; i < ilosc_znakow; i++){
        random = rand() % baza.length();
        haslo += baza[random];
    }
    cout << "Wygenerowane haslo: " << haslo << '\n';

}

/**
 *@fn sprawdza czy haslo jest silne i zwraca wartosc logiczna
 */
bool sprawdz_sile_hasla(string &haslo, const vector<Haslo> baza_haslo){
    bool czy_dlugie = false;
    bool czy_male = false;
    bool czy_duze = false;
    bool czy_znaki = false;
    bool czy_uzyte = false;
    cout << "\n";
    if(haslo.length() >= 8){
        czy_dlugie = true;
        cout << "+haslo zawiera przynajmniej 8 znakow\n";
    }else{
        cout << "-haslo jest krotsze niz 8 znakow\n";
    }
    for(char znak : haslo){
        if(std::isupper(znak)){
            czy_duze = true;
        }else if( std::islower(znak)){
            czy_male = true;
        }else if(std::isdigit(znak)){
            czy_znaki = true;
        }
    }
    for(auto h : baza_haslo){
        if(h.getZawartosc() == haslo)
            czy_uzyte = true;
    }

    if(czy_uzyte)
        cout << "-haslo jest juz uzyte w innym miejscu\n";
    else
        cout << "+haslo nie jest jeszcze nigdzie uzyte\n";

    if(czy_duze)
        cout << "+haslo zawiera duze litery\n";
    else
        cout << "-haslo nie zawiera duzych liter\n";

    if(czy_male)
        cout << "+haslo zawiera male litery\n";
    else
        cout << "-haslo nie zawiera malych liter\n";

    if(czy_znaki)
        cout << "+haslo zawiera cyfry\n";
    else
        cout << "-haslo nie zawiera cyfr\n";

    return (czy_dlugie && czy_duze && czy_male && czy_znaki && !czy_uzyte);
}

/**
 *@fn generuje hash hasla glownego i zwraca go w postaci string
 */
string wygeneruj_hash(const string haslo_szyfrujace){
    std::size_t hash_hasla = std::hash<std::string>{}(haslo_szyfrujace);
    std::bitset<sizeof(size_t)*8> bit_hash(hash_hasla);
    return bit_hash.to_string();
}

/**
 *@fn zapisuje nowy hash hasla glownego do pliku i zwraca jego wartosc w postaci string
 */
string zapisz_nowy_hash(const string filePath){
    auto outStream = std::fstream(filePath,std::ios::out|std::ios::app);

    string haslo;
    string hash_hasla;
    while(haslo.empty()){
        cout << "Podaj nowe haslo szyfrujace: ";
        std::getline(cin, haslo);
        hash_hasla = wygeneruj_hash(haslo);
    }

    outStream<<hash_hasla<<'\n';
    outStream.close();
    cout <<" Wygenerowano nowy hash hasla w pliku. Zapamietaj swoje haslo: "<< haslo << '\n';
    return haslo;

}

/**
 *@fn generuje timestamp i zwraca go w postaci vector<string>
 */
auto wygeneruj_timestamp(){
    time_t czas = time(0);

    tm *lt = localtime(&czas);
    int g = lt->tm_hour;
    int m = lt->tm_min;
    int s = lt->tm_sec;

    string godzina = std::to_string(g);
    string minuta = std::to_string(m);
    string sekunda = std::to_string(s);

    if(g < 10)
        godzina = '0'+godzina;
    if(m < 10)
        minuta = '0'+minuta;
    if(s < 10)
        sekunda = '0'+sekunda;

    vector<string> timestamp = {godzina,minuta,sekunda};
    return timestamp;
}

/**
 *@fn dopisuje timestamp na koncu pliku
 */
void dopisz_timestamp(const string filePath){
    auto inFile = std::fstream(filePath, std::ios::in);

    vector<string> timestamp = wygeneruj_timestamp();

    vector<string> lines;
    string line;

    while(std::getline(inFile,line)){
        lines.push_back(line);
    }
    inFile.close();

    auto outFile = std::fstream(filePath, std::ios::out | std::ios::trunc);
    for(int i = 0; i < lines.size(); i++){
        switch(i){
            case 6: outFile << timestamp.at(0) << lines.at(i) << '\n';
                break;
            case 12: outFile << timestamp.at(1) << lines.at(i) << '\n';
                break;
            case 18: outFile << timestamp.at(2) << lines.at(i) << '\n';
                break;
            default: outFile << lines.at(i) << '\n';
        }
    }
    outFile.close();
}

/**
 *@fn sprawdza czy podane haslo jest zgodne z hashem hasla w pliku i zwraca wartosc logiczna
 */
bool zweryfikuj_hash(const string filePath, const string haslo_szyfrujace){
    dopisz_timestamp(filePath);

    if(haslo_szyfrujace.empty())
        return false;

    auto inStream = std::fstream(filePath, std::ios::in);
    string hash_hasla;
    std::getline(inStream,hash_hasla);
    inStream.close();

    string hash_podanego_hasla = wygeneruj_hash(haslo_szyfrujace);
    cout << hash_podanego_hasla << '\n';
    cout << hash_hasla << '\n';
    return (hash_podanego_hasla == hash_hasla);
}

/**
 *@fn zapisuje do pliku zaszyfrowana pojedyncza linie
 * szyfrowanie polega na zamianie kazego chara na bitset, nastepnie xor z kolejnym znakiem hasla szyfrujacego
 * a na koncu wszystkie bity sa negowane
 */
void zapis_do_pliku(const string filePath, const string text, const string haslo_szyfrujace){
    auto outStream = std::fstream(filePath, std::ios::out | std::ios::app);
    for( int i = 0; i < text.size(); i++){
        char s = haslo_szyfrujace[i%haslo_szyfrujace.size()];
        std::bitset<8> szyfr(s);
        std::bitset<8> znak(text[i]);

        znak ^= szyfr;
        znak = ~znak;

        outStream << znak;
    }
    outStream << '\n';
    outStream.close();
}

/**
 *@fn metoda ta roszyfrowuje i odczytuje z pliku hasla i kategorie, a natepnie pobiera je do zmiennych lokalnych
 */
void odczyt_z_pliku(const string filePath, const string haslo_szyfrujace, vector<Haslo> &baza_haslo, set<string> &baza_kategoria){
    auto inStream = std::fstream(filePath, std::ios::in);
    string val;
    string fragment;
    string result;

    string haslo;
    string kategoria;
    string portal;
    string nazwa;
    string login;

    int line = 0;
    int counter;
    while(std::getline(inStream,val)) {
        counter = 0;

        //nie rozszyfrowuje linii w ktorych sa timestampy i hash hasla
        if(line%6 != 0){
            //odszyfrowywanie poszczegolnych linii
            for(int i = 0; i < val.size(); i += 8) {
                //wydzielam z bitsetu 8 znakow czyli zakodowanego jednego chara
                std::bitset<8> bitchar(val.substr(i, 8));

                //odwracam negacje bitowa
                bitchar = ~bitchar;
                std::bitset<8> szyfr(haslo_szyfrujace[counter % haslo_szyfrujace.size()]);

                bitchar = bitchar ^ szyfr;
                //to_ulong zamienia bitset na long, a nastepnie zamieniam long na char
                char converted_char = (char) (bitchar.to_ulong());
                result += converted_char;
                counter++;
            }
        }

        //przydzielanie odszyfrowywanych wartosci
        if (line != 0){
            switch (line % 6) {
                case 0:
                    baza_haslo.push_back(Haslo(nazwa, haslo, kategoria, portal, login));
                    haslo.clear();
                    kategoria.clear();
                    portal.clear();
                    nazwa.clear();
                    login.clear();
                    break;
                case 1:
                    kategoria = result;
                    baza_kategoria.insert(kategoria);
                    break;
                case 2:
                    haslo = result;
                    break;
                case 3:
                    nazwa = result;
                    break;
                case 4:
                    portal = result;
                    break;
                case 5:
                    login = result;
                    break;
            }
        }
        result.clear();
        line++;
    }

    if(!haslo.empty() && !kategoria.empty() && !nazwa.empty())
        baza_haslo.push_back(Haslo(nazwa,haslo,kategoria,portal,login));

    inStream.close();
}

/**@fn usuwa poprzednia zawartosc pliku, a nastepnie zapisuje do pliku pobrane wczesniej hasla i informacje wedlug ustalonego wzoru
 *
 * //wzor zapisu :
    // 0. hash hasla glownego
    // 1. linia kategoria
    // 2. linia tekst reprezentujacy haslo
    // 3. linia nazwa hasla
    // 4. linia strona/serwis
    // 5. linia login
    // itd
    // 6. linia godzina + bzdury
    // 12. linia minuta + bzdury
    // 18. linia sekunda + bzdury
 */
void zapisz_calosc_do_pliku(const string filePath, const string haslo_szyfrujace, const vector<Haslo> baza_haslo){
    string hash_hasla = wygeneruj_hash(haslo_szyfrujace);

    auto czyszczenie_pliku = std::fstream(filePath, std::ios::out | std::ios::trunc);
    czyszczenie_pliku.close();

    string text;
    bool czyPierwszaLinia = true;
    for(int i = 0; i < baza_haslo.size(); i++){
        Haslo haslo = baza_haslo.at(i);
        for(int line = 0; line < 6; line++){
            if(!czyPierwszaLinia){
                switch(line%6){
                    case 0:
                        text = "random";
                        break;
                    case 1:
                        text = haslo.getKategoria();
                        break;
                    case 2:
                        text = haslo.getZawartosc();
                        break;
                    case 3:
                        text = haslo.getNazwa();
                        break;
                    case 4:
                        text = haslo.getSerwis();
                        break;
                    case 5:
                        text = haslo.getLogin();
                        break;
                }
                zapis_do_pliku(filePath,text,haslo_szyfrujace);
            }else{
                czyPierwszaLinia = false;
                auto outStream = std::fstream(filePath, std::ios::out | std::ios::app);
                outStream << wygeneruj_hash(haslo_szyfrujace) << '\n';
            }

        }
    }
    zapis_do_pliku(filePath,"random",haslo_szyfrujace);

    dopisz_timestamp(filePath);
}

/**
 * @fn dodaje haslo do zmiennych lokalnych i zapisuje je w pliku
 */

void dodaj_haslo(const string filePath, const string haslo_szyfrujace, vector<Haslo> &baza_haslo,set<string> &kategorie){
    string haslo;
    string nazwa;
    string serwis;
    string login;
    string kategoria;

    while(nazwa.empty()) {
        cout << "Wprowadz nazwe hasla: ";
        std::getline(cin, nazwa);
        cout << '\n';
        if(nazwa.empty())
            cout << "Nie wprowadzono wartosci! \n";
    }

    while(haslo.empty()){
        cout << "Wprowadz haslo (albo wygeneruj wpisujac 'gen'): ";
        std::getline(cin,haslo);
        cout <<'\n';
        if(haslo.empty()){
            cout << "Nie wprowadzono wartosci! \n";
        }else if(haslo == "gen"){
            generuj_haslo(haslo);

            cout << "Czy na pewno chcesz zapisac to haslo? (zatwierdz 'tak')\n";
            string zatwierdz;
            std::getline(cin,zatwierdz);
            if(zatwierdz != "tak")
                haslo.clear();
        }else if(!sprawdz_sile_hasla(haslo,baza_haslo)){
            cout << "Czy na pewno chcesz zapisac to haslo? (zatwierdz 'tak')\n";
            string zatwierdz;
            std::getline(cin,zatwierdz);
            if(zatwierdz != "tak")
                haslo.clear();
        }

    }

    while(kategoria.empty()){
        cout << "\nJezeli chcesz uzyc zapisanej kategorii wpisz 'z', a jezeli chcesz stworzyc kategorie wpisz jej nazwe: ";
        std::getline(cin, kategoria);
        if(kategoria == "z"){
            if(kategorie.empty()){
                cout << "Brak zapisanych kategorii! \n";
                kategoria.clear();
            }else{
                //przeksztalcam set na vector, zeby moc wyciagnac wartosci o okreslonych indexach
                vector<string> katVector(kategorie.begin(), kategorie.end());
                for( int i = 0; i < katVector.size(); i++){
                    cout << '\n' << i << ". " << katVector.at(i);
                }

                int nrKategorii = -1;
                while(nrKategorii < 0 || nrKategorii >= katVector.size()){
                    cout << '\n' << "Wybierz numer kategorii: ";
                    cin >> nrKategorii;
                    cout << '\n';
                    if(nrKategorii < 0 || nrKategorii >= katVector.size())
                        cout << "Wprowadzono numer z poza zakresu! \n";
                }
                cin.ignore();
                kategoria = katVector.at(nrKategorii);
            }
        }else if(kategoria.size() > 0){
            kategorie.insert(kategoria);
        }
    }

    cout << '\n'
    <<"Dodatkowe informacje (jezeli nie chcesz ich wprowadzac naciskaj enter) \n";

    cout << "Wprowadz nazwe serwisu/portalu: ";
    std::getline(cin,serwis);
    cout << '\n';

    cout << "Wprowadz login: ";
    std::getline(cin,login);
    cout << '\n';

    Haslo nowe_haslo(nazwa,haslo, kategoria,serwis,login);
    nowe_haslo.wyswietl();
    baza_haslo.push_back(nowe_haslo);

    zapisz_calosc_do_pliku(filePath,haslo_szyfrujace,baza_haslo);
}

/**
 *@fn usuwa kategorie wraz z haslami, ktore do niej naleza
 */
void usun_kategorie(const string filePath, const string haslo_szyfrujace, vector<Haslo> &baza_haslo, set<string> &kategorie){
    string kat_do_usuniecia;

    vector<string> katVector(kategorie.begin(), kategorie.end());
    cout << "Kategorie do usuniecia: ";
    for( int i = 0; i < katVector.size(); i++){
        cout << '\n' << i << ". " << katVector.at(i);
    }

    int nrKategorii = -1;
    while(nrKategorii < 0 || nrKategorii >= katVector.size()){
        cout << '\n' << "Wybierz numer kategorii: ";
        cin >> nrKategorii;
        cout << '\n';
        if(nrKategorii < 0 || nrKategorii >= katVector.size())
            cout << "Wprowadzono numer z poza zakresu! \n";
    }
    kat_do_usuniecia = katVector.at(nrKategorii);

    std::erase_if(baza_haslo, [kat_do_usuniecia](Haslo& haslo){
        return haslo.getKategoria() == kat_do_usuniecia;
    });

    std::erase_if(kategorie,[kat_do_usuniecia](string kat){
        return kat == kat_do_usuniecia;
    });

    zapisz_calosc_do_pliku(filePath,haslo_szyfrujace,baza_haslo);
}

/**
 *@fn dodaje kategorie do set-u
 */
void dodaj_kategorie(set<string> &kategorie){
    string nowe;
    cout << "Podaj nazwe kategorii: ";
    std::getline(cin,nowe);
    cout <<'\n';
    if(kategorie.contains(nowe))
        cout << "Kategoria juz istnieje\n";
    else
        cout << "Stworzono kategorie: " << nowe << '\n';
    kategorie.insert(nowe);
}

//@fn wyswietla wszystkie hasla
void wyswietl_hasla(const vector<Haslo> &baza_haslo){
    cout << "\nZapisane hasla: \n";
    int i = 0;
    for( auto h : baza_haslo){
        cout << '\n' << i <<". ";
        h.wyswietl();
        i++;
    }
}

/**
 *@fn usuwa haslo
 */
void usun_haslo(const string filePath, const string haslo_szyfrujace, vector<Haslo> &baza_haslo){
    cout << "Zapisane hasla: \n";
    for(int i = 0; i < baza_haslo.size(); i++){
        cout << '\n' << i << ". ";
        baza_haslo.at(i).wyswietl();
    }
    cout << '\n';

    int nr = -1;
    while(nr < 0 || nr >= baza_haslo.size()){
        cout << "Wybierz numer hasla do usuniecia: ";
        cin >> nr;
        if(nr < 0 || nr >= baza_haslo.size())
            cout << "Wprowadzono numer z poza zakresu\n";
    }

    char choice;
    cout << "Czy na pewno chcesz usunac haslo? \n(zeby zaakceptowac wpisz 't'):";
    cin >> choice;
    if(choice == 't'){
        baza_haslo.erase(baza_haslo.begin()+nr);
        cout << "Usunieto haslo\n";
        zapisz_calosc_do_pliku(filePath,haslo_szyfrujace,baza_haslo);
    }else{
        cout << "Anulowano akcje\n";
    }
}

/**
 * @fn zmienia jedna z wartosci hasla
 */
void edytuj_haslo(const string filePath, const string haslo_szyfrujace, vector<Haslo> &baza_haslo, set<string> &kategorie){
    wyswietl_hasla(baza_haslo);
    cout << "\nWpisz numer hasla, ktore chcesz edytowac: ";
    int nr = -1;
    while( nr < 0 || nr >= baza_haslo.size()){
        cin >> nr;
        if ( nr < 0 || nr >= baza_haslo.size())
            cout << "Wprowadzono numer z poza zakresu\n";
    }
    cin.ignore();
    baza_haslo.at(nr).wyswietl();
    string wybor;
    bool czy_poprawne = false;
    while(!czy_poprawne){
        czy_poprawne = true;
        wybor.clear();

        cout << "\nWpisz co chcesz edytowac: ";
        std::getline(cin,wybor);

        if(wybor == "nazwa"){
            wybor.clear();
            while(wybor.empty()){
                cout << "Wprowadz wartosc: ";
                std::getline(cin, wybor);
                if(wybor.size() == 0)
                    cout << "Nie wprowadzono wartosci\n";
                }
                baza_haslo.at(nr).setNazwa(wybor);
        }else if(wybor == "haslo") {
            wybor.clear();
            while (wybor.empty()) {
                cout << "Wprowadz wartosc (albo wygeneruj haslo 'gen'): ";
                std::getline(cin, wybor);
                if (wybor.empty())
                    cout << "Nie wprowadzono wartosci\n";
                else if( wybor == "gen"){
                    generuj_haslo(wybor);
                    cout << "Czy na pewno chcesz zapisac to haslo? (zatwierdz 'tak')\n";
                    string zatwierdz;
                    std::getline(cin,zatwierdz);
                    if(zatwierdz != "tak")
                        wybor.clear();
                }else if(sprawdz_sile_hasla(wybor,baza_haslo)){
                    cout << "Czy na pewno chcesz zapisac to haslo? (zatwierdz 'tak')\n";
                    string zatwierdz;
                    std::getline(cin,zatwierdz);
                    if(zatwierdz != "tak")
                        wybor.clear();
                }
            }
            baza_haslo.at(nr).setZawartosc(wybor);
        }else if(wybor == "kategoria"){
            wybor.clear();
            while(wybor.empty()){
                cout << "Wprowadz wartosc: ";
                std::getline(cin, wybor);
                if(wybor.size() == 0)
                    cout << "Nie wprowadzono wartosci\n";
            }
            baza_haslo.at(nr).setKategoria(wybor);
            kategorie.insert(wybor);
        }else if(wybor == "serwis"){
            wybor.clear();
            cout << "Wprowadz wartosc: ";
            std::getline(cin, wybor);

            baza_haslo.at(nr).setSerwis(wybor);
        }else if(wybor == "login"){
            wybor.clear();
            cout << "Wprowadz wartosc: ";
            std::getline(cin, wybor);

            baza_haslo.at(nr).setLogin(wybor);
        }else if(wybor == "q" || wybor == "Q"){
            return;
        }else{
            czy_poprawne = false;
            cout << "Wprowadzono niepoprawne dane\n"
            <<"Zeby cofnac wpisz 'q'\n"
              "Sprobuj ponownie:";
        }
    }
    zapisz_calosc_do_pliku(filePath,haslo_szyfrujace,baza_haslo);
}

/**
 *@fn wyswietla hasla, ktore zgadzaja sie z wprowadzona fraza
 */
void wyszukaj_hasla(const vector<Haslo> baza_haslo){
    cout << "Wpisz fragment dowolnej frazy, zeby wyszukac haslo: ";
    string szukane;
    while(szukane.empty()){
        std::getline(cin,szukane);
        for(auto h : baza_haslo){
            if(h.getKategoria().find(szukane) != string::npos || h.getNazwa().find(szukane) != string::npos
            || h.getZawartosc().find(szukane) != string::npos || h.getLogin().find(szukane) != string::npos
            || h.getSerwis().find(szukane) != string::npos)
            {
                h.wyswietl();
            }
        }
        if(szukane.empty()){
            cout << "Nie podano zadnego znaku!\n"
                    "Sproboj ponownie: ";
        }
    }
}

/**
 * @fn sortuje hasla po wybranym elemencie
 */
void posortuj_hasla(const string filePath, const string haslo_szyfrujace, vector<Haslo> &baza_haslo){
    cout << "Wybierz po jakich elementach chcesz sortowac: ";
    string wybor;

    cout << "\nnazwa | haslo | kategoria | serwis | login \n";

    while(wybor.empty()) {
        std::getline(cin, wybor);
        if (wybor == "nazwa") {
            std::sort(baza_haslo.begin(), baza_haslo.end(),[](const Haslo& h1, const Haslo& h2){
                return (h1.getNazwa() < h2.getNazwa());});
        } else if (wybor == "haslo") {
            std::sort(baza_haslo.begin(), baza_haslo.end(), [](const Haslo& h1, const Haslo& h2){
                return (h1.getZawartosc() < h2.getZawartosc());
            });
        } else if (wybor == "kategoria") {
            std::sort(baza_haslo.begin(), baza_haslo.end(), [](const Haslo& h1, const Haslo& h2){
                return (h1.getKategoria() < h2.getKategoria());
            });
        } else if (wybor == "serwis") {
            std::sort(baza_haslo.begin(), baza_haslo.end(), [](const Haslo& h1, const Haslo& h2){
                return (h1.getSerwis() < h2.getSerwis());
            });
        } else if (wybor == "login") {
            std::sort(baza_haslo.begin(), baza_haslo.end(), [](const Haslo& h1, const Haslo& h2){
                return (h1.getLogin() < h2.getLogin());
            });
        } else if (wybor == "q" || wybor == "Q") {
            return;
        } else {
            wybor.clear();
            cout << "Wprowadzono niepoprawne dane\n"
                 << "Zeby cofnac wpisz 'q'\n"
                    "Sprobuj ponownie:";
        }
    }
}

int main() {
    string filePath;
    vector<string> pliki = {
        "/Users/olek/Documents/CV/cv_projects/c++/user1.txt",
        "/Users/olek/Documents/CV/cv_projects/c++/password_manager/user2.txt",
        "/Users/olek/Documents/CV/cv_projects/c++/password_manager/user3.txt"
    };

    string haslo_szyfrujace;
    set<string> baza_kategoria;
    vector<Haslo> baza_haslo;

    cout << "MENEDZER HASEL\n";
    for(int i = 0; i < pliki.size(); i++){
        cout << i << ". " << pliki.at(i) << '\n';
    }
    cout << "Wybierz numer pliku lub podaj pelna sciezke: ";
    while(!filePath.ends_with(".txt") || !std::filesystem::exists(filePath)){
        std::getline(cin, filePath);
        cout << '\n';
        for(int i = 0; i < pliki.size(); i++){
            if(std::to_string(i)==filePath)
                filePath = pliki.at(i);
        }
        if (!filePath.ends_with(".txt") || !std::filesystem::exists(filePath)){
            cout << "sciezka nie istnieje lub nie zawiera pliku tekstowego!\n"
                    "Sproboj ponownie: ";
        }
    }

    if(std::filesystem::file_size(filePath) == 0){
        haslo_szyfrujace = zapisz_nowy_hash(filePath);
    }

    while(!zweryfikuj_hash(filePath, haslo_szyfrujace)){
        cout << "Podaj haslo szyfrujace: ";
        std::getline(cin,haslo_szyfrujace);
        cout << '\n';
        if(!zweryfikuj_hash(filePath, haslo_szyfrujace)){
            cout << "Podano niepoprawne haslo!\n";
        }
    }
    odczyt_z_pliku(filePath, haslo_szyfrujace, baza_haslo, baza_kategoria);
    cout << "Pomyslnie zalogowano!\n";

    string wybor;
    while(true){
        cout << "\n"
                "1. Wyszukaj hasla\n"
                "2. Posortuj hasla\n"
                "3. Dodaj haslo\n"
                "4. Edytuj haslo\n"
                "5. Usun haslo\n"
                "6. Dodaj kategorie\n"
                "7. Usun kategorie\n"
                "8. Wyswietl wszystkie hasla\n"
                "q. Oposc aplikacje\n"
                "Wybierz opcje: \n";
        std::getline(cin, wybor);

        if(wybor == "Wyszukaj hasla" || wybor == std::to_string(1)){
            wyszukaj_hasla(baza_haslo);
        }
        else if(wybor == "Posortuj hasla" || wybor == std::to_string(2)){
            posortuj_hasla(filePath,haslo_szyfrujace,baza_haslo);
        }
        else if(wybor == "Dodaj haslo" || wybor == std::to_string(3)){
            dodaj_haslo(filePath,haslo_szyfrujace,baza_haslo,baza_kategoria);
        }
        else if(wybor == "Edytuj haslo" || wybor == std::to_string(4)){
            edytuj_haslo(filePath,haslo_szyfrujace,baza_haslo,baza_kategoria);
        }
        else if(wybor == "Usun haslo" || wybor == std::to_string(5)){
            usun_haslo(filePath,haslo_szyfrujace,baza_haslo);
        }
        else if(wybor == "Dodaj kategorie" || wybor == std::to_string(6)){
            dodaj_kategorie(baza_kategoria);
        }
        else if(wybor == "Usun kategorie" || wybor == std::to_string(7)){
            usun_kategorie(filePath,haslo_szyfrujace,baza_haslo,baza_kategoria);
        }
        else if(wybor == "Wyswietl wszystkie hasla" || wybor == std::to_string(8)){
            wyswietl_hasla(baza_haslo);
        }
        else if(wybor == "q" || wybor == "Q"){
            zapisz_calosc_do_pliku(filePath,haslo_szyfrujace,baza_haslo);
            return 0;
        }
    }


}
