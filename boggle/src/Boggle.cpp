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

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// TODO: implement the members you declared in Boggle.h
Boggle:: Boggle(){
    int x,y, randomNr;
    board = Grid<char>(BOARD_SIZE,BOARD_SIZE);

    for (int i = 0; i < NUM_CUBES; i++){
        x = i%BOARD_SIZE;
        y = i/BOARD_SIZE;

        randomNr = randomInteger(0, BOARD_SIZE);
        board[x][y] = CUBES[i][randomNr];
    }

    shuffle(board);
}
