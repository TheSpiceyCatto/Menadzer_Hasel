#ifndef MENADZER_HASEL_DELETECATEGORY_H
#define MENADZER_HASEL_DELETECATEGORY_H
#include <iostream>
#include "../FunctionLibrary.h"
using namespace std;

namespace Delete{
    /**
     * Usuwa podaną przez użytkownika kategorie oraz hasla z nią związane.
     * @param directory Ścieżka pliku źródłowego.
     * @param hasla Referencja do vectora z zapisanymi hasłami.
     * @param kategorie Referencja do vectora z aktualnymi kategoriami.
     * @param key Klucz do odszyfrowania haseł i informacji o nich zapisanych w pliku źródłowym.
     */
    void UsunKategorie(string directory, vector<Password>& hasla, vector<string>& kategorie, string key);
}

#endif //MENADZER_HASEL_DELETECATEGORY_H
