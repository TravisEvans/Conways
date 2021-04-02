#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#ifndef Conways
#include "Conways.h"
#endif

using namespace Conways;

//  declarations
void resizeCalculationGrid(int displaySizeX, int displaySizeY, vector<vector<Cell>> &calculationGrid);
void iterateThroughBothGrids(vector<vector<Cell>> displayGrid, vector<vector<Cell>> &calculationGrid);
void calculateCell(int cellX, int cellY, vector<vector<Cell>> displayGrid, vector<vector<Cell>> &calculationGrid);
void displayCalculationGrid(vector<vector<Cell>> calculationGrid);

void gameStep(vector<vector<Cell>> displayGrid, vector<vector<Cell>> calculationGrid)
{
    resizeCalculationGrid(displayGrid[0].size(), displayGrid.size(), calculationGrid);  //  makes grids same size

    iterateThroughBothGrids(displayGrid, calculationGrid);
    // calculateCell();
    displayCalculationGrid(calculationGrid);
}

void resizeCalculationGrid(int displaySizeX, int displaySizeY, vector<vector<Cell>> &calculationGrid)
{
    calculationGrid.resize(displaySizeY);
    for (vector<Cell> &cellVec : calculationGrid)
    {   
        cellVec.resize(displaySizeX);
    }
}

void iterateThroughBothGrids(vector<vector<Cell>> displayGrid, vector<vector<Cell>> &calculationGrid)
{   
    //  x and y are what has been checked
    for (long unsigned int y = 0; y < displayGrid.size(); y++)    {
        for (long unsigned int x = 0; x < displayGrid[0].size(); x++) {
            calculateCell(x, y, displayGrid, calculationGrid);   //  ERROR
        }
    }
}

void calculateCell(int cellX, int cellY, vector<vector<Cell>> displayGrid, vector<vector<Cell>> &calculationGrid)
{
    //  make array of cell and neighbours where
    /*
        0,  0, 0
        0,cell,0
        0,  0, 0
    */

    //  holder for cell + neighbours
    int cluster[3][3] = {   
        {0, 0, 0},  // 0,1,2
        {0, 0, 0},  // 3,4,5
        {0, 0, 0}}; // 6,7,8

    //  get real values from displayGrid into cluster[][]
    for (int ymod = 0; ymod < 3; ymod++) {
        for (int xmod = 0; xmod < 3; xmod++) {
            // try {
            //     cluster[1+(ymod-1)][1+(xmod-1)] = displayGrid[cellY+ymod][cellX+xmod].getState();   //  ERROR
            // } catch (...)   {
            //     cluster[1+ymod][1+xmod] = 0;
            // }
            // if (displayGrid[cellY + ymod][cellX + xmod].getState() == NULL) {
            //     // cout << "hit if" << endl;
            //     cluster[1+ymod][1+xmod] = 0;
            // } else  {
            //     // cout << "hit else" << endl;
            //     cluster[1+(ymod-1)][1+(xmod-1)] = displayGrid[cellY+ymod][cellX+xmod].getState();   //  FIXME
            // }

            if (cellY + (ymod-1) < 0 ||
                (unsigned long int)(cellY + (ymod-1)) > (displayGrid.size()-1) ||   // fuck .size()
                cellX + (xmod-1) < 0 ||
                (unsigned long int)(cellX + (xmod-1)) > displayGrid[0].size())
            {
                cout << "hit if" << endl;
                cluster[1+(ymod-1)][1+(xmod-1)] = 0;
            }
            else
            {
                cluster[1+(ymod-1)][1+(xmod-1)] = displayGrid[cellY+(ymod-1)][cellX+(xmod-1)].getState();
            }

        // cout << "hit after" << endl;
        }
    }

    //  display the above, for testing reasons
    cout << endl;
    cout << cluster[0][0];
    cout << cluster[0][1];
    cout << cluster[0][2];
    cout << endl;
    cout << cluster[1][0];
    cout << cluster[1][1];
    cout << cluster[1][2];
    cout << endl;
    cout << cluster[2][0];
    cout << cluster[2][1];
    cout << cluster[2][2];
    cout << endl;
}

void displayCalculationGrid(vector<vector<Cell>> calculationGrid)
{
    for (vector<Cell> cellVec : calculationGrid)    {
        cout << "\t\t";
        for (Cell c : cellVec)  {
            cout << c.getState();
        }
        cout << endl;
    }
}