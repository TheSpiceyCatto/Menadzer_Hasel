#include "main.h"

void Main::readCommands(vector<Password>& hasla, vector<string>& kategorie, const string directory, const string currentKey){
    const string Wyszukaj_Hasla[] = {"WYSZUKAJ HASŁA", "WYSZUKAJ HASłA", "WYSZUKAJ HASLA"};
    const string Posortuj_Hasla[] = {"POSORTUJ HASŁA", "POSORTUJ HASłA", "POSORTUJ HASLA"};
    const string Dodaj_Haslo[] = {"DODAJ HASŁO", "POSORTUJ HASłO", "DODAJ HASLO"};
    const string Edytuj_Haslo[] = {"EDYTUJ HASŁO", "EDYTUJ HASłO", "EDYTUJ HASLO"};
    const string Usun_Haslo[] = {"USUŃ HASŁO", "USUŃ HASłO", "USUŃ HASLO", "USUń HASŁO",  "USUń HASłO", "USUń HASLO", "USUN HASŁO", "USUN HASłO", "USUN HASLO"};
    const string Dodaj_Kategorie = "DODAJ KATEGORIE";
    const string Usun_Kategorie[] = {"USUŃ KATEGORIE", "USUń KATEGORIE", "USUN KATEGORIE"};
    const string Pomoc = "POMOC";
    const string Zamknij = "ZAMKNIJ";
    bool isRunning = true;

    while (isRunning) {
        string command;
        cout << "Podaj komende:" << endl;
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (find(begin(Wyszukaj_Hasla), end(Wyszukaj_Hasla), command) != end(Wyszukaj_Hasla)) {
            Search::Wyszukaj(hasla, kategorie);
        } else if (find(begin(Posortuj_Hasla), end(Posortuj_Hasla), command) != end(Posortuj_Hasla)) {
            cout << "Komenda dostepna tylko w pelnej wersji programu." << endl;
        } else if (find(begin(Dodaj_Haslo), end(Dodaj_Haslo), command) != end(Dodaj_Haslo)) {
            AddPassword::DodajHaslo(hasla, kategorie, directory, currentKey);
        } else if (find(begin(Edytuj_Haslo), end(Edytuj_Haslo), command) != end(Edytuj_Haslo)) {
            cout << "Komenda dostepna tylko w pelnej wersji programu." << endl;
        } else if (find(begin(Usun_Haslo), end(Usun_Haslo), command) != end(Usun_Haslo)) {
            DeletePassword::UsunHaslo(directory, hasla, currentKey);
        } else if (Dodaj_Kategorie.compare(command) == 0) {
            AddCategory::DodajKategorie(kategorie);
        } else if (find(begin(Usun_Kategorie), end(Usun_Kategorie), command) != end(Usun_Kategorie)) {
            Delete::UsunKategorie(directory, hasla, kategorie, currentKey);
        } else if (Pomoc.compare(command) == 0) {
            Functions::helpPage("help.txt");
        } else if (Zamknij.compare(command) == 0) {
            isRunning = false;
        } else {
            cout << "Nie rozpoznano polecenia, napisz \"Pomoc\" by zobaczyc liste komend." << endl;
        }
    }
}


int main() {
    const static string masterKey = "AS!sdDeEeP0908@/kAsHdakdu";
    static string currentKey;

    cout << "Podaj sciezke do pliku:" << endl;
    string directory;
    cin >> directory;
    Functions::openFile(directory, currentKey, masterKey);
    Functions::helpPage("help.txt");

    vector<Password> hasla;
    vector<string> kategorie;

    Functions::readFile(directory, hasla, kategorie, currentKey);

    Main::readCommands(hasla, kategorie, directory, currentKey);
    return 0;
}
