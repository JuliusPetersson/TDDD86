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
void playOneGame(Boggle& boggle) {
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
        boggle.forceSetup();
    }

    boggle.draw();
    while (boggle.inputWord()){
        boggle.updateHumanPoints();
        std:: cout << "\n" << "Your words are: "<< std:: endl;
        boggle.printHumanwords();
        std:: cout << "\n" << "Your points are:   "<< boggle.humanPoints <<  std:: endl;
    }
    boggle.generateRobotWords();
    boggle.updateRobotPoints();
    if(boggle.robotPoints > boggle.humanPoints){
        std:: cout << "AHAHAH YOU LOST SUCKER!!!!  " << "\nMY WORDS WERE:   "<< std:: endl;
        boggle.printRobotWords();
        std:: cout << "MY SCORE WAS: "<< boggle.robotPoints << std:: endl;
    }else{
        std:: cout << "FINE YOU WON THIS TIME! I WILL REMEMBER THIS!" << " \nMY WORDS WERE:   "<< std:: endl;
        boggle.printRobotWords();
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
