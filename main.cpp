#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Krypt_Biblioteka.h"
#include "Haslo.h"
using namespace Biblioteka;
using namespace std;


const static string masterPass = "AS!sdDeEeP0908@/kAsHdakdu";

auto OtworzPlik(fstream& file, string& pass){
    cout << "Podaj sciezke do pliku:" << endl;
    string directory;
    cin >> directory;
    file.open(directory, ios::in | ios::out);
    if(!file){
        file.close();
        file.clear();
        file.open(directory, ios::out);
        cout << "Nie wykryto pliku! Tworze nowy plik." << endl;
        file.close();
        file.clear();
        file.open(directory, ios::in | ios::out);
    }
    string haslo;
    if(file.peek() == fstream::traits_type::eof()){
        cout << "Plik pusty, stwórz hasło:" << endl;
        cin >> haslo;
        file.seekg(0, ios::beg);
        file << Polecenia::Enkrypcja(haslo, masterPass);
    } else {
        cout << "Podaj haslo:" << endl;
        cin >> haslo;
        string correctPass;
        getline(file, correctPass);
        while(Polecenia::Enkrypcja(haslo, masterPass) != correctPass){
            cout << "Haslo niepoprawne, sprobuj ponownie:" << endl;
            cin >> haslo;
        }
    }
    pass = haslo;
    Polecenia::Pomoc();
    cin.clear();
    cin.ignore();
}

bool isRunning = true;

auto CzytajKomendy(string pass){
    const string Wyszukaj_Hasla[] = {"WYSZUKAJ HASŁA", "WYSZUKAJ HASłA", "WYSZUKAJ HASLA"};
    const string Posortuj_Hasla[] = {"POSORTUJ HASŁA", "POSORTUJ HASłA", "POSORTUJ HASLA"};
    const string Dodaj_Haslo[] = {"DODAJ HASŁO", "POSORTUJ HASłO", "DODAJ HASLO"};
    const string Edytuj_Haslo[] = {"EDYTUJ HASŁO", "EDYTUJ HASłO", "EDYTUJ HASLO"};
    const string Usun_Haslo[] = {"USUŃ HASŁO", "USUŃ HASłO", "USUŃ HASLO", "USUń HASŁO",  "USUń HASłO", "USUń HASLO", "USUN HASŁO", "USUN HASłO", "USUN HASLO"};
    const string Dodaj_Kategorie = "DODAJ KATEGORIE";
    const string Usun_Kategorie[] = {"USUŃ KATEGORIE", "USUń KATEGORIE", "USUN KATEGORIE"};
    const string Pomoc = "POMOC";
    const string Zamknij = "ZAMKNIJ";

    string command;
    cout << "Podaj komende:" << endl;
    getline(cin, command);
    transform(command.begin(), command.end(), command.begin(), ::toupper);

    if(find(begin(Wyszukaj_Hasla), end(Wyszukaj_Hasla), command) != end(Wyszukaj_Hasla)) {
        Haslo::Wyszukaj("");
    } else if (find(begin(Posortuj_Hasla), end(Posortuj_Hasla), command) != end(Posortuj_Hasla)) {
        Haslo::Sortuj();
    } else if (find(begin(Dodaj_Haslo), end(Dodaj_Haslo), command) != end(Dodaj_Haslo)) {
        Haslo::DodajHaslo();
    } else if (find(begin(Edytuj_Haslo), end(Edytuj_Haslo), command) != end(Edytuj_Haslo)) {
        Haslo::EdytujHaslo();
    } else if (find(begin(Usun_Haslo), end(Usun_Haslo), command) != end(Usun_Haslo)) {
        Haslo::UsunHaslo();
    } else if (Dodaj_Kategorie.compare(command) ==  0) {
        Haslo::DodajKategorie();
    } else if (find(begin(Usun_Kategorie), end(Usun_Kategorie), command) != end(Usun_Kategorie)) {
        Haslo::UsunKategorie();
    } else if (Pomoc.compare(command) ==  0) {
        Polecenia::Pomoc();
    } else if (Zamknij.compare(command) == 0){
        isRunning = false;
    } else {
        cout << "Nie rozpoznano Biblioteka, napisz \"Pomoc\" by zobaczyc liste komend." << endl;
    }
}

auto main() -> int {
    fstream currentFile;
    string currentPass;
    OtworzPlik(currentFile, currentPass);

    while (isRunning){
        CzytajKomendy(currentPass);
    }
    currentFile.close();
    return 0;
}
