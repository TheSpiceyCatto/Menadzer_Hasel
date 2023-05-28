#ifndef HASLO_H
#define HASLO_H
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include "Krypt_Biblioteka.h"
using namespace Biblioteka;
using namespace std;

class Haslo {
private:
    string nazwa, haslo, kategoria;
    string strona, login;

public:
    Haslo(string nazwa, string szyfr, string kategoria) : nazwa(nazwa), haslo(szyfr), kategoria(kategoria) {}

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
            string decryptedLine = Functions::decryption(line, key);
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
                line = Functions::decryption(line, key);

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

private:
    static void writePassword(string directory, Haslo& haslo, string& key){
        fstream file(directory);
        file.seekp(0, ios::end);
        file << endl << Functions::encryption(haslo.outputInfo(), key);
        file.close();
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

    string outputInfo(){
        string result;
        result += "Nazwa: " + getNazwa() + "; ";
        if(!getLogin().empty())
            result += "Login: " + getLogin() + "; ";
        result += "Haslo: " + getHaslo() + "; ";
        result += "Kategoria: " + getKategoria() + (getStrona().empty() ? ";" : "; ");
        if(!getStrona().empty())
            result += "Strona: " + getStrona() + ";";
        return result;
    }
public:
    const string& getNazwa() const {
        return nazwa;
    }
    void setNazwa(const string &nazwa) {
        Haslo::nazwa = nazwa;
    }
    const string &getHaslo() const {
        return haslo;
    }
    void setHaslo(const string &szyfr) {
        Haslo::haslo = szyfr;
    }
    const string &getKategoria() const {
        return kategoria;
    }
    void setKategoria(const string &kategoria) {
        Haslo::kategoria = kategoria;
    }
    const string &getStrona() const {
        return strona;
    }
    void setStrona(const string &strona) {
        this->strona = strona;
    }
    const string &getLogin() const {
        return login;
    }
    void setLogin(const string &login) {
        this->login = login;
    }
};

#endif // HASLO_H
