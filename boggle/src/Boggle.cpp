// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "iostream"
#include "string"
#include "array"
#include "string"
#include "lexicon.h"

static const string L_ALPHABET = "abcdefghijklmnopqrstuvwxyz";
static const string U_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
                                          "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                          "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                                          "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
                                          "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
                                 };

// TODO: implement the members you declared in Boggle.h




char toUpper(char c){
    for (unsigned int i = 0; i < U_ALPHABET.size(); i++){
        if (L_ALPHABET[i] == c) return U_ALPHABET[i];
    }
    return c;
}

//reads upper/lower case letters from the input buffer,
//return upper case letter
//returns the charachter zero to indicate invalid input
char readLetter() {
    char c;
    std::cin >> c;

    for (unsigned int i = 0; i <  U_ALPHABET.size(); i++){
        if (U_ALPHABET[i] == toUpper(c)) return U_ALPHABET[i];
    }

    return '0';
}

//write this propperly its not right, needs like a string contains fuction or sumthin
string readWord() {
    string s;

    std::getline(std::cin,s);

    for (unsigned int j = 0; j < s.size(); j++){
        for (unsigned int i = 0; i < U_ALPHABET.size(); i++){
            if (U_ALPHABET ==toUpper(s[j])) return s;
        }
        s[j] = toUpper(s[j]);
    }

    return "dadda";
}

bool Boggle:: evaluateWord(string word){
    for (string i:humanWords){
        std:: cout << word <<  std::endl;
        if (i == word || !(wordList.contains(word)) || word.size() < 3) return false;
    }
    return true;
}

bool Boggle:: inputWord(){
    string s;
    do{
        cout << "enter your pathetic word" << endl;
        s = readWord();
        std::cout << s << std::endl;
        if (s == "") {
            return false;
        }else if((!evaluateWord(s))){
            cout << "invalid word" << endl;
        }
    }while(!evaluateWord(s));
    humanWords.push_back(s);
    return true;
}

bool Boggle:: isOnBoard(string word) const{


    //string s;
    //for (unsigned int i = 0; i < s.size(); i++){
        //s[i] = word[i];
      //  if (!wordList.containsPrefix(s)) return false;
    //}
    //if (wordList.contains(s)) return true;

    //return false;
}

bool Boggle::isOnBoard(int letterX, int letterY, string word){
    for(int x = -1; x < 2; x++){

        for(int y = -1; y < 2; y++){

            if(!(letterX+x < 0 || BOARD_SIZE<letterX+x)){

                if(!(letterY+y < 0 || BOARD_SIZE<letterY+y)){

                    if (!(y == 0 && x == 0)){

                        if(word[1] == board[y][x]){

                            if(isOnBoard(letterX+x,letterY+y, word.substr(1))) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

Boggle:: Boggle(){
    int x,y, randomNr;
    board = Grid<char>(BOARD_SIZE,BOARD_SIZE);

    for (int i = 0; i < NUM_CUBES; i++){
        x = i%BOARD_SIZE;
        y = i/BOARD_SIZE;

        randomNr = randomInteger(0, BOARD_SIZE);
        board[x][y] = CUBES[i][randomNr];
    }
    humanWords = vector<string>();
    shuffle(board);
    wordList = Lexicon("EnglishWords.dat");
}

void Boggle:: draw() const{
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            std::cout << board.get(y,x);
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Boggle:: forceSetup(){
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            std::cout << "enter a letter" << std::endl;
            char c;
            do{
                c = readLetter();
                if (c == '0'){
                    std::cout << "invalid input" << std::endl;
                }
            }
            while (c == '0');

            board.set(y,x,c);
        }
        std::cout << "\n";
    }
}

void Boggle:: juliusForce(){
    string rows[] = {"FYCL", "IOMG", "ORIL","HJHU"};
    for (int y = 0; y < BOARD_SIZE; y++){
        for(int x = 0; x < BOARD_SIZE; x++){
            board.set(y,x,rows[y][x]);
        }
    }
}
