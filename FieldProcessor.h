#ifndef H_FIELD_PROCESSOR
#define H_FIELD_PROCESSOR

#include <vector>
#include <array>
#include <bitset>

class FieldProcessor
{
public:
    FieldProcessor();
    ~FieldProcessor();

    void newGenerationProcessing();

private:
    static const unsigned short rowsNum = 6;
    static const unsigned short colsNum = 10;

    std::vector<std::array<std::bitset<colsNum>, rowsNum>> generations;

    void makeFirstGeneration();
    void printField();
    void isAllCellsDie();
    bool compareTwoFields(std::array<std::bitset<colsNum>, rowsNum>& firstField, std::array<std::bitset<colsNum>, rowsNum>& secondField);
    void checkSameFieldBefore();
};

#endif // H_FIELD_PROCESSOR