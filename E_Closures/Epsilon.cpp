#include "Epsilon.h"
using namespace std;
Epsilon::Epsilon(std::string fileName)
{
    this->fileName = fileName;
    FileSearch();
    PrintTransitionTable(transition_table);
    FindEclosure();
}

void Epsilon::FileSearch()
{
    ifstream myfile(fileName);
    if (!myfile)
    {
        cout << "No such file";
        return;
    }
    string temp;
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
    myfile.close();
}
void Epsilon::nextState()
{

    string currentState = startState;
    string temp;
    string nextState = transition_table[0][epsilon];
    for (size_t i = 0; i < NOL() - 4; i++)
    {
        nextState = transition_table[i][epsilon];
        temp += nextState;
    }
    cout << endl;
}
void Epsilon::FindEclosure()
{
    int rows = 0;
    int j = 0;
   
    for (size_t i = 0; i < sizeOfAlpha; i++)
    {
        if (alphabet[i] == "E")
            epsilon = i;
    }
    nextState();
    for (size_t i = 0; i < NOL() - 4; i++)
    {
        if (transition_table[i][epsilon] == "-")
        {
            cout << "E-Closure of (" << states[i] << ") = {" << states[i]<< "}\n";
            continue;
        }
        cout << "E-Closure of (" << states[i] << ") = {"<< states[i]<<"," 
             << transition_table[i][epsilon] << ",}\n";
    }
}

int Epsilon::NOL()
{
    ifstream myFile(fileName);
    string line;
    int count = 0;
    while (!myFile.eof())
    {
        getline(myFile, line);
        count++;
    }
    myFile.close();
    return count;
}

int Epsilon::removeSpaces(string str)
{
    size_t pos = str.find(' ');
    while (pos != string::npos)
    {
        str.replace(pos, 1, "");
        pos = str.find(' ');
    }
    return str.length();
}

void Epsilon::AddToArray(string(&arr)[MAX_SIZE], string temp)
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

void Epsilon::AddTo2DArray(string(&arr)[MAX_SIZE][MAX_SIZE], string temp, int row)
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
void Epsilon::PrintTransitionTable(string array[MAX_SIZE][MAX_SIZE])
{
    cout << "Your Transition table from " + fileName <<" is: \n\n";
    cout << "   ";
    for (size_t i = 0; i < sizeOfAlpha; i++)
    {
        cout << alphabet[i] << " ";
    }cout << endl;
    for (size_t i = 1; i < (sizeOfAlpha * sizeOfAlpha); i++)
    {
        cout << "-";
    }cout << endl;
    for (size_t i = 0; i < NOL() - 4; i++)
    {
        cout << states[i] << "| ";
        for (size_t j = 0; j < sizeOfAlpha; j++)
        {
            cout << transition_table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------\n";
}