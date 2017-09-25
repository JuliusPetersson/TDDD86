#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

#define LIFE 70

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
bool sameFamily(const string word1,const string word2,const char letter){    
    if (word1.length() ==  word2.length()){
        for(int i = 0; i < word1.length(); i++){
	    if ((word1[i] == letter) || (word2[i] == letter)){
	        if (!(word2[i] == word1[i])){
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

/*given a set of words and an array of letter guesses sorts the words into a set of word families 
 */
void sortByFamily(char guess, set<string> words, set<set<string> >& families){
    families.clear();
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

/*sets the words set to the longest word family in the families set
 */
void longestFamily(set<string>& words, const set<set<string> > families){
    set<string> longest;
    
    for (set<string> family : families){
	
	if(longest.size() < family.size()){
	    
	    familyInfo(longest);
	    cout << "------------" << endl;
	    familyInfo(family);
	    cout << "------------" << endl;
	    longest = family;
	}
    }
    words = longest;
}

bool charInWord(const string word, char letter){
    bool match = false;

    for (char wLetter : word){
	match = match || (wLetter == letter);
    }

    return match;
}

/*
  looks if there is a family of words that does not have the given letter in it,
  assumes the list has been sorted by family.
  returns true if family was found, otherwise false
 */
bool getNonMatch(char guess, const set<set<string> > families, set<string>& words){
    for (set<string> family : families){
	
	if(charInWord(*family.begin(), guess)){
	    words = *families.begin();
	    return true;
	}
    }
    return false;
}

bool wholeMatch(string word, char* guesses){
    bool match = true;
    for (char letter : word){
	bool semiMatch = false;
	for (char guess : guesses){
	    semiMatch = semiMatch || (letter = guess);
	}
	match = match && semiMatch;
    }

    return match;
}

int main() {
    char guessedLetters[LIFE];
    int guesses = 0;
    set<string> dictionary;
    set<string> words;
    set<set<string> > families;
    int length;
    bool victory = false;

    set<string> s1,s2,s3,s4,s5,s6,s7,s8, w;
    set<set<string> > f1;

    generateDictionary(dictionary);
    
    cout << "Welcome to Hangman." << endl;
    cout << "please enter length of word." << endl;

    {
	bool correct_input = false;
	while (!correct_input){
	    cin >> length;

	    correct_input = !cin.fail();
	    if (!correct_input) {
		cout << "Invalid input"  << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
	    }
	}
    }

    getWordsByLength(length, dictionary, words);
    
    while(guesses < LIFE && !victory)
    {
        char guess;
	bool new_letter = false;
	
	while(!new_letter){
		
	    cout << "Enter a Letter"<<endl;
	    try {
		cin >> guess;
		
		new_letter = true;
		for(int i = 0; i < guesses; i++){
		    new_letter = new_letter && !(guessedLetters[i] == guess);
		}
		if (!new_letter) cout << "already guessed " << "\""<< guess << "\"" << endl;

		new_letter = false;
		for (char alph_letter : ALPHABET){
		    new_letter = new_letter || guess == alph_letter;
		}
		if (!new_letter) cout << "\"" << guess << "\" " << "is not in alphabet" << endl;
	    }
	    catch(...){
		cout << "invalid input"<< endl;
	    }
	}

           
        
        guessedLetters[guesses] = guess;
	
        guesses++;
	sortByFamily(guess, words, families);

	if(!(words.size() == 2)) longestFamily(words, families);
	else{
	    if (!(getNonMatch(guess, families, words))){
		longestFamily(words, families);	
	    }
	    
		cout << "two words left" << endl;
	}

	printWordByGuesses(guessedLetters, *(words.begin()), guesses);

	victory = wholeMatch(words.begin(), guesses);
    }
    
    return 0;
}
