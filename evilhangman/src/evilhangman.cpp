#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

#define LIFE 10

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void generateDictionary(set<string>& dictionary){
    string dictWord;
    fstream file;
    file.open("dictionary.txt");
    if (file.is_open()){
	while (getline(file, dictWord)){
	    dictionary.insert(dictWord);
	}
    }
    else{
	cout << "file not opened" << endl;
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
                    return false;
                }
            }
        }

        return true;
    }
    else{
        return false;
    }
}

void sortByFamily(char guess, set<string>& words, set<set<string> >& families){
    while (!words.empty()) {
        set<string> family;
	const string testWord = *words.begin();
        family.insert(testWord);
        words.erase(testWord);

	
        for(set<string>::iterator word = words.begin();word != words.end(); word++){
	    if (sameFamily(testWord, *word, guess)){
	      family.insert(*word);
	      words.erase(*word);
	    }
        }

	families.insert(family);
    }
}

void longestFamily(set<string>& words, const set<set<string> > families){
    set<string> longest;
    
    for (set<set<string> >::iterator family = families.begin();family != families.end(); family++){
	
	if(longest.size() < (*family).size()){
	    longest = *family;
	}
    }

    words = longest;
}

void printWordByGuesses(char* guessedLetters, string word, int guesses){
    for (char wletter : word){
	bool view = false;
	for (int i = 0; i < guesses && !view; i++){
	    view = wletter == guessedLetters[i];
	}
	
	if (view){
	    cout << wletter << " ";
	}
	else{
	    cout << "_ ";
	}
	
    }
    cout << endl;
}

int main() {
    char guessedLetters[LIFE];
    int guesses = 0;
    set<string> dictionary;
    set<string> words;
    set<set<string> > families;
    int length;

    generateDictionary(dictionary);

    cout << "Welcome to Hangman." << endl;
    cout << "please enter length of word." << endl;
    
    cin >> length;

    getWordsByLength(length, dictionary, words);

    while(guesses < LIFE){
	char guess;
	cout << "Enter a Letter"<<endl;
	cin >> guess;
	guessedLetters[guesses] = guess;
	
	guesses++;
	
	sortByFamily(guess, words, families);
	longestFamily(words, families);
	printWordByGuesses(guessedLetters, *words.begin(), guesses);

	for (string word : words){
	    cout << word << ", ";
	}
	cout << endl;
    }
    
    return 0;
}
