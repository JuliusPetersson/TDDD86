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

void getWordsByLength(unsigned int length,const set<string>& dictionary, set<string>& result){
    for(string word : dictionary){
        if (word.length() == length)result.insert(word);
    }
}

bool sameFamily(string word1, string word2, char letter){
    if (word1.length() ==  word2.length()){
        for(int i = 0; i < word1.length(); i++){
            if (word1[i] == letter || (word2[i] == letter)){
                if (!(word2[i] == letter && word1[i] == letter)){

                    cout << "fel familj" << endl;
                    return false;
                }
            }
        }

        cout << "sann" << endl;
        return true;
    }
    else{
        cout << "olika längd" << endl;
        return false;
    }
}

void sortByFamily(char guess, set<string>& words){
    set<set<string> > families;


    while (!words.empty()) {
        set<string> family;
        family.insert(*words.begin());
        words.erase(*words.begin());

        /*for(set<string>::iterator word = words.begin();word < words.end(); word++){
        }*/
    }
}

int main() {
    set<string> dictionary;
    set<string> words;
    int length;

    generateDictionary(dictionary);

    cout << "Welcome to Hangman." << endl;
    cout << "please enter length of word." << endl;

    while(words.size() == 0){
        cin >> length;
        getWordsByLength(length, dictionary, words);
    }

    cout << sameFamily("Cooadd","hejaff", 'a') << endl;

    return 0;
}
