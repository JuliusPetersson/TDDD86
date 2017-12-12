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

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
                                          "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                          "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                                          "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
                                          "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
                                 };





void Boggle:: resetGame(){
    humanWords.clear();
    robotWords.clear();
    robotPoints = 0;
    humanPoints = 0;
}

bool Boggle:: evaluateWord(const string word) const{
    if(!(wordList.contains(word)) || (word.size() < 4)) return false;
    for (string i:humanWords){
        if (i == word) return false;
    }
    return true;
}

bool Boggle:: inputWord(const string s){

    if (evaluateWord(s)&&isOnBoard(s)){
        humanWords.insert(s);
        return true;
    }
    else{
        return false;
    }

}

bool Boggle:: isOnBoard(const string word) {
    int x,y;
    bool onboard;
    for (int i = 0; i < NUM_CUBES; i++){
        x = i%BOARD_SIZE;
        y = i/BOARD_SIZE;

        if (board[x][y].c == word[0]){
            onboard = isNeighbour(x,y,word.substr(1));
            if (onboard) return true;
        }
    }
    return false;
}

bool Boggle::isNeighbour(int letterX, int letterY, const string word) {
    board[letterX][letterY].visited = true;
    if (word.size()==0){
        board[letterX][letterY].visited = false;
        return true;
    }
    for(int x = -1; x < 2; x++){
        for(int y = -1; y < 2; y++){
            if((!(letterX+x < 0 || BOARD_SIZE<=letterX+x))&&
                    (!(letterY+y < 0 || BOARD_SIZE<=letterY+y))&&
                    (word[0] == board[letterX+x][letterY+y].c)&&
                    !(board[letterX+x][letterY+y].visited)){

                if(isNeighbour(letterX+x,letterY+y, word.substr(1))){
                    board[letterX][letterY].visited = false;
                    return true;
                }
            }
        }
    }
    board[letterX][letterY].visited = false;
    return false;
}

void Boggle:: robotLetterSearch(int letterX, int letterY, string word){
    board[letterX][letterY].visited = true;
    word = word + board[letterX][letterY].c;

    if (wordList.contains(word)&&evaluateWord(word)){
        robotWords.insert(word);
    }

    for(int x = -1; x < 2; x++){
        for(int y = -1; y < 2; y++){
            if((!(letterX+x < 0 || BOARD_SIZE<=letterX+x))&&
                    (!(letterY+y < 0 || BOARD_SIZE<=letterY+y))&&
                    (wordList.containsPrefix(word))&&
                    !(board[letterX+x][letterY+y].visited)){


                robotLetterSearch(letterX+x, letterY+y, word);

            }
        }
    }
    board[letterX][letterY].visited = false;
}

void Boggle:: removeUsedWords(){
    for (string i: humanWords){
        if (robotWords.find(i) != robotWords.end()){
            robotWords.erase(i);
        }
    }

}

void Boggle :: generateRobotWords(){
    for(int x = 0; x < BOARD_SIZE; x++){
        for(int y = 0; y < BOARD_SIZE; y++){
            robotLetterSearch(x,y, "");
        }
    }
    removeUsedWords();
}

set<string> Boggle :: getHumanWords() const{
    return humanWords;
}


set<string> Boggle :: getRobotWords() const{
    return robotWords;
}

void Boggle:: updateHumanPoints(){
    humanPoints = 0;
    for (string i:humanWords){
        humanPoints += i.size() - 3;
    }
}

void Boggle:: updateRobotPoints(){
    robotPoints = 0;
    for (string i:robotWords){
        robotPoints += i.size() - 3;
    }
}

void Boggle::randomizeBoard(){
    int x,y, randomNr;

    for (int i = 0; i < NUM_CUBES; i++){
        x = i%BOARD_SIZE;
        y = i/BOARD_SIZE;

        randomNr = randomInteger(0, BOARD_SIZE);
        board[x][y].c = CUBES[i][randomNr];
    }
}

Boggle:: Boggle(){
    robotWords = set<string>();
    board = Grid<Cube>(BOARD_SIZE,BOARD_SIZE);
    humanPoints = 0;
    robotPoints = 0;
    randomizeBoard();

    humanWords = set<string>();
    shuffle(board);
    wordList = Lexicon("EnglishWords.dat");
}

void Boggle:: draw() const{
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            std::cout << board.get(x,y).c;
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Boggle:: forceSetup(const string s){
    int x,y;
    for (int i = 0; i < NUM_CUBES; i++){
        x = i%BOARD_SIZE;
        y = i/BOARD_SIZE;

        Cube c = Cube();
        c.c = s[i];
        board[x][y] = c;
    }
}

void Boggle:: juliusForce(){
    string rows[] = {"FYCL", "IOMG", "ORIL","HJHU"};
    for (int y = 0; y < BOARD_SIZE; y++){
        for(int x = 0; x < BOARD_SIZE; x++){
            board[x][y].c = rows[y][x];
        }
    }
}
