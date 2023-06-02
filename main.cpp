#include "main.h"

void Main::readCommands(vector<Password>& hasla, vector<string>& kategorie, const string directory, const string currentKey){
//    const string Wyszukaj_Hasla[] = {"WYSZUKAJ HASŁA", "WYSZUKAJ HASłA", "WYSZUKAJ HASLA"};
//    const string Posortuj_Hasla[] = {"POSORTUJ HASŁA", "POSORTUJ HASłA", "POSORTUJ HASLA"};
//    const string Dodaj_Haslo[] = {"DODAJ HASŁO", "POSORTUJ HASłO", "DODAJ HASLO"};
//    const string Edytuj_Haslo[] = {"EDYTUJ HASŁO", "EDYTUJ HASłO", "EDYTUJ HASLO"};
//    const string Usun_Haslo[] = {"USUŃ HASŁO", "USUŃ HASłO", "USUŃ HASLO", "USUń HASŁO",  "USUń HASłO", "USUń HASLO", "USUN HASŁO", "USUN HASłO", "USUN HASLO"};
//    const string Dodaj_Kategorie = "DODAJ KATEGORIE";
//    const string Usun_Kategorie[] = {"USUŃ KATEGORIE", "USUń KATEGORIE", "USUN KATEGORIE"};
//    const string Pomoc = "POMOC";
//    const string Zamknij = "ZAMKNIJ";
    vector<string> commands = { "Wyszukaj Hasla", "Posortuj Hasla", "Dodaj Haslo", "Edytuj Haslo", "Usun Haslo", "Dodaj Kategorie", "Usun Kategorie", "Pomoc", "Zamknij" };
    bool isRunning = true;

    while (isRunning) {
        string command = Functions::chooseFromVector("Wybierz polecenie:", commands, "Niepoprawny wybor polecenia. Wpisz 8 by zobaczyc dostepne komendy.");
        int index = distance(commands.begin(), find(commands.begin(), commands.end(), command));
        switch (index) {
            case 0:
                Search::Wyszukaj(hasla, kategorie);
                break;
            case 1:
                cout << "Komenda dostepna tylko w pelnej wersji programu." << endl;
                break;
            case 2:
                AddPassword::DodajHaslo(hasla, kategorie, directory, currentKey);
                break;
            case 3:
                cout << "Komenda dostepna tylko w pelnej wersji programu." << endl;
                break;
            case 4:
                DeletePassword::UsunHaslo(directory, hasla, currentKey);
                break;
            case 5:
                AddCategory::DodajKategorie(kategorie);
                break;
            case 6:
                Delete::UsunKategorie(directory, hasla, kategorie, currentKey);
                break;
            case 7:
                Functions::helpPage("help.txt");
                break;
            case 8:
                isRunning = false;
                break;
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

    vector<Password> hasla;
    vector<string> kategorie;

    Functions::readFile(directory, hasla, kategorie, currentKey);

    Main::readCommands(hasla, kategorie, directory, currentKey);
    return 0;
}
