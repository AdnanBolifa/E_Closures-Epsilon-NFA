#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Epsilon
{
public:
    Epsilon(std::string fileName);

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
    int epsilon = 0;

    void FileSearch();
    void FindEclosure();
    int NOL();
    int removeSpaces(string str);
    void AddToArray(string(&arr)[MAX_SIZE], std::string temp);
    void AddTo2DArray(string(&arr)[MAX_SIZE][MAX_SIZE], std::string temp, int row);
    void PrintTransitionTable(string arr[MAX_SIZE][MAX_SIZE]);
    void nextState();
};
