#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void generateDictionary(set<string>& dictionary){
    string dictWord;
    fstream file;
    file.open("dictionary.txt");
    while (getline(file, dictWord)){
        dictionary.insert(dictWord);
    }

}

int main() {
    cout << "Welcome to Hangman." << endl;

    set<string> dictionary;
    generateDictionary(dictionary);

    for (vector<string>::iterator it = neighbours.begin(); it < neighbours.end(); it++){

    }

    // TODO: Finish the program!

    return 0;
}
