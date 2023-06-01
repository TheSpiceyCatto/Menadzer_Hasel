#ifndef MENADZER_HASEL_ADDCATEGORY_H
#define MENADZER_HASEL_ADDCATEGORY_H
#include <iostream>
#include <vector>
using namespace std;

namespace AddCategory{
    /**
     * Funkcja dodaje nową kategorię podaną przez użytkownika.
     *
     * @param kategorie Referencja do vectora z aktualnymi kategoriami.
     */
    void DodajKategorie(vector<string>& kategorie);
}

#endif //MENADZER_HASEL_ADDCATEGORY_H
