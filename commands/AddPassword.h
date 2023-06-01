#ifndef MENADZER_HASEL_ADDPASSWORD_H
#define MENADZER_HASEL_ADDPASSWORD_H
#include <iostream>
#include "../FunctionLibrary.h"
using namespace std;

namespace AddPassword{
    /**
     * Tworzy nowe hasło na podstawie odpowiedzi podanych przez użytkownika a następnie dodawane jest ono do pliku źródłowego.
     *
     * @param hasla Referencja do vectora z aktualnymi hasłami.
     * @param kategorie Referencja do vectora z kategoriami które użytkownik może wybrać podczas tworzenia hasła.
     * @param directory Ścieżka do pliku źródłowego.
     * @param key Klucz do zaszyfrowania nowego hasła.
     */
    void DodajHaslo(vector<Password>& hasla, vector<string>& kategorie, string directory, string key);

    /**
     * Generuje nowe hasło na podstawie odpowiedzi podanych przez użytkownika.
     * @return Wygenerowane hasło
     */
    string generatePassword();

    /**
     * Ocenia hasło na podstawie jego długości, zawartości dużych i małych znaków oraz znaków specjalnych.
     * @param haslo Hasło do ocenienia
     * @return Ocena hasła
     */
    string evaluatePassword(string haslo);

    /**
     * Dopisuje zaszyfrowane hasło do pliku źródłowego.
     * @param directory Ścieżka do pliku źródłowego.
     * @param haslo Referencja do hasło do dodania.
     * @param key Klucz do zaszyfrowania hasła.
     */
    void writePassword(string directory, Password& haslo, string& key);
}

#endif //MENADZER_HASEL_ADDPASSWORD_H
