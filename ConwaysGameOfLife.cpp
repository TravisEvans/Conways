#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h> // rand
#include <time.h>   //  time
#include <chrono>
#include <thread>

using namespace std;

#ifndef Conways
#include "Conways.h"
using namespace Conways;
#endif

// #ifdef _WIN32
// #include <Windows.h>    //  Windows
// #else
// #include <unistd.h> //  linux
// #endif

//  variables
int lifeCheckLimiter = 999;

// functions
void run(vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid);
bool checkForLife(vector<vector<Cell>> displayGrid);
void populateCellGrid(vector<vector<Cell>> &displayGrid);
void displayCellGrid(vector<vector<Cell>> displayGrid);
void gameStep(vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid);

//  constants
const int MS_PER_FRAME = 0; // milliseconds

/**
 * main function
 * @param none doesnt exist
 */
int main()
{
    vector<vector<Cell>> displayGrid;
    vector<vector<Cell>> calculationGrid;

    while (true)    {
        run(displayGrid, calculationGrid);  //  single instance of grids
        // this_thread::sleep_for(chrono::milliseconds(MS_PER_FRAME));
    }

    return 0;
}

void run(vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid)
{
    if (!checkForLife(displayGrid))    {   //  so, if there is no life, do...
        populateCellGrid(displayGrid);   //  populate dead grid
    }
    system("clear");    //  with stepping, will clear screen
    cout << "\n\n\n" << endl;

    displayCellGrid(displayGrid); //  see how life is going
    cout << endl;
    gameStep(displayGrid, calculationGrid);    //  step

    cout << "\n\n\n" << endl;
}

bool checkForLife(vector<vector<Cell>> displayGrid)    {   //  check if life has ended (recursion reasons)
    if (lifeCheckLimiter >= 100)    {
        for (vector<Cell> cellVec : displayGrid)   {
            for (Cell cell : cellVec)   {
                if (cell.getState() == true)    {
                    lifeCheckLimiter = 0;
                    return true;    //  life exists
                }
            }
        }

        return false;   //  lifen't
    }
    lifeCheckLimiter++;
    return true;    //  there is assumed to be life here
}

/**
 * Currently randomly populates a referenced displayGrid with "life" cells
 */
void populateCellGrid(vector<vector<Cell>> &displayGrid)
{
    displayGrid.clear();
    for (int i = 0; i < 50; i++)    { //  10 is a magic number, basically the min y size
    vector<Cell> cellVec;
    displayGrid.push_back(cellVec);
        for (int j = 0; j < 100; j++){ //  20 is a magic number, basically the min x size
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
    cout << "\t\t ";  // border top
    for (int i = 0; i < (int)displayGrid[0].size(); i++)
        cout << "-";
    cout << endl;
    
    for (vector<Cell> cellVec : displayGrid)
    {
        cout << "\t\t|";    //  border left
        for (Cell cell : cellVec)
        {   
            if (cell.getState() == true)
                cout << "o";
            if (cell.getState() == false)
                cout << " ";
        }
        cout << "|";    //  border right
        cout << endl;
    }
    cout << "\t\t "; // border bottom
    for (int i = 0; i < (int)displayGrid[0].size(); i++)
        cout << "-";
}
