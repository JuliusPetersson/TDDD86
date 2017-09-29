#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

#define LIFE 26

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
  get words from dictionary
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

/*
  puts words from the dictionary into wordList that match the given length
 */
void getWordsByLength(unsigned int length,const set<string>& dictionary, set<string>& wordList){
    for(string word : dictionary){
        if (word.length() == length)wordList.insert(word);
    }
}

/*
  checks if two words are of the same family given an array of guessed letters
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

/*
  given a set of words and an array of letter guesses sorts the words into a set of word families 
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




/*
  prints out only the correct guessed letters in a word
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

/*
  debug function that prints out information about a given word family
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

/*
  prints all the families in a set
 */
void familiesInfo(set<set<string> > families){
    for (set<string> fam : families){
        familyInfo(fam);
    }
}

/*
  sets the words set to the longest word family in the families set
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

/*
  checks if a given char is in a string 
 */
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


/*
  
 */
bool wholeMatch(string word, char* guessedLetters, int guesses){
    bool match = true;
    char guess;
    
    for (char letter : word){
	bool semiMatch = false;
	for (int i = 0; i < guesses; i++){
	    guess = guessedLetters[i];
	    semiMatch = semiMatch || (letter == guess);
	}
	match = match && semiMatch;
    }

    return match;
}

bool getYesNo(){
    string answ;

    while(answ != "yes" && answ != "no"){
	cin >> answ;
	if(answ != "yes" && answ != "no")cout << "invalid input, either say yes or no." << endl;
    }

    return answ == "yes";
    
}

char getLetter(const char* guessedLetters, int guesses){
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
	    if (!new_letter)cout << "already guessed " << "\""<< guess << "\"" << endl;
	       

	    if (new_letter){
		new_letter = false;
		for (char alph_letter : ALPHABET){
		    new_letter = new_letter || guess == alph_letter;
		}
		if (!new_letter) cout << "\"" << guess << "\" " << "is not in alphabet" << endl;
	    }
	}
	catch(...){
	    cout << "invalid input"<< endl;
	}
    }
    return guess;
}

int getInt(int bot, int top){
    bool correct_input = false;
    int nr;
    
    while (!correct_input){
	cin >> nr;
	
	correct_input = !cin.fail();
	if (!correct_input) {
	    cout << "Invalid input"  << endl;
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    
	}

	correct_input = bot < nr && nr < top;

	if (!correct_input){
	    cout << "Number not in span from " << bot << " to " << top << ". Enter a new nr." << endl;
	}
    }
    
    return nr;
}

int getWordLength(){
    bool correct_input = false;
    int length;
    while (!correct_input){
	cin >> length;
	
	correct_input = !cin.fail();
	if (!correct_input) {
	    cout << "Invalid input"  << endl;
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    
	}
    }

    return length;
}


int main() {
    char guessedLetters[LIFE];
    char guess;
    int guesses = 0;
    int life = 0;
    set<string> dictionary;
    set<string> words;
    set<set<string> > families;
    int length;
    bool victory = false;
    bool viewWords;
    set<string> s1,s2,s3,s4,s5,s6,s7,s8, w;
    set<set<string> > f1;

    generateDictionary(dictionary);
    
    cout << "Welcome to Hangman." << endl;
    cout << "please enter length of word." << endl;
    while (words.size() == 0){
	length = getWordLength();
	getWordsByLength(length, dictionary, words);
	if(words.size() == 0){
	    cout << "there where no letters of length " << length << endl;
	}
    }

    cout << "You wanna view the words left? yes/no" << endl;

    viewWords = getYesNo();

    cout << "How many guesses do you want?" << endl;

    life = getInt(0, 26);
    
    while(life > 0 && !victory)
    {
	if (viewWords)familyInfo(words);
	cout <<"\n--------------------------\n\nLife left " << life << "\n";
        guess = getLetter(guessedLetters, guesses);
        guessedLetters[guesses] = guess;
        guesses++;
	sortByFamily(guess, words, families);
	
	if (life == 1){
	    if (!(getNonMatch(guess, families, words))){
		longestFamily(words, families);	
	    }
	}
	else{
	    longestFamily(words, families);
	}

	if (!(charInWord(*words.begin(), guess))){
	    life--;
	}

	printWordByGuesses(guessedLetters, *(words.begin()), guesses);
	victory = wholeMatch(*words.begin(), guessedLetters, guesses);
    }

    if(victory){
	cout << "Congratulations, you won!" << endl;
    }
    else{
	cout << "You lost, try again!" << endl;
    }
    
    return 0;
}
