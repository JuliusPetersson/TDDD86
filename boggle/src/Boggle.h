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
    // TODO: decide the public member functions and declare them
    Boggle();
    bool evaluateWord(string);
    void draw() const;
    bool inputWord();
    bool isOnBoard(string);
    void juliusForce();
    void forceSetup();
    bool isNeighbour(int letterX, int letterY, string word);
    void robotLetterSearch(int letterX, int letterY, string word);
    void generateRobotWords();
    void printRobotWords();
    void printHumanwords();
    void updateHumansPoints();
    void updateRobotPoints();
    int humanPoints;
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
