#include "AddPassword.h"

void AddPassword::DodajHaslo(vector<Password>& hasla, vector<string>& kategorie, string directory, string key){
    if(!kategorie.empty()){
        string buffNazwa, buffHaslo, buffKategoria, buffStrona, buffLogin;

        cout << "Podaj nazwe hasla:" << endl;
        getline(cin, buffNazwa);
        while(cin.fail() || buffNazwa.empty()){
            cout << "Nie podano nazwy, sprobuj ponownie:" << endl;
            getline(cin, buffNazwa);
        }

        cout << "Podaj login (zostaw puste by pominac):" << endl;
        getline(cin, buffLogin);

        do {
            string input;
            cout << "Czy wygenerowac haslo? Y/n" << endl;
            getline(cin, input);
            if (toupper(input[0]) == 'N') {
                cout << "Podaj haslo:" << endl;
                getline(cin, buffHaslo);
                bool gotPass = false;
                while (!gotPass) {
                    bool exists = false;
                    for (auto haslo : hasla) {
                        if (haslo.getHaslo().compare(buffHaslo) == 0){
                            exists = true;
                            break;
                        }
                    }
                    if(cin.fail() || buffHaslo.empty()){
                        cout << "Nie podano hasla, sprobuj ponownie:" << endl;
                        getline(cin, buffHaslo);
                    } else if (exists){
                        cout << "Haslo juz istnieje! Sprobuj ponownie:" << endl;
                        getline(cin, buffHaslo);
                    } else {
                        gotPass = true;
                    }
                }
                cout << "Haslo jest " + evaluatePassword(buffHaslo) << endl;
            } else if (toupper(input[0]) == 'Y' || input[0] == '\0') {
                buffHaslo = generatePassword();
            } else {
                cout << "Nie rozpoznano odpowiedzi" << endl;
            }
        } while (buffHaslo.empty());

        cout << "Podaj strone WWW (zostaw puste by pominac):" << endl;
        getline(cin, buffStrona);

        buffKategoria = Functions::chooseFromVector("Wybierz kategorie (podaj numer):", kategorie, "Niepoprawny wybor kategorii.");

        Password haslo(buffNazwa, buffHaslo, buffKategoria);
        if(!buffStrona.empty()){
            haslo.setStrona(buffStrona);
        }
        if(!buffLogin.empty()){
            haslo.setLogin(buffLogin);
        }

        hasla.push_back(haslo);
        writePassword(directory, haslo, key);

        cin.clear();
        cin.ignore();
    } else {
        cout << "Brak kategorii, sprobuj \"Pomoc\" lub \"Dodaj Kategorie\"" << endl;
    }
}

string AddPassword::generatePassword(){
    int charNum;
    bool upLow, special, numbers;
    string input;

    cout << "Podaj ilosc znakow:" << endl;
    getline(cin, input);
    while(cin.fail() || input.empty() || !Functions::isNumber(input) || (Functions::isNumber(input) && stoi(input) <= 0)){
        cout << "Niepoprawna odpowiedz, sprobuj ponownie:" << endl;
        getline(cin, input);
    }
    charNum = stoi(input);

    upLow = Functions::booleanQuestion("Czy uzywac wielkich i malych liter? Y/n");
    numbers = Functions::booleanQuestion("Czy uzywac liczb? Y/n");
    special = Functions::booleanQuestion("Czy uzywac znakow specjalnych? Y/n");

    int choiceMin = numbers ? 1 : 2;
    int choiceMax = special ? 3 : 2;
    string result;
    for (int i = 0; i < charNum; ++i) {
        int randChoice = Functions::getRandomNumber(choiceMin, choiceMax);
        if (randChoice == 1) {
            result += (char) Functions::getRandomNumber(48, 57);
        } else if (randChoice == 2) {
            if(upLow && Functions::getRandomNumber(0, 1) == 1){
                result += (char) Functions::getRandomNumber(65, 90);
            } else {
                result += (char) Functions::getRandomNumber(97, 122);
            }
        } else if (randChoice == 3) {
            string specialChars = "!\"#$%&'()*+,-./:<=>?@[\\]^_`{|}~";
            int randomIndex = Functions::getRandomNumber(0, specialChars.length() - 1);
            result += specialChars[randomIndex];
        }
    }
    return result;
}

string AddPassword::evaluatePassword(string haslo){
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
    } else {
        return "bardzo, ale to bardzo dobre";
    }
}

void AddPassword::writePassword(string directory, Password& haslo, string& key){
    fstream file(directory);
    file.seekp(0, ios::end);
    file << endl << Functions::encryption(haslo.toString(), key);
    file.close();
}
