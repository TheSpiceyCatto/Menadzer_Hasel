#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Komendy.h"
using namespace komendy;
using namespace std;

auto OpenFile(fstream& file){
    cout << "Podaj sciezke do pliku:" << endl;
    string directory;
    cin >> directory;
    file.open(directory, fstream::in | fstream::out);
    if(!file){
        file.close();
        file.open(directory, fstream::out);
        cout << "Nie wykryto pliku! Tworze nowy plik." << endl;
        file.close();
        file.open(directory, fstream::in | fstream::out);
    }
    Polecenia::Pomoc();
    cin.clear();
    cin.ignore();
}

bool isRunning = true;

auto ReadCommand(string command){
    const string Wyszukaj_Hasla[] = {"WYSZUKAJ HASŁA", "WYSZUKAJ HASłA", "WYSZUKAJ HASLA"};
    const string Posortuj_Hasla[] = {"POSORTUJ HASŁA", "POSORTUJ HASłA", "POSORTUJ HASLA"};
    const string Dodaj_Haslo[] = {"DODAJ HASŁO", "POSORTUJ HASłO", "DODAJ HASLO"};
    const string Edytuj_Haslo[] = {"EDYTUJ HASŁO", "EDYTUJ HASłO", "EDYTUJ HASLO"};
    const string Usun_Haslo[] = {"USUŃ HASŁO", "USUŃ HASłO", "USUŃ HASLO", "USUń HASŁO",  "USUń HASłO", "USUń HASLO", "USUN HASŁO", "USUN HASłO", "USUN HASLO"};
    const string Dodaj_Kategorie = "DODAJ KATEGORIE";
    const string Usun_Kategorie[] = {"USUŃ KATEGORIE", "USUń KATEGORIE", "USUN KATEGORIE"};
    const string Pomoc = "POMOC";
    const string Zamknij = "ZAMKNIJ";
    if(find(begin(Wyszukaj_Hasla), end(Wyszukaj_Hasla), command) != end(Wyszukaj_Hasla)) {
        Polecenia::Wyszukaj("SZUKAM");
    } else if (find(begin(Posortuj_Hasla), end(Posortuj_Hasla), command) != end(Posortuj_Hasla)) {
        Polecenia::Sortuj();
    } else if (find(begin(Dodaj_Haslo), end(Dodaj_Haslo), command) != end(Dodaj_Haslo)) {
        Polecenia::DodajHaslo();
    } else if (find(begin(Edytuj_Haslo), end(Edytuj_Haslo), command) != end(Edytuj_Haslo)) {
        Polecenia::EdytujHaslo();
    } else if (find(begin(Usun_Haslo), end(Usun_Haslo), command) != end(Usun_Haslo)) {
        Polecenia::UsunHaslo();
    } else if (Dodaj_Kategorie.compare(command) ==  0) {
        Polecenia::DodajKategorie();
    } else if (find(begin(Usun_Kategorie), end(Usun_Kategorie), command) != end(Usun_Kategorie)) {
        Polecenia::UsunKategorie();
    } else if (Pomoc.compare(command) ==  0) {
        Polecenia::Pomoc();
    } else if (Zamknij.compare(command) == 0){
        isRunning = false;
    } else {
        cout << "Nie rozpoznano komendy, napisz \"Pomoc\" by zobaczyc liste komend." << endl;
    }
}

auto main() -> int {
    fstream currentFile;
    OpenFile(currentFile);

    string command;
    while (isRunning){
        cout << "Podaj komende:" << endl;
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::toupper);
        ReadCommand(command);
    }

    currentFile.close();
    return 0;
}
