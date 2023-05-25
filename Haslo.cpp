#include "Haslo.h"
#include <iostream>
using namespace std;

static vector<Haslo> hasla;
static vector<string> kategorie;

string nazwa, szyfr, kategoria;
string strona, login;

Haslo::Haslo(string nazwa, string szyfr, string kategoria) : nazwa(nazwa), szyfr(szyfr),
                                                                                  kategoria(kategoria) {}

void Haslo::Wyszukaj(string mess) {
    cout << mess << endl;
}

void Haslo::Sortuj() {}

void Haslo::EdytujHaslo() {}

void Haslo::UsunHaslo() {}

void Haslo::DodajKategorie() {}

void Haslo::UsunKategorie() {}

void Haslo::DodajHaslo(){
    string buffNazwa, buffSzyfr, buffKategoria, buffStrona, buffLogin;
    cout << "Podaj nazwe hasla:" << endl;
    cin >> buffNazwa;
    cout << "Podaj login (zostaw puste by pominac):" << endl;
    cin >> buffLogin;
    cout << "Podaj haslo:" << endl;
    cin >> buffSzyfr;
    cout << "Podaj strone WWW (zostaw puste by pominac):" << endl;
    cin >> buffStrona;
    buffKategoria = WybierzKategorie();
    Haslo haslo(buffNazwa, buffSzyfr, buffKategoria);
    if(!buffStrona.empty()){
        haslo.setStrona(buffStrona);
    }
    if(!buffLogin.empty()){
        haslo.setLogin(buffLogin);
    }
}

string Haslo::WybierzKategorie(){
    cout << "Wybierz kategorie (podaj numer):" << endl;
    for(int i = 0; i < kategorie.size(); i++){
        cout << i+1 << ". " << kategorie[i] << endl;
    }
    int choice;
    bool correctChoice = false;
    while (!correctChoice){
        cin >> choice;
        if(choice >= 0 && choice < kategorie.size()){
            correctChoice = true;
        } else {
            cout << "Nie poprawny wybor kategori." << endl;
        }
    }
    return kategorie.at(choice);
}
