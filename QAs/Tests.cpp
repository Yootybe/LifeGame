#include <gtest/gtest.h>

#include "FieldProcessor.h"

static const unsigned short rowsNum = 6;
static const unsigned short colsNum = 10;

class FieldProcessorTest
{
public:
    FieldProcessorTest() {};
    ~FieldProcessorTest() {};

    void pushGeneration(FieldProcessor& fp, std::array<std::bitset<colsNum>, rowsNum>& generation)
    {
        fp.generations.push_back(std::move(generation));
    }
    
    void processNextGeneration(FieldProcessor& fp)
    {
        fp.newGenerationProcessing();
    }

    bool compareExpectedGeneration(FieldProcessor& fp, std::array<std::bitset<colsNum>, rowsNum>& generation)
    {
        return fp.compareTwoFields(fp.generations.back(), generation);
    }
};

TEST(fieldprocessor, test1)
{
    FieldProcessor fp;
    FieldProcessorTest fpt;

    std::array<std::bitset<colsNum>, rowsNum> firstGeneration;
    firstGeneration[0] = {0b1010101000};
    firstGeneration[1] = {0b0000110101};
    firstGeneration[2] = {0b1001000010};
    firstGeneration[3] = {0b0010110001};
    firstGeneration[4] = {0b0100000001};
    firstGeneration[5] = {0b0101001000};

    std::array<std::bitset<colsNum>, rowsNum> expectedSecondGeneration;
    expectedSecondGeneration[0] = {0b0001101000};
    expectedSecondGeneration[1] = {0b0100111110};
    expectedSecondGeneration[2] = {0b0001001011};
    expectedSecondGeneration[3] = {0b0111100011};
    expectedSecondGeneration[4] = {0b0101110000};
    expectedSecondGeneration[5] = {0b0010000000};

    fpt.pushGeneration(fp, firstGeneration);

    std::cout << std::endl;

    fpt.processNextGeneration(fp);

    EXPECT_EQ(fpt.compareExpectedGeneration(fp, expectedSecondGeneration), true);
}