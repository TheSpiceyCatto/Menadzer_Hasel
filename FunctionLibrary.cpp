#include "FunctionLibrary.h"

string Functions::encryption(string haslo, string key){
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

string Functions::decryption(string haslo, string key){
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

void Functions::readFile(string directory, vector<Password>& hasla, vector<string>& kategorie, string key){
    fstream file;
    file.open(directory, ios::in | ios::out);
    string nazwa, login, haslo, kategoria, strona;
    int startPos, endPos;
    string line;
    getline(file, line);
    while(getline(file, line)) {
        if (!line.empty()){
            line = decryption(line, key);

            bool hasLogin = line.find("; Login:") != string::npos;
            bool hasSite = line.find("; Strona:") != string::npos;

            startPos = line.find("Nazwa: ") + 7;
            endPos = hasLogin ? line.find("; Login:") : line.find("; Haslo:");
            nazwa = line.substr(startPos, endPos - startPos);

            if (hasLogin){
                startPos = line.find("Login: ") + 7;
                endPos = line.find("; Haslo:");
                login = line.substr(startPos, endPos - startPos);
            }

            startPos = line.find("Haslo: ") + 7;
            endPos = line.find("; Kategoria:");
            haslo = line.substr(startPos, endPos - startPos);

            startPos = line.find("Kategoria: ") + 11;
            endPos = hasSite ? line.find("; Strona:") : line.rfind(";");
            kategoria = line.substr(startPos, endPos - startPos);

            if (hasSite){
                startPos = line.find("Strona: ") + 8;
                endPos = line.rfind(";");
                strona = line.substr(startPos, endPos - startPos);
            }

            Password newHaslo(nazwa, haslo, kategoria);
            if (hasLogin)
                newHaslo.setLogin(login);
            if (hasSite)
                newHaslo.setStrona(strona);
            hasla.push_back(newHaslo);

            if (!(find(kategorie.begin(), kategorie.end(), kategoria) != kategorie.end())) {
                kategorie.push_back(kategoria);
            }
        }
    }
    file.close();
}

void Functions::openFile(string directory, string& currentKey, const string& masterKey){
    fstream file;
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
        file << encryption(haslo, masterKey);
    } else {
        cout << "Podaj haslo:" << endl;
        cin >> haslo;
        string correctPass;
        getline(file, correctPass);
        while(encryption(haslo, masterKey) != correctPass){
            cout << "Haslo niepoprawne, sprobuj ponownie:" << endl;
            cin >> haslo;
        }
    }
    currentKey = haslo;
    file.close();
    cin.clear();
    cin.ignore();
}

bool Functions::booleanQuestion(const string mess){
    bool result;
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
    return result;
}

bool Functions::isNumber(string& str) {
    try {
        size_t pos = 0;
        stoi(str, &pos);
        return pos == str.length();
    } catch (const exception&) {
        return false;
    }
}

int Functions::getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

void Functions::helpPage(string dir){
    ifstream helpFile(dir);
    string line;
    while(getline(helpFile, line)){
        cout << line << endl;
    }
    helpFile.close();
}
