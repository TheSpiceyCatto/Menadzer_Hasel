#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

#ifndef MENADZER_HASEL_KOMENDY_H
#define MENADZER_HASEL_KOMENDY_H
#pragma once


namespace Biblioteka{
    class Polecenia{
    public:
        static auto Pomoc(){
            ifstream helpFile("help.txt");
            string line;
            while(getline(helpFile, line)){
                cout << line << endl;
            }
            helpFile.close();
        }

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
}

#endif //MENADZER_HASEL_KOMENDY_H
