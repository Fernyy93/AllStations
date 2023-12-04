#include "include/file_reader.h"
#include "include/TrainStopSequenceAnalyzer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    

    // Read the train stop sequence data from the file directly into a vector
    FileReader fileReader("express.csv");
    std::vector<std::pair<std::string, bool>> stopSequence = fileReader.readFile();

    // Analyze the stop sequence and print the result
    TrainStopSequenceAnalyzer analyzer(stopSequence);
    std::string result = analyzer.analyzeStopSequence();

    std::cout << result << std::endl;

    return 0;
}
