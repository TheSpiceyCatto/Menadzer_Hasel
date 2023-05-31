#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Krypt_Biblioteka.h"
using namespace Biblioteka;
using namespace std;


const static string masterKey = "AS!sdDeEeP0908@/kAsHdakdu";
static string currentKey;

bool isRunning = true;


auto main() -> int {
    cout << "Podaj sciezke do pliku:" << endl;
    string directory;
    cin >> directory;
    Functions::OpenFile(directory, currentKey, masterKey);
    Functions::helpPage("help.txt");

    vector<Haslo> hasla;
    vector<string> kategorie;

    Functions::readFile(directory, hasla, kategorie, currentKey);

    while (isRunning){
        isRunning = Functions::ReadCommands(hasla, kategorie, directory, currentKey);
    }
    return 0;
}
