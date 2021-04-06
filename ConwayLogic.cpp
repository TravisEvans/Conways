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
void populateCalculationGrid(int cellX, int cellY, int (&cluster)[3][3], vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid);
void displayCalculationGrid(vector<vector<Cell>> calculationGrid);
void replaceDisplay(vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid);

void gameStep(vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid)
{
    resizeCalculationGrid(displayGrid[0].size(), displayGrid.size(), calculationGrid);  //  makes grids same size

    iterateThroughBothGrids(displayGrid, calculationGrid);
    replaceDisplay(displayGrid, calculationGrid);
    // displayCalculationGrid(calculationGrid); //  mainly for testing
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
            calculateCell(x, y, displayGrid, calculationGrid);
        }
    }
}

void calculateCell(int cellX, int cellY, vector<vector<Cell>> displayGrid, vector<vector<Cell>> &calculationGrid)
{
    //  get real values from displayGrid into cluster[][] and send elsewhere to populate calculationGrid
    int cluster[3][3] = {   
        {0, 0, 0},  // 0,1,2
        {0, 0, 0},  // 3,4,5
        {0, 0, 0}}; // 6,7,8
    for (int ymod = 0; ymod < 3; ymod++) {
        //  holder for cell + neighbours

        for (int xmod = 0; xmod < 3; xmod++) {

            if ((cellY + (ymod-1)) < 0 ||
                (signed int)(cellY + (ymod-1)) > (signed int)(displayGrid.size()-1) ||   // fuck .size() and stupid seg faults
                (cellX + (xmod-1)) < 0 ||
                (signed int)(cellX + (xmod-1)) > (signed int)(displayGrid[0].size()-1))      //  why the fuck does this .size() work????? I even triple checked?!?!?!?
            {
                cluster[1+(ymod-1)][1+(xmod-1)] = 0;
                // cout << cluster[1+(ymod-1)][1+(xmod-1)] << "|";
            }
            else
            {
                // bool life = displayGrid[cellY+(ymod-1)][cellX+(xmod-1)].getState();
                // cout << displayGrid[cellY+(ymod-1)][cellX+(xmod-1)].getState() << "\t" << life << endl;
                // life == true ? cluster[1+(ymod-1)][1+(xmod-1)] = 1 : cluster[1+(ymod-1)][1+(xmod-1)] = 0;
                cluster[1+(ymod-1)][1+(xmod-1)] = displayGrid[cellY+(ymod-1)][cellX+(xmod-1)].getState();
                // cout << cluster[1+(ymod-1)][1+(xmod-1)] << "|";
                // cout << life << endl;
            }
        }

    }
    populateCalculationGrid(cellX, cellY, cluster, displayGrid, calculationGrid);    //  aforementioned 'elsewhere'
    // cout << "cluster values for " << cellY << cellX << ":\n" << cluster[0][0] << "|" << cluster[0][1] << "|" << cluster[0][2] << "|\n" << cluster[1][0] << "|" << cluster[1][1] << "|" <<  cluster[1][2] << "|\n" << cluster[2][0] << "|" << cluster[2][1] << "|" << cluster[2][2] << "|" << endl;
    // cout << "total neighbours:\t " << (cluster[0][0] + cluster[0][1] + cluster[0][2] +
    //                                       cluster[1][0] + /*    cell + */ cluster[1][2] + cluster[2][0] + cluster[2][1] + cluster[2][2]) << endl;
    //  UP TO HERE IS GOOD
}

void populateCalculationGrid(int cellX, int cellY, int (&cluster)[3][3], vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid)
{
    //  this is where the rules come in, calculated from the cluster
    //  remember, ignore cluster[1][1]
    int neighbours = cluster[0][0] + cluster[0][1] + cluster[0][2] + // this is the issue ERROR
                         cluster[1][0] + /*    cell + */ cluster[1][2] + 
                         cluster[2][0] + cluster[2][1] + cluster[2][2];

    // cout << "cluster values for " << cellY << cellX << ":\n" << cluster[0][0] << "|" << cluster[0][1] << "|" << cluster[0][2] << "|\n" << cluster[1][0] << "|" << cluster[1][1] << "|" <<  cluster[1][2] << "|\n" << cluster[2][0] << "|" << cluster[2][1] << "|" << cluster[2][2] << "|" << endl;
    // cout << "total neighbours:\t " << (cluster[0][0] + cluster[0][1] + cluster[0][2] +
    //                                       cluster[1][0] + /*    cell + */ cluster[1][2] + cluster[2][0] + cluster[2][1] + cluster[2][2]) << endl;

    //  rule 1. if <2 neighbours, then die
    //  rule 2. if 2 or 3 neighbours, then stay the same
    //  rule 3. if 3 neighbours, then become alive (from dead)
    //  rule 4. if >3 neighbours, then die
    

    if (neighbours < 2) {
        calculationGrid[cellY][cellX].setDead();
    } else if (neighbours > 3)  {
        calculationGrid[cellY][cellX].setDead();
    } else if (neighbours == 3)  {
        calculationGrid[cellY][cellX].setAlive();
    } else if (neighbours == 2 && (displayGrid[cellY][cellX].getState() == true))    {
        calculationGrid[cellY][cellX].setAlive();
    }
}

void displayCalculationGrid(vector<vector<Cell>> calculationGrid)
{
    for (vector<Cell> cellVec : calculationGrid)    {
        cout << "\t\t";
        for (Cell c : cellVec)  {
            if (c.getState() == true)
                cout << "□"; //□
            else
                cout << "x";
        }
        cout << endl;
    }
}

void replaceDisplay(vector<vector<Cell>> &displayGrid, vector<vector<Cell>> &calculationGrid)   {
    for (int i = 0; i < (int)displayGrid.size(); i++)   {
        for (int j =0; j < (int)displayGrid[0].size(); j++)  {

            displayGrid[i][j] = calculationGrid[i][j];
                   
        }
    }
}