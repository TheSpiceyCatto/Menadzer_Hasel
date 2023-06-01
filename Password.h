#ifndef MENADZER_HASEL_PASSWORD_H
#define MENADZER_HASEL_PASSWORD_H
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include <sstream>
using namespace std;

class Password {
private:
    string nazwa, haslo, kategoria;
    string strona, login;

public:
    Password(string nazwa, string haslo, string kategoria);

    /**
     * Zwraca informacje o haśle.
     * @return Informacje o haśle.
     */
    string toString();

    const string& getNazwa() const;
    void setNazwa(const string &nazwa);
    const string& getHaslo() const;
    void setHaslo(const string &szyfr);
    const string& getKategoria() const;
    void setKategoria(const string &kategoria);
    const string& getStrona() const;
    void setStrona(const string &strona);
    const string& getLogin() const;
    void setLogin(const string &login);
    friend ostream& operator<<(ostream& os, const Password& haslo);
};
#endif