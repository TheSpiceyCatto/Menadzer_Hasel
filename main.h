#ifndef MENADZER_HASEL_MAIN_H
#define MENADZER_HASEL_MAIN_H
#include <iostream>
#include <string>
#include <vector>
#include "commands/Search.h"
#include "commands/DeleteCategory.h"
#include "commands/DeletePassword.h"
#include "commands/AddPassword.h"
#include "commands/AddCategory.h"
#include "FunctionLibrary.h"
using namespace std;

namespace Main{
    /**
     * Odczytuje komendy użytkownika i wywołuje odpowiednie funkcje.
     * @param hasla Referencja do vectora z aktualnymi hasłami.
     * @param kategorie Referencja do vectora z aktualnymi kategoriami.
     * @param directory Ścieżka do pliku źródłowego.
     * @param currentKey Aktualny klucz szyfrowania.
     */
    void readCommands(vector<Password>& hasla, vector<string>& kategorie, const string directory, const string currentKey);
}

#endif //MENADZER_HASEL_MAIN_H
