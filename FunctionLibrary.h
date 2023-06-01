#ifndef MENADZER_HASEL_FUNCTION_LIBRARY_H
#define MENADZER_HASEL_FUNCTION_LIBRARY_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include <sstream>
#include "Password.h"
using namespace std;

namespace Functions {
    string encryption(string haslo, string key);
    string decryption(string haslo, string key);
    void readFile(string directory, vector<Password>& hasla, vector<string>& kategorie, string key);
    void openFile(string directory, string& currentKey, const string& masterKey);
    void booleanQuestion(const string mess, bool& result);
    template <typename T> T chooseFromVector(string mess, vector<T> vec, string err);
    bool isNumber(string& str);
    int getRandomNumber(int min, int max);
    void helpPage(string dir);
    #include "ChooseFromVector.tpp"
}
#endif