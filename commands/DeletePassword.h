#ifndef MENADZER_HASEL_DELETEPASSWORD_H
#define MENADZER_HASEL_DELETEPASSWORD_H
#include "../FunctionLibrary.h"

namespace DeletePassword{
    /**
     * Usuwa jedno lub więcej haseł wybranych przez użytkownika.
     * @param directory Ścieżka do pliku źródłowego.
     * @param hasla Referencja do vectora z aktualnymi hasłami.
     * @param key Klucz do odszyfrowania haseł w pliku.
     */
    void UsunHaslo(string directory, vector<Password>& hasla, string key);
}

#endif //MENADZER_HASEL_DELETEPASSWORD_H
