#include "Password.h"

Password::Password(string nazwa, string haslo, string kategoria) : nazwa(nazwa), haslo(haslo), kategoria(kategoria) {}

ostream& operator<<(ostream& os, const Password& haslo){
    os << "Nazwa: " << haslo.getNazwa() << "; ";
    if(!haslo.getLogin().empty())
        os << "Login: " << haslo.getLogin() << "; ";
    os << "Haslo: " << haslo.getHaslo() << "; ";
    os << "Kategoria: " << haslo.getKategoria() << (haslo.getStrona().empty() ? ";" : "; ");
    if(!haslo.getStrona().empty())
        os << "Strona: " << haslo.getStrona() << ";";
    return os;
}

string Password::toString(){
    string res;
    res += "Nazwa: " + getNazwa() + "; ";
    if(!getLogin().empty())
        res += "Login: " + getLogin() + "; ";
    res += "Haslo: " + getHaslo() + "; ";
    res += "Kategoria: " + getKategoria() + (getStrona().empty() ? ";" : "; ");
    if(!getStrona().empty())
        res += "Strona: " + getStrona() + ";";
    return res;
}

const string& Password::getNazwa() const {
    return nazwa;
}
void Password::setNazwa(const string &nazwa) {
    Password::nazwa = nazwa;
}
const string& Password::getHaslo() const {
    return haslo;
}
void Password::setHaslo(const string &szyfr) {
    Password::haslo = szyfr;
}
const string& Password::getKategoria() const {
    return kategoria;
}
void Password::setKategoria(const string &kategoria) {
    Password::kategoria = kategoria;
}
const string& Password::getStrona() const {
    return strona;
}
void Password::setStrona(const string &strona) {
    this->strona = strona;
}
const string& Password::getLogin() const {
    return login;
}
void Password::setLogin(const string &login) {
    this->login = login;
}
