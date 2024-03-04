#include <gtest/gtest.h>

#include <filesystem>
#include <memory>
#include <vector>

#include <lab1.hpp>

namespace fs = std::filesystem;

void testingProgram(const std::vector<std::string> &input, const std::vector<std::string> &expectedOutput1, const std::vector<std::string> &expectedOutput2) {
    const char *fileWithOutput1 = "output1.txt";
    const char *fileWithOutput2 = "output2.txt";

    std::stringstream inFile;
    inFile << fileWithOutput1 << std::endl;
    inFile << fileWithOutput2 << std::endl;
    for (std::string line : input) {
        inFile << line << std::endl;
    }

    std::streambuf* oldInBuf = std::cin.rdbuf(inFile.rdbuf());

    ASSERT_TRUE(fs::exists("/home/test/Desktop/os-labs/build/lab1/child-lab1"));

    ParentRoutine("/home/test/Desktop/os-labs/build/lab1/child-lab1");
    std::cin.rdbuf(oldInBuf);
    
    auto outFile1 = std::ifstream(fileWithOutput1);
    auto outFile2 = std::ifstream(fileWithOutput2);
    if (!outFile1.is_open()) {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }
    for (const std::string &line : expectedOutput1) {
        std::string result;
        getline(outFile1, result);
        EXPECT_EQ(result, line);
    }
    outFile1.close();

    if (!outFile2.is_open()) {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }
    for (const std::string &line : expectedOutput2) {
        std::string result;
        getline(outFile2, result);
        EXPECT_EQ(result, line);
    }
    outFile2.close();
}

TEST(firstLabTests, emptyTest) {
    std::vector<std::string> input = {};

    std::vector<std::string> expectedOutput1 = {};

    std::vector<std::string> expectedOutput2 = {};

    testingProgram(input, expectedOutput1, expectedOutput2);
}

TEST(firstLabTests, firstSimpleTest) {
    std::vector<std::string> input = {
        "01",
        "02",
        "001",
        "002"
    };

    std::vector<std::string> expectedOutput1 = {
        "10",
        "20"
    };

    std::vector<std::string> expectedOutput2 = {
        "100",
        "200"
    };

    testingProgram(input, expectedOutput1, expectedOutput2);
}

TEST(firstLabTests, secondSimpleTest) {
    std::vector<std::string> input = {
            "This test has only",
            "one output file."
    };

    std::vector<std::string> expectedOutput1 = {
            "ylno sah tset sihT",
            ".elif tuptuo eno"
    };

    std::vector<std::string> expectedOutput2 = {};


    testingProgram(input, expectedOutput1, expectedOutput2);
}

TEST(firstLabTests, thirdSimpleTest) {
    std::vector<std::string> input = {
            "The length of this string is even,",
            "but the length of this string isn't even.",
            "There are 37 characters in this line,",
            "but there are already as many as 60 characters in this line!"
    };

    std::vector<std::string> expectedOutput1 = {
            ",neve si gnirts siht fo htgnel ehT",
            "!enil siht ni sretcarahc 06 sa ynam sa ydaerla era ereht tub"
    };

    std::vector<std::string> expectedOutput2 = {
            ".neve t'nsi gnirts siht fo htgnel eht tub",
            ",enil siht ni sretcarahc 73 era erehT"
    };


    testingProgram(input, expectedOutput1, expectedOutput2);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
