#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

#define LIFE 50

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
/*Loads dictionary words from a file and puts them into the dictionary
 */
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

/*puts words from the dictionary into wordList that match the given length
 */
void getWordsByLength(unsigned int length,const set<string>& dictionary, set<string>& wordList){
    for(string word : dictionary){
        if (word.length() == length)wordList.insert(word);
    }
}

/*checks if two words are of the same family given an array of guessed letters
 */
bool sameFamily(const string word1,const string word2,const char* letters,const int guesses){    
    if (word1.length() ==  word2.length()){
        for(int i = 0; i < word1.length(); i++){
	    for (int j = 0; j < guesses; j++){
		char letter = letters[j];
		    
		if ((word1[i] == letter) || (word2[i] == letter)){
		    if (!(word2[i] == word1[i])){
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

/*given a set of words and an array of letter guesses sorts the words into a set of word families 
 */
void sortByFamily(char* guesses, const set<string> words, set<set<string> >& families, int amountGuesses){
    families.clear();
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


/*sets the words set to the longest word family in the families set
 */
void longestFamily(set<string>& words, const set<set<string> > families){
    set<string> longest;
    
    for (set<string> family : families){
	
	if(longest.size() < family.size()){
	    longest = family;
	}
    }
    words = longest;
}

/*prints out only the correct guessed letters in a word
 */
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

/*debug function that prints out information about a given word family
 */
void familyInfo(set<string> family){
    cout << "len: " << family.size() << "\n{";

    int i = 0;
    for (string word : family){
	cout << word << ", ";
	i++;
	if (i%10 == 0){
	    cout << "\n";
	}
    }
    cout << "}" << endl;   
}

/*prints all the families in a set
 */
void familiesInfo(set<set<string> > families){
    for (set<string> fam : families){
        familyInfo(fam);
    }
}

void lastLife(set<string>& words, const set<set<string> > families, char* guesses){
}

int main() {
    char guessedLetters[LIFE];
    int guesses = 0;
    set<string> dictionary;
    set<string> words;
    set<set<string> > families;
    int length;

    set<string> s1,s2,s3,s4,s5,s6,s7,s8, w;
    set<set<string> > f1;

    generateDictionary(dictionary);
    
    cout << "Welcome to Hangman." << endl;
    cout << "please enter length of word." << endl;
    
    
    cin >> length;

    getWordsByLength(length, dictionary, words);
    
    while(guesses < LIFE)
    {
        char guess;
        bool sepGuess = false;
        while (!sepGuess){
            cout << "Enter a Letter"<<endl;
            cin >> guess;

            sepGuess = true;
            for(int i = 0; i < guesses; i++){
                sepGuess = !(guessedLetters[i] == guess);
            }
        }
        guessedLetters[guesses] = guess;
	
        guesses++;
	
        sortByFamily(guessedLetters, words, families, guesses);
        longestFamily(words, families);
        printWordByGuesses(guessedLetters, *(words.begin()), guesses);
    }
    
    return 0;
}
