#ifndef TRAIN_STOP_SEQUENCE_ANALYZER_H
#define TRAIN_STOP_SEQUENCE_ANALYZER_H

#include <vector>
#include <string>

class TrainStopSequenceAnalyzer {
public:
    TrainStopSequenceAnalyzer(const std::vector<std::pair<std::string, bool>>& stopSequence);
    std::string analyzeStopSequence();

private:
    std::vector<std::pair<std::string, bool>> stopSequence;
};

#endif // TRAIN_STOP_SEQUENCE_ANALYZER_H
#pragma once
