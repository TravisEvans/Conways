#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h> // rand
#include <time.h>   //  time
using namespace std;

#ifndef Conways
#include "Conways.h"
using namespace Conways;
#endif

// declarations
void run(vector<vector<Cell>> displayGrid, vector<vector<Cell>> calculationGrid);
bool checkForLife(vector<vector<Cell>> displayGrid);
void populateCellGrid(vector<vector<Cell>> &displayGrid);
void displayCellGrid(vector<vector<Cell>> displayGrid);
void gameStep(vector<vector<Cell>> displayGrid, vector<vector<Cell>> calculationGrid);

/**
 * main function
 * @param none doesnt exist
 */
int main()
{
    vector<vector<Cell>> displayGrid;
    vector<vector<Cell>> calculationGrid;

    run(displayGrid, calculationGrid);  //  single instance of grids

    return 0;
}

void run(vector<vector<Cell>> displayGrid, vector<vector<Cell>> calculationGrid)
{
    if (!checkForLife(displayGrid))    {   //  so, if there is no life, do...
        populateCellGrid(displayGrid);   //  populate dead grid
    }

    system("clear");    //  with stepping, will clear screen
    cout << "\n\n\n" << endl;

    displayCellGrid(displayGrid); //  see how life is going
    cout << endl;
    gameStep(displayGrid, calculationGrid);    //  see the calculation grid

    cout << "\n\n\n" << endl;
}

bool checkForLife(vector<vector<Cell>> displayGrid)    {   //  check if life has ended (recursion reasons)
    bool life = false;
    for (vector<Cell> cellVec : displayGrid)   {
        for (Cell cell : cellVec)   {
            if (cell.getState() == true)    {
                life = true;
            }
        }
    }
    return life;
}

/**
 * Currently populates a referenced displayGrid with arbitrary numbers.
 * TODO: add random population / generation
 */
void populateCellGrid(vector<vector<Cell>> &displayGrid)
{
    for (int i = 0; i < 10; i++)    { //  10 is a magic number, basically the min y size
    vector<Cell> cellVec;
    displayGrid.push_back(cellVec);
        for (int j = 0; j < 20; j++){ //  20 is a magic number, basically the min x size
            Cell c;
            //  get random number for use in generation
            srand(time(NULL)*rand());  //  seed1
            int n = rand() % 2; //  has to either be 0 or 1, dead or alive
            if (n == 1)
            {
                c.setAlive();
            }

            displayGrid[i].push_back(c);
        }
    }
}

void displayCellGrid(vector<vector<Cell>> displayGrid)
{
    for (vector<Cell> cellVec : displayGrid)
    {
        cout << "\t\t";
        for (Cell cell : cellVec)
        {
            cout << cell.getState();
            //□ 
        }
        cout << endl;
    }
}
