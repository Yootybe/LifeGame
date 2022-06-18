#include <iostream>
#include <sstream>

#include "FieldProcessor.h"

enum nearLiveCells : unsigned short
{
    aliveCellsThreshold = 2,
    deadCellsThreshold = 3
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
    std::vector<bool> firstField(startPos, false);

    bool deadCells = false;

    for (unsigned short i = 0; i < rowsNum; i++)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        { 
            firstField.push_back(((rand() % 10 + 1) > 4) ? true : false);
            
            if (firstField.back())
                deadCells = true;
        }
        firstField.insert(firstField.end(), 2, false);
    }

    firstField.insert(firstField.end(), colsNum + 1, false);

    generations.push_back(std::move(firstField));

    if (!deadCells)
    {
        std::cout << "All cells die. Game over" << std::endl;
        checkGameStatus();
        exit(-1);
    }

    printField();
}

void FieldProcessor::printField()
{
    std::vector<bool>* curGen = &generations.back();
    std::stringstream ss;

    for (unsigned short i = startPos; i < endPos; i += 2)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            ss << std::to_string((*curGen)[i]);
            i++;
        }
        ss << std::endl;
    }
    std::cout << ss.str();
}

bool FieldProcessor::setCellStatus(unsigned short numOfLiveCellsAround, bool prevStatus)
{
    if (prevStatus)
    {
        if (numOfLiveCellsAround == nearLiveCells::aliveCellsThreshold || numOfLiveCellsAround == nearLiveCells::deadCellsThreshold)
            return true;
    }
    else
    {
        if (numOfLiveCellsAround == nearLiveCells::deadCellsThreshold)
        {
            bornCells++;
            return true;
        }
    }

    if (prevStatus)
        deadCells++;

    return false;
}

void FieldProcessor::newGenerationProcessing()
{
    std::vector<bool>* prevGen = &generations.back();
    std::vector<bool> currentCellsStatuses(startPos, false);

    bool deadCells = false;

    for (unsigned short i = startPos; i < endPos; i += 2)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            unsigned short numOfLiveCellsAround = (*prevGen)[i - colsNum - 3] + (*prevGen)[i - colsNum - 2] + (*prevGen)[i - colsNum - 1]
                + (*prevGen)[i - 1] + (*prevGen)[i + 1] + (*prevGen)[i + colsNum + 1] + (*prevGen)[i + colsNum + 2] + (*prevGen)[i + colsNum + 3];
            
            currentCellsStatuses.push_back(setCellStatus(numOfLiveCellsAround, (*prevGen)[i]));
            i++;

            if (currentCellsStatuses.back())
                deadCells = true;
        }
        currentCellsStatuses.insert(currentCellsStatuses.end(), 2, false);
    }

    currentCellsStatuses.insert(currentCellsStatuses.end(), colsNum + 1, false);

    generations.push_back(std::move(currentCellsStatuses));

    printField();

    if (!deadCells)
    {
        std::cout << "All cells die. Game over" << std::endl;
        checkGameStatus();
        exit(-1);
    }

    checkSameFieldBefore();
}

bool FieldProcessor::compareTwoFields(std::vector<bool>& firstField, std::vector<bool>& secondField)
{
    for (unsigned short i = startPos; i < endPos; i += 2)
    {
        for (unsigned short j = 0; j < colsNum; j++)
        {
            if (firstField[i] != secondField[i])
                return false;
            i++;
        }
    }
    return true;
}

void FieldProcessor::checkSameFieldBefore()
{
    auto rIt = generations.rbegin();
    if (compareTwoFields(*rIt, *(rIt++)))
    {
        std::cout << "Same cell. Game over" << std::endl;
        checkGameStatus();
        exit(-1);
    }

    for (; rIt != generations.rend(); rIt++)
    {
        if (compareTwoFields(generations.back(), *rIt))
        {
            std::cout << "Periodic configuration of cells. Game over" << std::endl;
            checkGameStatus();
            exit(-1);
        }
    }
}

void FieldProcessor::checkGameStatus()
{
    std::string status = "\nFor the entire game\nWas created " + std::to_string(generations.size()) + " generations\n";
    status += "Was born " + std::to_string(bornCells) + " cells\n";
    status += "Was died " + std::to_string(deadCells) + " cells\n";
    std::cout << status;
}