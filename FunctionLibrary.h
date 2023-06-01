#ifndef MENADZER_HASEL_FUNCTION_LIBRARY_H
#define MENADZER_HASEL_FUNCTION_LIBRARY_H
#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include <sstream>
#include "Password.h"
using namespace std;

namespace Functions {
    /**
     * Szyfruje hasło na podstawie klucza.
     * @param haslo Hasło do zaszyfrowania.
     * @param key Klucz szyfru.
     * @return Zaszyfrowane hasło.
     */
    string encryption(string haslo, string key);

    /**
     * Odszyfrowuje hasło na podstawie klucza.
     * @param haslo Zaszyfrowane hasło do odszyfrowania.
     * @param key Klucz szyfru.
     * @return Odszyfrowane hasło.
     */
    string decryption(string haslo, string key);

    /**
     * Odczytuje hasła i kategorie zapisane w pliku źródłowym do odpowiednich vectorów.
     * @param directory Ścieżka do pliku źródłowego.
     * @param hasla Referencja do vectora do którego będą zapisane hasła.
     * @param kategorie Referencja do vectora do którego będą zapisane kategorie.
     * @param key Klucz do odszzyfrowania pliku.
     */
    void readFile(string directory, vector<Password>& hasla, vector<string>& kategorie, string key);

    /**
     * Otwiera ścieżkę do pliku źródłowego podaną przez użytkownika, jeśli plik istnieje pyta go o hasło główne i sprawdza czy jest poprawne, jeśli nie tworzy plik i użytkownik podaje nowe hasło główne.
     * @brief Sprawdza czy użytkownik zna hasło do pliku źródłowego albo czy trzeba stworzyć nowe.
     *
     * @param directory Ścieżka do pliku źródłowego.
     * @param currentKey Referencja do zmiennej w której będzie zapisane hasło główne do szyfrowania i odszyfrowania reszty haseł.
     * @param masterKey Klucz którym są szyfrowane jedynie hasła do plików źródłowych.
     */
    void openFile(string directory, string& currentKey, const string& masterKey);

    /**
     * Zadaje pytanie typu tak/nie i zwraca odpowiedź. Domyślna odpowiedź to tak.
     * @param mess Treść pytania.
     * @return Odpowiedź na pytanie.
     */
    bool booleanQuestion(const string mess);

    /**
     * Wypisuje zawartość vectora i czeka aż użytkownik wybierze jeden z elementów.
     * @tparam T Typ vectora.
     * @param mess Wiadomość dla użytkownika przed wybraniem elementu.
     * @param vec Wypisywany vector.
     * @param err Wiadomość gdy użytkownik wybierze nieistniejący element.
     * @return Wybrany element vectora.
     */
    template <typename T> T chooseFromVector(string mess, vector<T> vec, string err);

    bool isNumber(string& str);
    int getRandomNumber(int min, int max);

    /**
     * Odczytuje plik z podpowiedziami do korzystania z komend.
     * @param dir Ścieżka do pliku z podpowiedziami.
     */
    void helpPage(string dir);
    #include "ChooseFromVector.tpp"
}
#endif