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
void run(vector<vector<Cell>> cellGrid);
bool checkForLife(vector<vector<Cell>> cellGrid);
void populateCellGrid(vector<vector<Cell>> &cellGrid);
void displayCellGrid(vector<vector<Cell>> cellGrid);

/**
 * main function
 * @param none doesnt exist
 */
int main()  {
    vector<vector<Cell>> cellGrid;

    run(cellGrid);  //  single instance of grid

    return 0;
}

void run(vector<vector<Cell>> cellGrid)
{
    if (!checkForLife(cellGrid))    {   //  so, if there is no life, do...
        populateCellGrid(cellGrid);   //  populate dead grid
    }

    displayCellGrid(cellGrid);     //  see how life is going
}

bool checkForLife(vector<vector<Cell>> cellGrid)    {   //  check if life has ended (recursion reasons)
    bool life = false;
    for (vector<Cell> cellVec : cellGrid)   {
        for (Cell cell : cellVec)   {
            if (cell.getState() == true)    {
                life = true;
            }
        }
    }
    return life;
}

/**
 * Currently populates a referenced cellGrid with arbitrary numbers.
 * TODO: add random population / generation
 */
void populateCellGrid(vector<vector<Cell>> &cellGrid)
{
    for (int i = 0; i < 20; i++)    { //  20 is a magic number, basically the min y size
    vector<Cell> cellVec;
    cellGrid.push_back(cellVec);
        for (int j = 0; j < 40; j++){ //  40 is a magic number, basically the min x size
            Cell c;
            //  get random number for use in generation
            srand(time(NULL)*rand());  //  seed1
            int n = rand() % 2; //  has to either be 0 or 1, dead or alive
            if (n == 1)
            {
                c.setAlive();
            }

            cellGrid[i].push_back(c);
        }
    }
}

void displayCellGrid(vector<vector<Cell>> cellGrid)
{
    for (vector<Cell> cellVec : cellGrid)
    {
        for (Cell cell : cellVec)
        {
            cout << cell.getState();
        }
        cout << endl;
    }
}