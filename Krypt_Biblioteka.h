#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include "Haslo.h"
using namespace std;

namespace Biblioteka{
    class Functions{
    public:
        static auto encryption(string haslo, string key){
            string result;
            int keyPos = 0;
            stringstream strStream;
            for(string::iterator it = haslo.begin(); it != haslo.end(); ++it){
                char shift = key[keyPos % key.length()];
                int character = *it + shift;
                strStream << hex << character;
                keyPos++;
            }
            return strStream.str();
        }

        static auto decryption(string haslo, string key){
            string result = "";
            int keyPos = 0;
            for(int i = 0; i < haslo.length(); i+=2){
                char shift = key[keyPos % key.length()];
                string hexVal = string() + haslo[i] + haslo[i + 1];
                result += char(stoi(hexVal, nullptr, 16) - shift);
                keyPos++;
            }
            return result;
        }

        static void filterHaslaByGetter(vector<Haslo> hasla, vector<Haslo>& buffHasla, const string& input, const string& (Haslo::*getter)() const) {
            vector<Haslo>& targetVector = (buffHasla.empty() ? hasla : buffHasla);
            vector<Haslo> filteredHasla;

            for (const auto& haslo : targetVector) {
                if ((haslo.*getter)().find(input) == 0) {
                    filteredHasla.push_back(haslo);
                }
            }
            buffHasla = move(filteredHasla);
        }


        static void Sortuj() {}

        static void EdytujHaslo() {}

        static void UsunHaslo() {}

        static void DodajKategorie(vector<string>& kategorie) {
            string kategoria;
            cout << "Podaj nowa kategorie:" << endl;
            cin >> kategoria;
            bool isValid;
            do {
                isValid = true;
                for (auto it = kategorie.begin(); it != kategorie.end(); ++it) {
                    if (it->compare(kategoria) == 0){
                        isValid = false;
                        cout << "Kategoria juz istnieje, sprobuj ponownie:" << endl;
                        cin >> kategoria;
                    }
                }
            } while (!isValid);
            kategorie.push_back(kategoria);
            cout << "Kategoria dodana" << endl;
            cin.clear();
            cin.ignore();
        }

        static void UsunKategorie(string directory, vector<Haslo>& hasla, vector<string>& kategorie, string key) {
            fstream file(directory);
            string choice = Functions::chooseCategory(kategorie);
            kategorie.erase(find(kategorie.begin(), kategorie.end(), choice));
            file.clear();
            file.seekg(0, ios::beg);
            vector<string> lines;
            string line;
            while (getline(file, line)){
                string decryptedLine = decryption(line, key);
                if (decryptedLine.find("Kategoria: " + choice) == string::npos){
                    lines.push_back(line);
                }
            }

            file.clear();
            file.close();
            file.open("a", std::ofstream::out | std::ofstream::trunc);
            file.close();
            file.open("a", ios::in | ios::out);
            for (auto e : lines) {
                file << e << endl;
            }
            hasla.erase(remove_if(hasla.begin(), hasla.end(), [choice](Haslo e) {return e.getKategoria().compare(choice) == 0;}), hasla.end());
            cin.clear();
            cin.ignore();
        }
        static void DodajHaslo(vector<Haslo>& hasla, vector<string>& kategorie, string directory, string key){
            if(!kategorie.empty()){
                string buffNazwa, buffHaslo, buffKategoria, buffStrona, buffLogin;

                cout << "Podaj nazwe hasla:" << endl;
                getline(cin, buffNazwa);
                while(cin.fail() || buffNazwa.empty()){
                    cout << "Nie podano nazwy, sprobuj ponownie:" << endl;
                    getline(cin, buffNazwa);
                }

                cout << "Podaj login (zostaw puste by pominac):" << endl;
                getline(cin, buffLogin);

                do {
                    string input;
                    cout << "Czy wygenerowac haslo? Y/n" << endl;
                    getline(cin, input);
                    if (toupper(input[0]) == 'N') {
                        cout << "Podaj haslo:" << endl;
                        getline(cin, buffHaslo);
                        bool gotPass = false;
                        while (!gotPass) {
                            bool exists = false;
                            for (auto haslo : hasla) {
                                if (haslo.getHaslo().compare(buffHaslo) == 0){
                                    exists = true;
                                    break;
                                }
                            }
                            if(cin.fail() || buffHaslo.empty()){
                                cout << "Nie podano hasla, sprobuj ponownie:" << endl;
                                getline(cin, buffHaslo);
                            } else if (exists){
                                cout << "Haslo juz istnieje! Sprobuj ponownie:" << endl;
                                getline(cin, buffHaslo);
                            } else {
                                gotPass = true;
                            }
                        }
                        cout << "Haslo jest " + Functions::evaluatePassword(buffHaslo) << endl;
                    } else if (toupper(input[0]) == 'Y' || input[0] == '\0') {
                        buffHaslo = Functions::generatePassword();
                    } else {
                        cout << "Nie rozpoznano odpowiedzi" << endl;
                    }
                } while (buffHaslo.empty());

                cout << "Podaj strone WWW (zostaw puste by pominac):" << endl;
                getline(cin, buffStrona);

                buffKategoria = Functions::chooseCategory(kategorie);

                Haslo haslo(buffNazwa, buffHaslo, buffKategoria);
                if(!buffStrona.empty()){
                    haslo.setStrona(buffStrona);
                }
                if(!buffLogin.empty()){
                    haslo.setLogin(buffLogin);
                }

                hasla.push_back(haslo);
                writePassword(directory, haslo, key);

                cin.clear();
                cin.ignore();
            } else {
                cout << "Brak kategorii, sprobuj \"Pomoc\" lub \"Dodaj Kategorie\"" << endl;
            }
        }
        static void readFile(string directory, vector<Haslo>& hasla, vector<string>& kategorie, string key){
            fstream file;
            file.open(directory, ios::in | ios::out);
            string nazwa, login, haslo, kategoria, strona;
            int startPos, endPos;
            string line;
            getline(file, line);
            while(getline(file, line)) {
                if (!line.empty()){
                    line = decryption(line, key);

                    bool hasLogin = line.find("; Login:") != string::npos;
                    bool hasSite = line.find("; Strona:") != string::npos;

                    startPos = line.find("Nazwa: ") + 7;
                    endPos = hasLogin ? line.find("; Login:") : line.find("; Haslo:");
                    nazwa = line.substr(startPos, endPos - startPos);

                    if (hasLogin){
                        startPos = line.find("Login: ") + 7;
                        endPos = line.find("; Haslo:");
                        login = line.substr(startPos, endPos - startPos);
                    }

                    startPos = line.find("Haslo: ") + 7;
                    endPos = line.find("; Kategoria:");
                    haslo = line.substr(startPos, endPos - startPos);

                    startPos = line.find("Kategoria: ") + 11;
                    endPos = hasSite ? line.find("; Strona:") : line.rfind(";");
                    kategoria = line.substr(startPos, endPos - startPos);

                    if (hasSite){
                        startPos = line.find("Strona: ") + 8;
                        endPos = line.rfind(";");
                        strona = line.substr(startPos, endPos - startPos);
                    }

                    Haslo newHaslo(nazwa, haslo, kategoria);
                    if (hasLogin)
                        newHaslo.setLogin(login);
                    if (hasSite)
                        newHaslo.setStrona(strona);
                    hasla.push_back(newHaslo);

                    if (!(find(kategorie.begin(), kategorie.end(), kategoria) != kategorie.end())) {
                        kategorie.push_back(kategoria);
                    }
                }
            }
            file.close();
        }

        static void Wyszukaj(vector<Haslo> hasla, vector<string>& kategorie) {
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
                            cout << haslo.outputInfo() << endl;
                        }
                        return;
                    } else {
                        reading = false;
                    }
                }
                vector<Haslo> buffHasla;
                string input2;
                for (auto it = input.begin(); it != input.end(); ++it) {
                    switch (*it) {
                        case 'N':
                            cout << "Podaj nazwe:" << endl;
                            getline(cin, input2);
                            filterHaslaByGetter(hasla, buffHasla, input2, &Haslo::getNazwa);
                            break;
                        case 'H':
                            cout << "Podaj haslo:" << endl;
                            getline(cin, input2);
                            filterHaslaByGetter(hasla, buffHasla, input2, &Haslo::getHaslo);
                            break;
                        case 'K':
                            input2 = Functions::chooseCategory(kategorie);
                            filterHaslaByGetter(hasla, buffHasla, input2, &Haslo::getKategoria);
                            break;
                        case 'S':
                            cout << "Podaj strone:" << endl;
                            getline(cin, input2);
                            filterHaslaByGetter(hasla, buffHasla, input2, &Haslo::getStrona);
                            break;
                        case 'L':
                            cout << "Podaj login:" << endl;
                            getline(cin, input2);
                            filterHaslaByGetter(hasla, buffHasla, input2, &Haslo::getLogin);
                            break;
                    }
                }
                if(!buffHasla.empty()){
                    for (auto haslo : buffHasla) {
                        cout << haslo.outputInfo();
                    }
                } else {
                    cout << "Nie znaleziono." << endl;
                }
            } else {
                cout << "Brak hasel!" << endl;
            }
        }

        static void writePassword(string directory, Haslo& haslo, string& key){
            fstream file(directory);
            file.seekp(0, ios::end);
            file << endl << encryption(haslo.outputInfo(), key);
            file.close();
        }


        static void OpenFile(string directory, string& currentKey, const string& masterKey){
            fstream file;
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
                file << Functions::encryption(haslo, masterKey);
            } else {
                cout << "Podaj haslo:" << endl;
                cin >> haslo;
                string correctPass;
                getline(file, correctPass);
                while(Functions::encryption(haslo, masterKey) != correctPass){
                    cout << "Haslo niepoprawne, sprobuj ponownie:" << endl;
                    cin >> haslo;
                }
            }
            currentKey = haslo;
            file.close();
            cin.clear();
            cin.ignore();
        }


        static string chooseCategory(vector<string>& kategorie){
            cout << "Wybierz kategorie (podaj numer):" << endl;
            for(int i = 0; i < kategorie.size(); i++){
                cout << i+1 << ". " << kategorie[i] << endl;
            }
            int choice;
            bool correctChoice = false;
            while (!correctChoice){
                cin >> choice;
                if(choice > 0 && choice <= kategorie.size()){
                    correctChoice = true;
                } else {
                    cout << "Niepoprawny wybor kategorii." << endl;
                }
            }
            return kategorie.at(choice-1);
        }

        static string evaluatePassword(string haslo){
            int score = haslo.size();
            bool lower = false, upper = false, special = false;
            for (auto it = haslo.begin(); it != haslo.end(); ++it) {
                int val = (int)*it;
                if (islower(val))
                    lower = true;
                if (isupper(val))
                    upper = true;
                if ((val >= 33 && val <= 47) || (val >= 60 && val <= 64) || (val >= 91 && val <= 96) || (val >= 123 && val <= 126))
                    special = true;
            }
            if (lower && upper)
                score += 3;
            if (special)
                score += 2;
            if (score < 10){
                return "slabe";
            } else if (score < 15){
                return "dobre";
            } else if (score < 20){
                return "bardzo dobre";
            } else if (score < 30){
                return "bardzo, ale to bardzo dobre";
            }
        }

        static string generatePassword(){
            int charNum;
            bool upLow, special, numbers;
            string input;

            cout << "Podaj ilosc znakow:" << endl;
            getline(cin, input);
            while(cin.fail() || input.empty() || !isNumber(input) || (isNumber(input) && stoi(input) <= 0)){
                cout << "Niepoprawna odpowiedz, sprobuj ponownie:" << endl;
                getline(cin, input);
            }
            charNum = stoi(input);

            Boolean_Question("Czy uzywac wielkich i malych liter? Y/n", upLow);
            Boolean_Question("Czy uzywac liczb? Y/n", numbers);
            Boolean_Question("Czy uzywac znakow specjalnych? Y/n", special);

            int choiceMin = numbers ? 1 : 2;
            int choiceMax = special ? 3 : 2;
            string result;
            for (int i = 0; i < charNum; ++i) {
                int randChoice = getRandomNumber(choiceMin, choiceMax);
                if (randChoice == 1) {
                    result += (char)getRandomNumber(48, 57);
                } else if (randChoice == 2) {
                    if(upLow && getRandomNumber(0, 1) == 1){
                        result += (char)getRandomNumber(65, 90);
                    } else {
                        result += (char) getRandomNumber(97, 122);
                    }
                } else if (randChoice == 3) {
                    string specialChars = "!\"#$%&'()*+,-./:<=>?@[\\]^_`{|}~";
                    int randomIndex = getRandomNumber(0, specialChars.length() - 1);
                    result += specialChars[randomIndex];
                }
            }
            return result;
        }
        static void Boolean_Question(const string mess, bool& result){
            bool answered = false;
            string input;
            do{
                cout << mess << endl;
                getline(cin, input);
                if (toupper(input[0]) == 'N') {
                    result = false;
                    answered = true;
                } else if (toupper(input[0]) == 'Y' || input[0] == '\0') {
                    result = true;
                    answered = true;
                } else {
                    cout << "Nie rozpoznano odpowiedzi" << endl;
                }
            } while (!answered);
        }

        static bool isNumber(string& str) {
            try {
                size_t pos = 0;
                stoi(str, &pos);
                return pos == str.length();
            } catch (const exception&) {
                return false;
            }
        }

        static int getRandomNumber(int min, int max) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distribution(min, max);
            return distribution(gen);
        }

        static void helpPage(string dir){
            ifstream helpFile(dir);
            string line;
            while(getline(helpFile, line)){
                cout << line << endl;
            }
            helpFile.close();
        }
        static bool ReadCommands(vector<Haslo>& hasla, vector<string>& kategorie, string directory, const string currentKey){
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
                Wyszukaj(hasla, kategorie);
            } else if (find(begin(Posortuj_Hasla), end(Posortuj_Hasla), command) != end(Posortuj_Hasla)) {
                Sortuj();
            } else if (find(begin(Dodaj_Haslo), end(Dodaj_Haslo), command) != end(Dodaj_Haslo)) {
                DodajHaslo(hasla, kategorie, directory, currentKey);
            } else if (find(begin(Edytuj_Haslo), end(Edytuj_Haslo), command) != end(Edytuj_Haslo)) {
                EdytujHaslo();
            } else if (find(begin(Usun_Haslo), end(Usun_Haslo), command) != end(Usun_Haslo)) {
                UsunHaslo();
            } else if (Dodaj_Kategorie.compare(command) ==  0) {
                DodajKategorie(kategorie);
            } else if (find(begin(Usun_Kategorie), end(Usun_Kategorie), command) != end(Usun_Kategorie)) {
                UsunKategorie(directory, hasla, kategorie, currentKey);
            } else if (Pomoc.compare(command) ==  0) {
                helpPage("help.txt");
            } else if (Zamknij.compare(command) == 0){
                return false;
            } else {
                cout << "Nie rozpoznano polecenia, napisz \"Pomoc\" by zobaczyc liste komend." << endl;
            }
        }
    };
}