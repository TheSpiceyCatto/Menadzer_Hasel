#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
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

                cout << "Podaj haslo:" << endl;
                getline(cin, buffHaslo);
                while(cin.fail() || buffHaslo.empty()){
                    cout << "Nie podano hasla, sprobuj ponownie:" << endl;
                    getline(cin, buffHaslo);
                }

                cout << "Podaj strone WWW (zostaw puste by pominac):" << endl;
                getline(cin, buffStrona);

                buffKategoria = WybierzKategorie(kategorie);

                Haslo haslo(buffNazwa, Kryptografia::Enkrypcja(buffHaslo, key), buffKategoria);

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

        static string WybierzKategorie(vector<string>& kategorie){
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
                    cout << "Nie poprawny wybor kategorii." << endl;
                }
            }
            return kategorie.at(choice-1);
        }
    };
}

#endif //MENADZER_HASEL_KOMENDY_H
