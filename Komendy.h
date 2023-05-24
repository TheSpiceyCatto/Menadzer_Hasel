#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

#ifndef MENADZER_HASEL_KOMENDY_H
#define MENADZER_HASEL_KOMENDY_H
#pragma once
namespace komendy{
    class Polecenia{
    public:
        static auto Wyszukaj(string mess){
            cout << mess << endl;
        }

        static auto Sortuj(){

        }

        static auto DodajHaslo(){

        }

        static auto EdytujHaslo(){

        }

        static auto UsunHaslo(){

        }

        static auto DodajKategorie(){

        }

        static auto UsunKategorie(){

        }

        static auto Pomoc(){
            ifstream helpFile("help.txt");
            string line;
            while(getline(helpFile, line)){
                cout << line << endl;
            }
            helpFile.close();
        }
    };
}

#endif //MENADZER_HASEL_KOMENDY_H
