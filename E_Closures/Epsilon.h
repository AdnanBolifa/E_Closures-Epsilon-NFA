#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Epsilon
{
public:
    Epsilon(std::string fileName, std::string word);

private:
    static const int MAX_SIZE = 25;
    int sizeOfAlpha;
    std::string states[MAX_SIZE];
    std::string alphabet[MAX_SIZE];
    std::string startState;
    std::string endState[MAX_SIZE];
    std::string transition_table[MAX_SIZE][MAX_SIZE];
    std::string fileName;
    std::string word;

    void FileSearch();
    void nextState();
    int NOL();
    bool ValidWord(std::string word);
    int removeSpaces(std::string str);
    void AddToArray(std::string(&arr)[MAX_SIZE], std::string temp);
    void AddTo2DArray(std::string(&arr)[MAX_SIZE][MAX_SIZE], std::string temp, int row);
};
