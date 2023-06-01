#ifndef MENADZER_HASEL_SEARCH_H
#define MENADZER_HASEL_SEARCH_H
#include <iostream>
#include "../FunctionLibrary.h"
using namespace std;

namespace Search{
    void Wyszukaj(vector<Password> hasla, vector<string>& kategorie);
    void filterPasswordsByGetter(vector<Password> hasla, vector<Password>& buffHasla, const string& input, const string& (Password::*getter)() const);
}

#endif //MENADZER_HASEL_SEARCH_H
