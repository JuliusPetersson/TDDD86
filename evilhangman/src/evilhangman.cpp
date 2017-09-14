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

void getWordsWLength(unsigned int length,const set<string>& dictionary, set<string>& result){
    for(string word : dictionary){
        if (word.length() == length)result.insert(word);
    }
}

int main() {
    cout << "Welcome to Hangman." << endl;

    set<string> dictionary;
    generateDictionary(dictionary);


    // TODO: Finish the program!

    return 0;
}
