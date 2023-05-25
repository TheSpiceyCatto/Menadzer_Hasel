#ifndef HASLO_H
#define HASLO_H
#include <vector>
#include <string>
using namespace std;

class Haslo {
private:
    static vector<Haslo> hasla;
    static vector<string> kategorie;

    string nazwa, szyfr, kategoria;
    string strona, login;

public:
    Haslo(string nazwa, string szyfr, string kategoria);

    static void Wyszukaj(string mess);
    static void Sortuj();
    static void EdytujHaslo();
    static void UsunHaslo();
    static void DodajKategorie();
    static void UsunKategorie();
    static void DodajHaslo();
    static string WybierzKategorie();

    void setStrona(const string &strona) {
        this->strona = strona;
    }

    void setLogin(const string &login) {
        this->login = login;
    }
};

#endif // HASLO_H
