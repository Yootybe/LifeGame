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

void FieldProcessor::newGenerationProcessing()
{
    std::array<std::bitset<colsNum>, rowsNum>* prevGen = &generations.back();
    std::array<std::bitset<colsNum>, rowsNum> currentCellsStatuses;

    unsigned short numOfLiveCellsAround = 0;
    bool isNumOfLiveCellsAroundCalculated = false;

    for (unsigned short i = 0; i < rowsNum; i++)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            // TODO: Bad algorithm, maybe need to use switch another idea
            if (i == 0 && j == 0)
            {
                numOfLiveCellsAround += (*prevGen)[i + 1][j] + (*prevGen)[i + 1][j + 1] + (*prevGen)[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == 0 && j == colsNum)
            {
                numOfLiveCellsAround += (*prevGen)[i][j - 1] + (*prevGen)[i + 1][j - 1] + (*prevGen)[i + 1][j];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == rowsNum && j == 0)
            {
                numOfLiveCellsAround += (*prevGen)[i - 1][j] + (*prevGen)[i - 1][j + 1] + (*prevGen)[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == rowsNum && j == colsNum)
            {
                numOfLiveCellsAround += (*prevGen)[i - 1][j] + (*prevGen)[i - 1][j - 1] + (*prevGen)[i][j - 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == 0 && !isNumOfLiveCellsAroundCalculated)
            {
                numOfLiveCellsAround += (*prevGen)[i][j - 1] + (*prevGen)[i + 1][j - 1]
                    + (*prevGen)[i + 1][j] + (*prevGen)[i + 1][j + 1] + (*prevGen)[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (i == rowsNum - 1 && !isNumOfLiveCellsAroundCalculated)
            {
                numOfLiveCellsAround += (*prevGen)[i][j - 1] + (*prevGen)[i - 1][j - 1]
                    + (*prevGen)[i - 1][j] + (*prevGen)[i - 1][j + 1] + (*prevGen)[i][j + 1];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (j == 0 && !isNumOfLiveCellsAroundCalculated)
            {
                numOfLiveCellsAround += (*prevGen)[i - 1][j] + (*prevGen)[i - 1][j + 1]
                    + (*prevGen)[i][j + 1] + (*prevGen)[i + 1][j + 1] + (*prevGen)[i + 1][j];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (j == colsNum - 1 && !isNumOfLiveCellsAroundCalculated)
            {
                numOfLiveCellsAround += (*prevGen)[i - 1][j] + (*prevGen)[i - 1][j - 1]
                    + (*prevGen)[i][j - 1] + (*prevGen)[i + 1][j - 1] + (*prevGen)[i + 1][j];
                isNumOfLiveCellsAroundCalculated = true;
            }

            if (!isNumOfLiveCellsAroundCalculated)
            {
                numOfLiveCellsAround += (*prevGen)[i][j - 1] + (*prevGen)[i - 1][j - 1] + (*prevGen)[i - 1][j]
                + (*prevGen)[i - 1][j + 1] + (*prevGen)[i][j + 1] + (*prevGen)[i + 1][j + 1] + (*prevGen)[i + 1][j] 
                    + (*prevGen)[i + 1][j - 1];
            }
            
            currentCellsStatuses[i][j] = false;
            if ((*prevGen)[i][j]) 
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

    printField();
    isAllCellsDie();
    checkSameFieldBefore();
}

void FieldProcessor::isAllCellsDie() // TODO: Need to test with different rand()
{
    for (auto const& rowElem : generations.back())
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            if (rowElem[j])
                return;
        }
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