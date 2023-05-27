#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
using namespace std;

#ifndef MENADZER_HASEL_KOMENDY_H
#define MENADZER_HASEL_KOMENDY_H
#pragma once


namespace Biblioteka{
    class Kryptografia{
    public:
        static auto Enkrypcja(string haslo, string key){
            string result = "";
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

        static auto Dekrypcja(string haslo, string key){
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
    };
    class Haslo {
        string nazwa, szyfr, kategoria;
        string strona, login;

        Haslo(string nazwa, string szyfr, string kategoria) : nazwa(nazwa), szyfr(szyfr), kategoria(kategoria) {}

    public:
        void setStrona(const string &strona) {
            this->strona = strona;
        }

        void setLogin(const string &login) {
            this->login = login;
        }

        static void Wyszukaj(string mess) {
            cout << mess << endl;
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

        static void UsunKategorie() {}

        static void DodajHaslo(vector<Haslo>& hasla, vector<string>& kategorie, string key){
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
                        while (cin.fail() || buffHaslo.empty()) {
                            cout << "Nie podano hasla, sprobuj ponownie:" << endl;
                            getline(cin, buffHaslo);
                        }
                    } else if (toupper(input[0]) == 'Y' || input[0] == '\0') {
                        buffHaslo = GeneratePassword();
                    } else {
                        cout << "Nie rozpoznano odpowiedzi" << endl;
                    }
                } while (buffHaslo.empty());

                cout << "Podaj strone WWW (zostaw puste by pominac):" << endl;
                getline(cin, buffStrona);

                buffKategoria = ChooseCategory(kategorie);

                Haslo haslo(buffNazwa, buffHaslo, buffKategoria);

                if(!buffStrona.empty()){
                    haslo.setStrona(buffStrona);
                }
                if(!buffLogin.empty()){
                    haslo.setLogin(buffLogin);
                }
                hasla.push_back(haslo);
                cin.clear();
                cin.ignore();
            } else {
                cout << "Brak kategorii, sprobuj \"Pomoc\" lub \"Dodaj Kategorie\"" << endl;
            }
        }

    //private:
        static string ChooseCategory(vector<string>& kategorie){
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

        static string GeneratePassword(){
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

            int letterMax = upLow ? 1 : 0;
            int choiceMin = numbers ? 1 : 2;
            int choiceMax = special ? 3 : 2;
            string result;
            for (int i = 0; i < charNum; ++i) {
                int randChoice = getRandomNumber(choiceMin, choiceMax);
                switch (randChoice) {
                    case 1:
                        //liczby
                        result += (char) getRandomNumber(48, 57);
                        break;
                    case 2:
                        //litery
                        if(getRandomNumber(0, letterMax) == 1){
                            result += (char)getRandomNumber(65, 90);
                        } else {
                            result += (char) getRandomNumber(97, 122);
                        }
                        break;
                    case 3:
                        //znaki specjalne
                        int specialChoice = getRandomNumber(1, 4);
                        switch (specialChoice) {
                            case 1:
                                result += (char)getRandomNumber(33, 47);
                                break;
                            case 2:
                                result += (char) getRandomNumber(58, 64);
                                break;
                            case 3:
                                result += (char) getRandomNumber(91, 96);
                                break;
                            case 4:
                                result += (char) getRandomNumber(123, 126);
                                break;
                        }
                        break;
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
    };
}

#endif //MENADZER_HASEL_KOMENDY_H
