#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
using namespace std;

class Haslo {
private:
    string nazwa, haslo, kategoria;
    string strona, login;

public:
    Haslo(string nazwa, string szyfr, string kategoria) : nazwa(nazwa), haslo(szyfr), kategoria(kategoria) {}

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