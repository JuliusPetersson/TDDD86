// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <array>
#include <iostream>
#include <string>
#include <grid.h>
#include <set>
#include "lexicon.h"
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();

    //checks to see if a word is a valid word
    bool evaluateWord(string) const;

    //draw self to board
    void draw() const;

    //allows the user to input a word
    bool inputWord();

    //checks if a given string is on the board
    bool isOnBoard(string);

    //debbuging setup, sets the board to a specific setup
    void juliusForce();

    //allows the user to force a setup
    void forceSetup();

    //recusivly look through all neghbours of letter to see if word can be created
    bool isNeighbour(int letterX, int letterY, string word);

    //recursively look through neighbours and adds all valid words to the robots word list
    void robotLetterSearch(int letterX, int letterY, string word);

    //generates the robots words
    void generateRobotWords();

    //prints the robots words
    void printRobotWords() const;

    //prints the humans words
    void printHumanwords() const;

    //generate the humans points
    void updateHumanPoints();

    //generate the robots points
    void updateRobotPoints();

    //resets the game
    void resetGame();

    //randomize the boards letters
    void randomizeBoard();

    //the humans points
    int humanPoints;

    //the robots points
    int robotPoints;
private:
    struct Cube{

        char c;
        bool visited;
    };

    Grid<Cube> board;
    void removeUsedWords();
    vector<string> humanWords;
    set<string> robotWords;
    Lexicon wordList;

    // TODO: decide the private member variables/functions and declare them

};

#endif
