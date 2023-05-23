#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

const auto HelpPage(){
    ifstream helpFile("help.txt");
    string line;
    while(getline(helpFile, line)){
        cout << line << endl;
    }
    helpFile.close();
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
        cout << "Jest" << endl;
    } else if (find(begin(Posortuj_Hasla), end(Posortuj_Hasla), command) != end(Posortuj_Hasla)) {
        cout << "Sort" << endl;
    } else if (find(begin(Dodaj_Haslo), end(Dodaj_Haslo), command) != end(Dodaj_Haslo)) {
        cout << "Dod" << endl;
    } else if (find(begin(Edytuj_Haslo), end(Edytuj_Haslo), command) != end(Edytuj_Haslo)) {
        cout << "Edit" << endl;
    } else if (find(begin(Usun_Haslo), end(Usun_Haslo), command) != end(Usun_Haslo)) {
        cout << "Usun" << endl;
    } else if (Dodaj_Kategorie.compare(command) ==  0) {
        cout << "DodK" << endl;
    } else if (find(begin(Usun_Kategorie), end(Usun_Kategorie), command) != end(Usun_Kategorie)) {
        cout << "UsunK" << endl;
    } else if (Pomoc.compare(command) ==  0) {
        HelpPage();
    } else if (Zamknij.compare(command) == 0){
        isRunning = false;
    } else {
        cout << "Nie rozpoznano komendy, napisz \"Pomoc\" by zobaczyć listę komend." << endl;
    }
}

auto main() -> int {
    HelpPage();
    string command;
    while (isRunning){
        cout << "Podaj komendę:" << endl;
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::toupper);
        ReadCommand(command);
    }
    return 0;
}
