#include "Search.h"

void Search::Wyszukaj(vector<Password> hasla, vector<string>& kategorie) {
    if(!hasla.empty()){
        string input;
        cout << "Podaj parametry wyszukiwania (zostaw puste by wyswietlic wszystko, wpisz \"Pomoc\" by zobaczyc wiecej):" << endl;
        bool reading = true;
        while (reading){
            getline(cin, input);
            transform(input.begin(), input.end(), input.begin(), ::toupper);
            if (input.compare("POMOC") == 0){
                Functions::helpPage("parameters.txt");
            } else if (cin.fail() || input.empty()){
                for (auto haslo : hasla) {
                    cout << haslo << endl;
                }
                return;
            } else {
                reading = false;
            }
        }
        vector<Password> buffHasla;
        string input2;
        for (auto it = input.begin(); it != input.end(); ++it) {
            switch (*it) {
                case 'N':
                    cout << "Podaj nazwe:" << endl;
                    getline(cin, input2);
                    filterPasswordsByGetter(hasla, buffHasla, input2, &Password::getNazwa);
                    break;
                case 'H':
                    cout << "Podaj haslo:" << endl;
                    getline(cin, input2);
                    filterPasswordsByGetter(hasla, buffHasla, input2, &Password::getHaslo);
                    break;
                case 'K':
                    input2 = Functions::chooseFromVector("Wybierz kategorie (podaj numer):", kategorie, "Niepoprawny wybor kategorii.");
                    filterPasswordsByGetter(hasla, buffHasla, input2, &Password::getKategoria);
                    break;
                case 'S':
                    cout << "Podaj strone:" << endl;
                    getline(cin, input2);
                    filterPasswordsByGetter(hasla, buffHasla, input2, &Password::getStrona);
                    break;
                case 'L':
                    cout << "Podaj login:" << endl;
                    getline(cin, input2);
                    filterPasswordsByGetter(hasla, buffHasla, input2, &Password::getLogin);
                    break;
            }
        }
        if(!buffHasla.empty()){
            for (auto haslo : buffHasla) {
                cout << haslo;
            }
        } else {
            cout << "Nie znaleziono." << endl;
        }
    } else {
        cout << "Brak hasel!" << endl;
    }
}

void Search::filterPasswordsByGetter(vector<Password> hasla, vector<Password>& buffHasla, const string& input, const string& (Password::*getter)() const) {
    vector<Password>& targetVector = (buffHasla.empty() ? hasla : buffHasla);
    vector<Password> filteredHasla;

    for (const auto& haslo : targetVector) {
        if ((haslo.*getter)().find(input) == 0) {
            filteredHasla.push_back(haslo);
        }
    }
    buffHasla = move(filteredHasla);
}
