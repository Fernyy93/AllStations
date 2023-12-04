#include "include/TrainStopSequenceAnalyzer.h"
#include <iostream>

TrainStopSequenceAnalyzer::TrainStopSequenceAnalyzer(const std::vector<std::pair<std::string, bool>>& stopSequence)
    : stopSequence(stopSequence) {}

std::string TrainStopSequenceAnalyzer::analyzeStopSequence() {
    // Starting output string
    std::string result = "This train ";

    // Vectors to record the express stations and intermediate stations in an express section
    std::vector<std::pair<std::string, bool>> expressSection;
    std::vector<std::pair<std::string, bool>> intermediateStops;

    size_t numStations = stopSequence.size();
    
    std::cout << numStations << std::endl;
    // Throw an error if there is less than 2 stations in the sequence
    if (numStations < 2) {
        std::cerr << "Error: Train stop sequence must contain at least two stations." << std::endl;
        return result;
    }
    // Case 1: only 2 stations in the sequence
    else if (numStations == 2) {
        result += "stops at " + stopSequence[0].first + " and " + stopSequence[1].first + " only.";
        return result;
    }
    
    else if (numStations > 2){
        bool stoppingAtAllStations = true;
        bool hasExpressSection = false;
        bool countExpressStart = true;
        size_t expressStart = 0;
        size_t expressEnd = 0;
        size_t numExpress = 0;        
        
        for (size_t i = 1; i < numStations - 1; i++) {
            // First check if the train skips a station and set the flag hasExpressSection to true
            if (!stopSequence[i].second) {
                hasExpressSection = true;
                // Then record the start of the express section and do not update in further iterations by using the flag countExpressStart
                if (countExpressStart) {
                    expressStart = i - 1;
                    countExpressStart = false;
                }
                
            }
            if (hasExpressSection) {
                // The rest of the cases only occur if the train does not stop at all stations
                stoppingAtAllStations = false;
                std::cout << stopSequence[i].second << std::endl;
                std::cout << "This train skipped " + stopSequence[i].first << std::endl;
                std::cout << "The express section starts at " + stopSequence[expressStart].first << std::endl;
                numExpress++;
                // From this point on, any stations the train skips are express, any stations the train stops at are intermediate
                if (!stopSequence[i].second) {
                    expressSection.emplace_back(stopSequence[i].first, stopSequence[i].second);
                }
                else {
                    intermediateStops.emplace_back(stopSequence[i].first, stopSequence[i].second);
                }
                
                
            }

        }

        // Analyze and build the result string based on the train's stop sequence
        // If the stoppingAtAll stations flag is still true, print the result
        // Case 2: stops at all stations
        if (stoppingAtAllStations) {
            result += "stops at all stations";
        }
        // Case 3: train skips a single station
        // If only one station was skipped.
        else if (numExpress == 1) {
            result += "stops at all stations except " + expressSection[0].first;
        }
        // Case 4: Has an express section.
        // Perform further analysis if there is an express section
        else if ((numExpress + intermediateStops.size()) > 1) {
            // error checking printout
            for (const auto& station : expressSection) {
                std::cout << "express: " << station.first << std::endl;
            }
            // another error checking printout
            for (const auto& station : intermediateStops) {
                std::cout << "intermediate: " << station.first << std::endl;
            }
            // add the station at the left hand side of the express station to the result
            result += "runs express from " + stopSequence[expressStart].first;
            std::cout << result << std::endl;
            result += " to ";
            std::cout << result << std::endl;
            // the formula for the station at the right hand side of the express section is: expressStart index + number of express stations + number of intermediate stations
            result += stopSequence[expressStart + numExpress + intermediateStops.size()].first;
            // Case 4a: Has an express section with a single intermediate stop
            if (intermediateStops.size() >= 1) {
                // we are only assuming there is a single intermediate stop
                result += ", stopping only at " + intermediateStops[0].first;
            }
            // Case 4b: Has a second express section.... I am not smart enough to figure that one out
            
        }
        
    }

    
    // the exit door is on the right hand side in the direction of travel
    return result;
}
