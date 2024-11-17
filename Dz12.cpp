#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

namespace fisy = std::filesystem;
using namespace std;

int main() {
    map<string, int> mymap;
    ifstream file("text.txt");

    if (!file) {
        cerr << "Error: Can't open file 'text.txt'" << endl;
        return 1;
    }

    fisy::path fpath = "words";
    if (!fisy::exists(fpath)) {
        if (fisy::create_directory(fpath)) {
            cout << "Folder " << fpath << " created" << endl;
        }
        else {
            cerr << "Error: Unable to create folder 'words'" << endl;
            return 1;
        }
    }
    else {
        cout << "Folder already exists\n";
    }

    fisy::path filep = fpath / "words.txt";
    ofstream file2(filep);

    if (!file2) {
        cerr << "Error: Can't create file '" << filep << "'" << endl;
        return 1;
    }

    string text, most_word;
    while (getline(file, text)) {
        stringstream ss(text);
        string word;
        while (ss >> word) {
            mymap[word]++;
        }
    }
    file.close();

    int max = 0;
    for (const auto& [word, num] : mymap) {
        cout << word << ": " << num << endl;
        file2 << word << ": " << num << endl;
        if (num > max) {
            max = num;
            most_word = word;
        }
    }

    cout << "\nMost often word: " << most_word << ": " << max << endl;
    file2 << "\nMost often word: " << most_word << ": " << max << endl;

    cout << "File '" << filep << "' created successfully" << endl;
    file2.close();

    return 0;
}
