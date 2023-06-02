template <typename T> T chooseFromVector(const string mess, vector<T> vec, const string err){
    cout << mess << endl;
    for(int i = 0; i < vec.size(); i++){
        cout << i+1 << ". " << vec.at(i) << endl;
    }
    int choice;
    bool correctChoice = false;
    while (!correctChoice){
        cin >> choice;
        if(choice > 0 && choice <= vec.size()){
            correctChoice = true;
        } else {
            cout << err << endl;
        }
        cin.clear();
        cin.ignore();
    }
    return vec.at(choice-1);
}
