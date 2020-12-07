#ifndef SAVES_HPP
#define SAVES_HPP

#include <string>
#include <vector>

class Saves {
    std::string savePath;

    std::vector<int> scores;
    const int MAX_NUM = 10;
public:
    Saves(std::string filename);

    void addScore(int value);

    std::vector<int> getScores(int num);

    void saveToFile();
};

#endif
