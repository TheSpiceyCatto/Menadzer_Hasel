#include "DeleteCategory.h"

void Delete::UsunKategorie(string directory, vector<Password>& hasla, vector<string>& kategorie, string key) {
    if (!kategorie.empty()){
        fstream file(directory);
        string choice = Functions::chooseFromVector("Wybierz kategorie (podaj numer):", kategorie, "Niepoprawny wybor kategorii.");
        kategorie.erase(find(kategorie.begin(), kategorie.end(), choice));
        file.clear();
        file.seekg(0, ios::beg);
        vector<string> lines;
        string line;
        while (getline(file, line)){
            string decryptedLine = Functions::decryption(line, key);
            if (decryptedLine.find("Kategoria: " + choice) == string::npos){
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
        hasla.erase(remove_if(hasla.begin(), hasla.end(), [choice](Password e) {return e.getKategoria().compare(choice) == 0;}), hasla.end());
    } else {
        cout << "Brak kategorii do usuniecia." << endl;
    }
}
