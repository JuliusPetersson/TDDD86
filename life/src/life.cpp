// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"

using namespace std;
const int LOW_BOUND = 1;
const int MIDDLE_BOUND = 3;
const int HIGH_BOUND = 4;

void openFile(fstream& file){
    //prompts user to enter file path and then tries to open the file.
    string filePath;

    cout << "Enter file path" << endl;
    cin >> filePath;
    file.open(filePath);
}

void loadGrid(Grid<char>& grid, fstream& file){
    /*
     * takes a grid and an open file
     *and loads in file data to create grid
     */

    if(file.is_open()){
        int columns, rows;
        file >> rows;
        file >> columns;

        grid = Grid<char>(rows, columns);

        for (int i = 0; i < rows; i++){
            string row;

            file >> row;
            for(int j = 0; j < columns; j++){
                grid.set(i,j, row[j]);
            }
        }
        file.close();
    }
    else{
        cout << "unable to open file" << endl;
    }
}


void printGrid(const Grid<char>& grid) {
    //prints a valid Grid<char>
    for (int rows = 0; rows < grid.numRows(); rows++){
        for (int cols = 0; cols < grid.numCols(); cols++){
            cout << grid.get(rows, cols);
        }
        cout << endl;
    }
}

int neighbours(const Grid<char>& grid, int col, int row){
    //counts the amount of alive neighbours a given square has

    int neighbours = 0;

    for (int i = row-1; i < row+2; i++){
        for (int j = col-1; j <col+2; j++){
            if(grid.inBounds(i, j) && !(i == row && j == col)){
                if (grid.get(i, j) == 'X'){
                    neighbours++;
                }
            }
        }
    }
    return neighbours;
}


void tick(Grid<char>& grid){
    //rolls the grid forward a generation

    Grid<char> nextGrid(grid.numRows(), grid.numCols());

    for (int y = 0; y < grid.numRows(); y++){
        for (int x = 0; x < grid.numCols(); x++){
            int neigh = neighbours(grid, x, y);
            if (neigh <= LOW_BOUND || neigh >= HIGH_BOUND){
                nextGrid.set(y,x, '-');
            }
            else if(neigh < MIDDLE_BOUND){
                nextGrid.set(y,x, grid.get(y,x));
            }
            else{
                nextGrid.set(y,x, 'X');
            }
        }
    }

    grid = nextGrid;
}


void animate(Grid<char> grid){
    //makes prints and pushes the grid forward for 100 generations automatically

    for (int i = 0; i < 100; i++){
        tick(grid);
        printGrid(grid);
        cout << "jhkassdajkhasdfsjdajkdfskhdfgshj" << endl;
        pause(100);
        clearConsole();
    }
}

void gameLoop(Grid<char>& grid){
    /*
     * main game loop.
     * lets the player choose between three options by entering either a,t or q
     * a - animate the given grid.
     * t - tick the grid forward one generation.
     * q - quit the program.
     */

    bool quit=false;

    while(!quit){

        cout << "a)nimate, t)ick, q)uit?" << endl;
        char input;
        cin >> input;

        if (input == 'a'){
            animate(grid);
        }
        else if(input== 't'){
            tick(grid);
            printGrid(grid);
        }
        else if(input == 'q'){
            quit = true;
        }

    }
    cout<<"Have a nice Life!"<<endl;
}

int main() {
    Grid<char> grid;

    {
        fstream gridFile;
        openFile(gridFile);
        loadGrid(grid, gridFile);
    }

    printGrid(grid);  
    gameLoop(grid);

    return 0;
}
