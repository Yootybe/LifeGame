#include <iostream>

#include "FieldProcessor.h"

enum nearLiveCells : unsigned short
{
    twoLiveCells = 2,
    threeLiveCells = 3
};

FieldProcessor::FieldProcessor()
{
    makeFirstGeneration();
}

FieldProcessor::~FieldProcessor()
{
    
}

void FieldProcessor::makeFirstGeneration()
{
    std::array<std::bitset<colsNum>, rowsNum> cellsStatuses;

    for (unsigned short i = 0; i < rowsNum; i++)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {   
            cellsStatuses[i][j] = false;

            if ((rand() % 10 + 1) > 3) // Random
                cellsStatuses[i][j] = true;
        }
    }
    generations.push_back(std::move(cellsStatuses));

    printField();
    isAllCellsDie();
}

void FieldProcessor::printField()
{
    for (auto const& rowElem : generations.back())
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            std::cout << rowElem[j];
        }
        std::cout << std::endl;
    }
}

bool FieldProcessor::setCellStatus(unsigned short numOfLiveCellsAround, bool prevStatus)
{
    if (prevStatus) 
    {
        if (numOfLiveCellsAround == nearLiveCells::twoLiveCells || numOfLiveCellsAround == nearLiveCells::threeLiveCells)
            return true;
    }
    else
    {
        if (numOfLiveCellsAround == nearLiveCells::threeLiveCells)
            return true;
    }
    return false;
}

void FieldProcessor::newGenerationProcessing()
{
    std::array<std::bitset<colsNum>, rowsNum>* prevGen = &generations.back();
    std::array<std::bitset<colsNum>, rowsNum> currentCellsStatuses;

    unsigned short numOfLiveCellsAround = 0;

    // Calculate corners values
    numOfLiveCellsAround = (*prevGen)[1][0] + (*prevGen)[1][1] + (*prevGen)[0][1];
    currentCellsStatuses[0][0] = setCellStatus(numOfLiveCellsAround, (*prevGen)[0][0]);

    numOfLiveCellsAround = (*prevGen)[1][colsNum - 1] + (*prevGen)[1][colsNum - 2] + (*prevGen)[0][colsNum - 2];
    currentCellsStatuses[0][colsNum - 1] = setCellStatus(numOfLiveCellsAround, (*prevGen)[0][colsNum - 1]);

    numOfLiveCellsAround = (*prevGen)[rowsNum - 2][0] + (*prevGen)[rowsNum - 2][1] + (*prevGen)[rowsNum - 1][1];
    currentCellsStatuses[rowsNum - 1][0] = setCellStatus(numOfLiveCellsAround, (*prevGen)[rowsNum - 1][0]);

    numOfLiveCellsAround = (*prevGen)[rowsNum - 1][colsNum - 2] + (*prevGen)[rowsNum - 2][colsNum - 2] + (*prevGen)[rowsNum - 2][colsNum - 1];
    currentCellsStatuses[rowsNum - 1][colsNum - 1] = setCellStatus(numOfLiveCellsAround, (*prevGen)[rowsNum - 1][colsNum - 1]);

    // Calculate left and right values
    for (unsigned short i = 1; i < rowsNum - 1; i++)
    {
        numOfLiveCellsAround = (*prevGen)[i - 1][0] + (*prevGen)[i - 1][1]
                    + (*prevGen)[i][1] + (*prevGen)[i + 1][1] + (*prevGen)[i + 1][0];
        currentCellsStatuses[i][0] = setCellStatus(numOfLiveCellsAround, (*prevGen)[i][0]);

        numOfLiveCellsAround = (*prevGen)[i - 1][colsNum - 1] + (*prevGen)[i - 1][colsNum - 2]
                    + (*prevGen)[i][colsNum - 2] + (*prevGen)[i + 1][colsNum - 2] + (*prevGen)[i + 1][colsNum - 1];
        currentCellsStatuses[i][colsNum - 1] = setCellStatus(numOfLiveCellsAround, (*prevGen)[i][colsNum - 1]);
    }

    // Calculate top and bottom values
    for (unsigned short j = 1; j < colsNum - 1; j++)
    {
        numOfLiveCellsAround = (*prevGen)[0][j - 1] + (*prevGen)[1][j - 1]
                    + (*prevGen)[1][j] + (*prevGen)[1][j + 1] + (*prevGen)[0][j + 1];
        currentCellsStatuses[0][j] = setCellStatus(numOfLiveCellsAround, (*prevGen)[0][j]);

        numOfLiveCellsAround = (*prevGen)[rowsNum - 1][j - 1] + (*prevGen)[rowsNum - 2][j - 1]
                    + (*prevGen)[rowsNum - 2][j] + (*prevGen)[rowsNum - 2][j + 1] + (*prevGen)[rowsNum - 1][j + 1];
        currentCellsStatuses[rowsNum - 1][j] = setCellStatus(numOfLiveCellsAround, (*prevGen)[rowsNum - 1][j]);
    }
    
    // Calculate middle values
    for (unsigned short i = 1; i < rowsNum - 1; i++)
    {
        for (unsigned short j = 1; j < colsNum - 1; j++)
        {
            numOfLiveCellsAround = (*prevGen)[i][j - 1] + (*prevGen)[i - 1][j - 1] + (*prevGen)[i - 1][j]
                + (*prevGen)[i - 1][j + 1] + (*prevGen)[i][j + 1] + (*prevGen)[i + 1][j + 1] + (*prevGen)[i + 1][j] 
                    + (*prevGen)[i + 1][j - 1];
            currentCellsStatuses[i][j] = setCellStatus(numOfLiveCellsAround, (*prevGen)[i][j]);
        }
    }
    generations.push_back(std::move(currentCellsStatuses));

    printField();
    isAllCellsDie();
    checkSameFieldBefore();
}

void FieldProcessor::isAllCellsDie() // TODO: Need to test with different rand()
{
    for (auto const& rowElem : generations.back())
    {
        if (rowElem.any())
            return;
    }

    std::cout << "All cells die. Game over" << std::endl;
    exit(-1);
}

bool FieldProcessor::compareTwoFields(std::array<std::bitset<colsNum>, rowsNum>& firstField, std::array<std::bitset<colsNum>, rowsNum>& secondField)
{
    for (unsigned short i = 0; i < rowsNum; i++)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            if (firstField[i][j] != secondField[i][j])
                return false;
        }
    }
    return true;
}

void FieldProcessor::checkSameFieldBefore()
{
    for (unsigned short i = 0; i < generations.size() - 1; i++)
    {
        if (compareTwoFields(generations.back(), generations[i]))
        {
            if (generations.size() - (i + 1) > 1)
            {
                std::cout << "Periodic configuration of cells. Game over" << std::endl;
            }
            else
            {
                std::cout << "Same cell. Game over" << std::endl;
            }
            exit(-1);
        }
    }
}