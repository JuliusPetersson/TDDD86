// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

static const string L_ALPHABET = "abcdefghijklmnopqrstuvwxyz";
static const string U_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char toUpper(char c){
    for (unsigned int i = 0; i < U_ALPHABET.size(); i++){
        if (L_ALPHABET[i] == c) return U_ALPHABET[i];
    }
    return c;
}

char readLetter() {
    string s;
    std::getline(std::cin,s);

    for (unsigned int i = 0; i <  U_ALPHABET.size(); i++){
        if (U_ALPHABET[i] == toUpper(s[0])) return U_ALPHABET[i];
    }

    return '0';
}

string readWord() {
    string s;
    std::getline(std::cin,s);
    for (unsigned int j = 0; j < s.size(); j++){
        s[j] = toUpper(s[j]);
    }

    return s;
}

void playOneGame(Boggle& boggle) {
    boggle.resetGame();
    std::cout << "do you wish to randomize a board?(y/n)" << std::endl;

    string c;
    bool correctInput;
    do{
        std::getline(std::cin, c);
        correctInput = c == "y" || c == "n";
        if(!correctInput){
            std::cout << "enter y or n" << std::endl;
        }
    }while(!correctInput);


    if (c == "y"){
        boggle.randomizeBoard();
    }
    else{
        string s;
        char c;
        while (s.size() < (boggle.BOARD_SIZE)*(boggle.BOARD_SIZE)){
            std::cout << "input letter" << std::endl;
            c = readLetter();
            if (c!='0'){
                s += c;
            }
        }
        boggle.forceSetup(s);
    }

    boggle.draw();
    string inputword;
    do{
        std::cout << "Enter a word on the board, atleast four letters"<<std::endl;
        inputword = readWord();

        if (boggle.inputWord(inputword)){
            boggle.updateHumanPoints();
            std:: cout << "\n" << "Your words are: "<< std:: endl;
            for (string s : boggle.getHumanWords()){
                std::cout << s << "\n";
            }
            std::cout << std::endl;

            std:: cout << "Your have "<< boggle.humanPoints << " points" << std:: endl;
        }
        else if(inputword!=""){
            std::cout << "invalid word, try again!" << std::endl;
        }
        else{
            std::cout << "finishing up" << std::endl;
        }
        std::cout << "--------------------------" << std::endl;
    }while (inputword != "");
    boggle.generateRobotWords();
    boggle.updateRobotPoints();
    if(boggle.robotPoints > boggle.humanPoints){
        std:: cout << "AHAHAH YOU LOST SUCKER!!!!  " << "\nMY WORDS WERE:   "<< std:: endl;
        for (string s : boggle.getRobotWords()){
            std::cout << s << "\n";
        }
        std::cout << std::endl;
        std:: cout << "MY SCORE WAS: "<< boggle.robotPoints << std:: endl;
    }else{
        std:: cout << "FINE YOU WON THIS TIME! I WILL REMEMBER THIS!" << " \nMY WORDS WERE:   "<< std:: endl;
        for (string s : boggle.getRobotWords()){
            std::cout << s << "\n";
        }
        std::cout << std::endl;
        std:: cout << " MY SCORE WAS: "<< boggle.robotPoints << std:: endl;
    }
}
//implement reset

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
