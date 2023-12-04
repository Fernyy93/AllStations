#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>

class FileReader {
public:
    FileReader(const std::string& filename);
    std::vector<std::pair<std::string, bool>> readFile();

private:
    std::string filename;
};

#endif // FILEREADER_H
#pragma once
