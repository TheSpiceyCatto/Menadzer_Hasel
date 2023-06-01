#ifndef MENADZER_HASEL_SEARCH_H
#define MENADZER_HASEL_SEARCH_H
#include <iostream>
#include "../FunctionLibrary.h"
using namespace std;

namespace Search{
    /**
     * Wyszukuje hasła na podstawie parametrów podanych przez użytkownika.
     * @param hasla Vector z aktualnymi hasłami.
     * @param kategorie Vector z kategoriami po których można szukać hasła.
     */
    void Wyszukaj(vector<Password> hasla, vector<string>& kategorie);

    /**
     * Zapisuje do tymczasowego vectora hasła, które pasują do wyszukiwanej frazy w odpowiednim parametrze haseł.
     * @param hasla Vector z aktualnymi hasłami.
     * @param buffHasla Referencja do tymczasowego vectora z przefiltrowanymi hasłami.
     * @param input Wyszukiwana fraza.
     * @param getter Pointer do odpowiedniej funkcji getter która zwraca parametr do porównania w klasie Password.
     */
    void filterPasswordsByGetter(vector<Password> hasla, vector<Password>& buffHasla, const string& input, const string& (Password::*getter)() const);
}

#endif //MENADZER_HASEL_SEARCH_H
