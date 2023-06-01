#ifndef MENADZER_HASEL_ADDPASSWORD_H
#define MENADZER_HASEL_ADDPASSWORD_H
#include <iostream>
#include "../FunctionLibrary.h"
using namespace std;

namespace AddPassword{
    void DodajHaslo(vector<Password>& hasla, vector<string>& kategorie, string directory, string key);
    string generatePassword();
    string evaluatePassword(string haslo);
    void writePassword(string directory, Password& haslo, string& key);
}

#endif //MENADZER_HASEL_ADDPASSWORD_H
