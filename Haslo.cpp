#include <iostream>
using namespace std;

class Haslo{
    string nazwa, szyfr, kategoria;
    string strona, login;

public:
    Haslo(const string &nazwa, const string &szyfr, const string &kategoria) : nazwa(nazwa), szyfr(szyfr), kategoria(kategoria) {}
};