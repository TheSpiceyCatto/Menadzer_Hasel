#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
using namespace std;

#ifndef MENADZER_HASEL_KOMENDY_H
#define MENADZER_HASEL_KOMENDY_H


namespace Biblioteka{
    class Functions{
    public:
        static auto encryption(string haslo, string key){
            string result;
            int keyPos = 0;
            stringstream strStream;
            for(string::iterator it = haslo.begin(); it != haslo.end(); ++it){
                char shift = key[keyPos % key.length()];
                int character = *it + shift;
                strStream << hex << character;
                keyPos++;
            }
            return strStream.str();
        }

        static auto decryption(string haslo, string key){
            string result = "";
            int keyPos = 0;
            for(int i = 0; i < haslo.length(); i+=2){
                char shift = key[keyPos % key.length()];
                string hexVal = string() + haslo[i] + haslo[i + 1];
                result += char(stoi(hexVal, nullptr, 16) - shift);
                keyPos++;
            }
            return result;
        }

        static void OpenFile(fstream& file, string& currentKey, const string& masterKey){
            cout << "Podaj sciezke do pliku:" << endl;
            string directory;
            cin >> directory;
            file.open(directory, ios::in | ios::out);
            if(!file){
                file.close();
                file.clear();
                file.open(directory, ios::out);
                cout << "Nie wykryto pliku! Tworze nowy plik." << endl;
                file.close();
                file.clear();
                file.open(directory, ios::in | ios::out);
            }
            string haslo;
            if(file.peek() == fstream::traits_type::eof()){
                cout << "Plik pusty, stwórz hasło:" << endl;
                cin >> haslo;
                file.seekg(0, ios::beg);
                file << Functions::encryption(haslo, masterKey);
            } else {
                cout << "Podaj haslo:" << endl;
                cin >> haslo;
                string correctPass;
                getline(file, correctPass);
                while(Functions::encryption(haslo, masterKey) != correctPass){
                    cout << "Haslo niepoprawne, sprobuj ponownie:" << endl;
                    cin >> haslo;
                }
            }
            currentKey = haslo;
            cin.clear();
            cin.ignore();
        }

        static void helpPage(string dir){
            ifstream helpFile(dir);
            string line;
            while(getline(helpFile, line)){
                cout << line << endl;
            }
            helpFile.close();
        }

        static string chooseCategory(vector<string>& kategorie){
            cout << "Wybierz kategorie (podaj numer):" << endl;
            for(int i = 0; i < kategorie.size(); i++){
                cout << i+1 << ". " << kategorie[i] << endl;
            }
            int choice;
            bool correctChoice = false;
            while (!correctChoice){
                cin >> choice;
                if(choice > 0 && choice <= kategorie.size()){
                    correctChoice = true;
                } else {
                    cout << "Niepoprawny wybor kategorii." << endl;
                }
            }
            return kategorie.at(choice-1);
        }

        static string evaluatePassword(string haslo){
            int score = haslo.size();
            bool lower = false, upper = false, special = false;
            for (auto it = haslo.begin(); it != haslo.end(); ++it) {
                int val = (int)*it;
                if (islower(val))
                    lower = true;
                if (isupper(val))
                    upper = true;
                if ((val >= 33 && val <= 47) || (val >= 60 && val <= 64) || (val >= 91 && val <= 96) || (val >= 123 && val <= 126))
                    special = true;
            }
            if (lower && upper)
                score += 3;
            if (special)
                score += 2;
            if (score < 10){
                return "slabe";
            } else if (score < 15){
                return "dobre";
            } else if (score < 20){
                return "bardzo dobre";
            } else if (score < 30){
                return "bardzo, ale to bardzo dobre";
            }
        }

        static string generatePassword(){
            int charNum;
            bool upLow, special, numbers;
            string input;

            cout << "Podaj ilosc znakow:" << endl;
            getline(cin, input);
            while(cin.fail() || input.empty() || !isNumber(input) || (isNumber(input) && stoi(input) <= 0)){
                cout << "Niepoprawna odpowiedz, sprobuj ponownie:" << endl;
                getline(cin, input);
            }
            charNum = stoi(input);

            Boolean_Question("Czy uzywac wielkich i malych liter? Y/n", upLow);
            Boolean_Question("Czy uzywac liczb? Y/n", numbers);
            Boolean_Question("Czy uzywac znakow specjalnych? Y/n", special);

            int choiceMin = numbers ? 1 : 2;
            int choiceMax = special ? 3 : 2;
            string result;
            for (int i = 0; i < charNum; ++i) {
                int randChoice = getRandomNumber(choiceMin, choiceMax);
                if (randChoice == 1) {
                    result += (char)getRandomNumber(48, 57);
                } else if (randChoice == 2) {
                    if(upLow && getRandomNumber(0, 1) == 1){
                        result += (char)getRandomNumber(65, 90);
                    } else {
                        result += (char) getRandomNumber(97, 122);
                    }
                } else if (randChoice == 3) {
                    string specialChars = "!\"#$%&'()*+,-./:<=>?@[\\]^_`{|}~";
                    int randomIndex = getRandomNumber(0, specialChars.length() - 1);
                    result += specialChars[randomIndex];
                }
            }
            return result;
        }
        static void Boolean_Question(const string mess, bool& result){
            bool answered = false;
            string input;
            do{
                cout << mess << endl;
                getline(cin, input);
                if (toupper(input[0]) == 'N') {
                    result = false;
                    answered = true;
                } else if (toupper(input[0]) == 'Y' || input[0] == '\0') {
                    result = true;
                    answered = true;
                } else {
                    cout << "Nie rozpoznano odpowiedzi" << endl;
                }
            } while (!answered);
        }

        static bool isNumber(string& str) {
            try {
                size_t pos = 0;
                stoi(str, &pos);
                return pos == str.length();
            } catch (const exception&) {
                return false;
            }
        }

        static int getRandomNumber(int min, int max) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distribution(min, max);
            return distribution(gen);
        }
    };
}

#endif //MENADZER_HASEL_KOMENDY_H
