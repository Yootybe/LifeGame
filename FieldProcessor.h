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

    std::vector<std::vector<bool>> generations;

    // Because real vector starts with zeroes and ends with zeroes by calculation algorithm
    static const unsigned short startPos = colsNum + 2 + 1;
    static const unsigned short endPos = ((colsNum + 2) * (rowsNum + 2)) - colsNum - 2;

    bool setCellStatus(unsigned short numOfLiveCellsAround, bool prevStatus);
    void makeFirstGeneration();
    void printField();
    bool compareTwoFields(std::vector<bool>& firstField, std::vector<bool>& secondField);
    void checkSameFieldBefore();
};

#endif // H_FIELD_PROCESSOR