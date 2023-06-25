#include "Epsilon.h"

Epsilon::Epsilon(std::string fileName, std::string word)
{
    this->fileName = fileName;
    this->word = word;
    FileSearch();
    nextState();
}

void Epsilon::FileSearch()
{
    std::ifstream myfile(fileName);
    if (!myfile)
    {
        std::cout << "No such file";
    }
    else
    {
        std::string temp;
        getline(myfile, temp);
        AddToArray(states, temp);

        getline(myfile, temp);
        sizeOfAlpha = removeSpaces(temp);
        AddToArray(alphabet, temp);

        getline(myfile, temp);
        startState = temp;

        getline(myfile, temp);
        AddToArray(endState, temp);

        for (int i = 0; i < NOL() - 4; i++)
        {
            getline(myfile, temp);
            AddTo2DArray(transition_table, temp, i);
        }
    }
    myfile.close();
}

void Epsilon::nextState()
{
    if (ValidWord(word))
    {
        int rows = 0;
        int j = 0;
        std::string currentState = startState;
        for (int i = 0; i < word.length(); i++)
        {
            std::string temp = currentState;
            while (j != sizeOfAlpha)
            {
                if (alphabet[j] == std::string(1, word[i]))
                    currentState = transition_table[rows][j];
                j++;
            }
            if (temp != currentState)
            {
                rows++;
                j = 0;
            }
            j = 0;
        }
        std::cout << "Current state: " << currentState << "\n";
        if (currentState == endState[0])
            std::cout << "\tAccepted!..\n";
        else
            std::cout << "\tNot Accepted!..\n";
    }
}

int Epsilon::NOL()
{
    std::ifstream myFile(fileName);
    std::string line;
    int count = 0;
    while (!myFile.eof())
    {
        getline(myFile, line);
        count++;
    }
    myFile.close();
    return count;
}

bool Epsilon::ValidWord(std::string word)
{
    for (char c : word)
    {
        bool charIsValid = false;
        for (std::string validChar : alphabet)
        {
            if (c == validChar[0])
            {
                charIsValid = true;
                break;
            }
        }
        if (!charIsValid)
        {
            std::cout << c << ": is not a valid character!\n";
            return false;
        }
    }
    return true;
}

int Epsilon::removeSpaces(std::string str)
{
    size_t pos = str.find(' ');
    while (pos != std::string::npos)
    {
        str.replace(pos, 1, "");
        pos = str.find(' ');
    }
    return str.length();
}

void Epsilon::AddToArray(std::string(&arr)[MAX_SIZE], std::string temp)
{
    int j = 0;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] == ' ')
        {
            j++;
            continue;
        }
        arr[j] += temp[i];
    }
}

void Epsilon::AddTo2DArray(std::string(&arr)[MAX_SIZE][MAX_SIZE], std::string temp, int row)
{
    int j = 0;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] == ' ')
        {
            j++;
            continue;
        }
        arr[row][j] += temp[i];
    }
}