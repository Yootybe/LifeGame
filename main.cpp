#include <vector>
#include <iostream>
#include <array>
#include <bitset>

static const unsigned short rowsNum = 6;
static const unsigned short colsNum = 10;

enum nearLiveCells : unsigned short
{
    twoLiveCells = 2,
    threeLiveCells = 3
};

std::vector<std::array<std::bitset<colsNum>, rowsNum>> generations;

void makeFirstGeneration()
{
    std::array<std::bitset<colsNum>, rowsNum> cellsStatuses;

    for(unsigned short i = 0; i < rowsNum; i++)
    {
        for(unsigned short j = 0; j < colsNum; j++)
        {   
            cellsStatuses[i][j] = false;

            if ((rand() % 10 + 1) > 9) // Random
                cellsStatuses[i][j] = true;
        }
    }
    generations.push_back(std::move(cellsStatuses));
}

void printField()
{
    for (auto const& rowElem : generations.back())
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            std::cout << rowElem[j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void newGenerationProcessing(std::array<std::bitset<colsNum>, rowsNum>& prevGen)
{
    std::array<std::bitset<colsNum>, rowsNum> currentCellsStatuses;

    unsigned short numOfLiveCellsAround = 0;
    bool isNumOfLiveCellsAroundCalculated = false;

    for(unsigned short i = 0; i < rowsNum; i++)
    {
        for(unsigned short j = 0; j < colsNum; j++)
        {
            if (i == 0 && j == 0)
            {
                numOfLiveCellsAround += prevGen[i + 1][j] + prevGen[i + 1][j + 1] + prevGen[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == 0 && j == colsNum)
            {
                numOfLiveCellsAround += prevGen[i][j - 1] + prevGen[i + 1][j - 1] + prevGen[i + 1][j];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == rowsNum && j == 0)
            {
                numOfLiveCellsAround += prevGen[i - 1][j] + prevGen[i - 1][j + 1] + prevGen[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == rowsNum && j == colsNum)
            {
                numOfLiveCellsAround += prevGen[i - 1][j] + prevGen[i - 1][j - 1] + prevGen[i][j - 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == 0)
            {
                numOfLiveCellsAround += prevGen[i][j - 1] + prevGen[i + 1][j - 1]
                    + prevGen[i + 1][j] + prevGen[i + 1][j + 1] + prevGen[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == rowsNum - 1)
            {
                numOfLiveCellsAround += prevGen[i][j - 1] + prevGen[i - 1][j - 1]
                    + prevGen[i - 1][j] + prevGen[i - 1][j + 1] + prevGen[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (j == 0)
            {
                numOfLiveCellsAround += prevGen[i - 1][j] + prevGen[i - 1][j + 1]
                    + prevGen[i][j + 1] + prevGen[i + 1][j + 1] + prevGen[i + 1][j];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (j == colsNum - 1)
            {
                numOfLiveCellsAround += prevGen[i - 1][j] + prevGen[i - 1][j - 1]
                    + prevGen[i][j - 1] + prevGen[i + 1][j - 1] + prevGen[i + 1][j];
                isNumOfLiveCellsAroundCalculated = true;
                // std::cout << numOfLiveCellsAround;
            }

            if (!isNumOfLiveCellsAroundCalculated)
            {
                numOfLiveCellsAround += prevGen[i][j - 1] + prevGen[i - 1][j - 1] + prevGen[i - 1][j]
                + prevGen[i - 1][j + 1] + prevGen[i][j + 1] + prevGen[i + 1][j + 1] + prevGen[i + 1][j] 
                    + prevGen[i + 1][j - 1];
            }
            
            currentCellsStatuses[i][j] = false;
            if (prevGen[i][j]) 
            {
                if (numOfLiveCellsAround == nearLiveCells::twoLiveCells || numOfLiveCellsAround == nearLiveCells::threeLiveCells)
                    currentCellsStatuses[i][j] = true;
            }
            else
            {
                if (numOfLiveCellsAround == nearLiveCells::threeLiveCells)
                    currentCellsStatuses[i][j] = true;
            }

            numOfLiveCellsAround = 0;
            isNumOfLiveCellsAroundCalculated = false;
        }
    }
    generations.push_back(std::move(currentCellsStatuses));
}

int main()
{
    makeFirstGeneration();
    printField();
    
    newGenerationProcessing(generations.back());
    printField();

    return 0;
}