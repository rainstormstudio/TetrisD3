#include "saves.hpp"
#include <algorithm>
#include "math.hpp"
#include <fstream>
#include <iostream>

Saves::Saves(std::string filename) {
    savePath = filename;
    scores = std::vector<int>(MAX_NUM, 0);
    if (filename.empty()) return;

    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line == "") continue;
            int len = line.length();
            int score = 0;
            if (Math::isNat(line)) {
                score = std::stoi(line);
            }
            if (0 <= score && score <= 999999) {
                addScore(score);
            }
        }
        infile.close();
    } else {
        saveToFile();
    }
}

void Saves::addScore(int value) {
    scores.push_back(value);
    std::sort(scores.begin(), scores.end(), [](int a, int b){return a > b;});
    scores.resize(MAX_NUM);
}

std::vector<int> Saves::getScores(int num) {
    std::vector<int> ans;
    for (int i = 0; i < num && i < scores.size(); i ++) {
        ans.push_back(scores[i]);
    }
    return ans;
}

void Saves::saveToFile() {
    std::ofstream output(savePath);
    if (output.is_open()) {
        for (auto score : scores) {
            output << score << std::endl;
        }
        output.close();
    } else {
        std::cerr << "Failed to open save file: " << savePath << std::endl;
    }
}