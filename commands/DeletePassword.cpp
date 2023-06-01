#include "DeletePassword.h"

void DeletePassword::UsunHaslo(string directory, vector<Password>& hasla, string key){
    bool less;
    less = Functions::booleanQuestion("Czy chcesz usunac tylko jedno haslo? Y/n");
    int num;
    if (less){
        num = 1;
    } else {
        cout << "Podaj liczbe hasel do usuniecia (dostepnych hasel jest " << hasla.size() << "):" << endl;
        bool valid = false;
        while (!valid){
            cin >> num;
            if (num > 0 && num <= hasla.size()){
                valid = true;
            } else {
                cout << "Niepoprawna liczba hasel, sprobuj ponownie (dostepnych hasel jest " << hasla.size() << "):"<< endl;
            }
        }
    }
    if (num != hasla.size()){
        for (int i = 0; i < num; i++) {
            Password haslo = Functions::chooseFromVector("Wybierz haslo (podaj numer)", hasla, "Niepoprawny wybor hasla.");
            string info = haslo.toString();
            hasla.erase(remove_if(hasla.begin(), hasla.end(), [info](Password p){
                return p.toString() == info;
            }));
        }
    } else {
        hasla.clear();
    }

    fstream file(directory);
    vector<string> lines;
    string line;
    bool isFirst = true;
    while (getline(file, line)){
        if (isFirst){
            isFirst = false;
            lines.push_back(line);
        } else {
            string decryptedLine = Functions::decryption(line, key);
            bool toErase = true;
            for (Password p : hasla) {
                if (decryptedLine == p.toString()){
                    toErase = false;
                    break;
                }
            }
            if (!toErase)
                lines.push_back(line);
        }
    }
    file.clear();
    file.close();
    file.open(directory, std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open(directory, ios::in | ios::out);
    for (auto e : lines) {
        file << e << endl;
    }
    cin.clear();
    cin.ignore();
}
