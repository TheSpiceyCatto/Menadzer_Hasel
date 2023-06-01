#include "AddCategory.h"

void AddCategory::DodajKategorie(vector<string>& kategorie) {
    string kategoria;
    cout << "Podaj nowa kategorie:" << endl;
    cin >> kategoria;
    bool isValid;
    do {
        isValid = true;
        for (auto it = kategorie.begin(); it != kategorie.end(); ++it) {
            if (it->compare(kategoria) == 0){
                isValid = false;
                cout << "Kategoria juz istnieje, sprobuj ponownie:" << endl;
                cin >> kategoria;
            }
        }
    } while (!isValid);
    kategorie.push_back(kategoria);
    cout << "Kategoria dodana" << endl;
    cin.clear();
    cin.ignore();
}
