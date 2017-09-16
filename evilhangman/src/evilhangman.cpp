#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

#define LIFE 10

using namespace std;

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

bool sameFamily(string word1, string word2, char* letters, int guesses){
    
    if (word1.length() ==  word2.length()){
        for(int i = 0; i < word1.length(); i++){
	    for (int i = 0; i < guesses; i++){
		char letter = letters[i];
		    
		if (word1[i] == letter || (word2[i] == letter)){
		    if (!(word2[i] == letter && word1[i] == letter)){
			return false;
		    }
		}
	    }
        }

        return true;
    }
    else{
        return false;
    }
}

void sortByFamily(char* guesses, set<string>& words, set<set<string> >& families, int amountGuesses){

    while (!words.empty()) {
        set<string> family;
	const string testWord = *words.begin();

        family.insert(testWord);
        words.erase(testWord);
	
        for(set<string>::iterator word = words.begin();word != words.end(); word++){
	    if (sameFamily(testWord, *word, guesses, amountGuesses)){
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
	  cout << sizeof(*family) << endl;
	if(longest.size() < (*family).size()){
	    longest = *family;
	}
    }
    cout << sizeof(longest) << endl;
    words = longest;
    cout << sizeof(words) << endl;

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
    
    while(guesses < LIFE)
    {
	cout << sizeof(words) << endl;
	char guess;
	cout << "Enter a Letter"<<endl;
	cin >> guess;
	guessedLetters[guesses] = guess;
	
	guesses++;
	
	sortByFamily(guessedLetters, words, families, guesses);
	longestFamily(words, families);
	printWordByGuesses(guessedLetters, *words.begin(), guesses);
	cout << sizeof(words) << endl;
	
    }
    
    return 0;
}
