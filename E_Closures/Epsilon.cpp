#include "Epsilon.h"
#include <sstream>
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
    while (getline(myfile, temp))
    {
        if (temp[0] == '#') // Ignore lines starting with '#'
            continue;
        AddToArray(states, temp);
        break;
    }

    while (getline(myfile, temp))
    {
        if (temp[0] == '#') // Ignore lines starting with '#'
            continue;
        sizeOfAlpha = removeSpaces(temp);
        AddToArray(alphabet, temp);
        break;
    }

    while (getline(myfile, temp))
    {
        if (temp[0] == '#') // Ignore lines starting with '#'
            continue;
        startState = temp;
        break;
    }

    while (getline(myfile, temp))
    {
        if (temp[0] == '#') // Ignore lines starting with '#'
            continue;
        AddToArray(endState, temp);
        break;
    }

    int i = 0;
    while (getline(myfile, temp))
    {
        if (temp[0] == '#') // Ignore lines starting with '#'
            continue;
        AddTo2DArray(transition_table, temp, i);
        i++;
        if (i >= NOL() - 4)
            break;
    }

    myfile.close();
}

int Epsilon::FindIndex(string state)
{
    string str(1, state[0]);
    for (size_t j = 0; j < NOL() - 4; j++)
    {
        if (states[j] == str)
            return j;
    }
}
string Epsilon::CheckEpsilon(string currentState)
{
    string epsilonStr = currentState;
    while (currentState != "-")
    {
        currentState = transition_table[FindIndex(currentState)][epsilon];
        if (currentState == "-") break;
        epsilonStr += " " + currentState;
    }
    return epsilonStr;
}
string Epsilon::nextState()
{
    for (size_t i = 0; i < NOL() - 4; i++)
    {
        if (transition_table[i][epsilon] == "-")
            continue;
        return CheckEpsilon(transition_table[i][epsilon]);
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
    cout << "E-Closure of (" << states[0] << ") = {" << states[0] << "," << nextState() << ",}\n";
    for (size_t i = 1; i < NOL() - 4; i++)
    {
        if (transition_table[i][epsilon] == "-")
        {
            cout << "E-Closure of (" << states[i] << ") = {" << states[i]<< "}\n";
            continue;
        }
        cout << "E-Closure of (" << states[i] << ") = {"<< nextState() << ",}\n";
    }
}
int Epsilon::NOL()
{
    ifstream myFile(fileName);
    string line;
    int count = 0;
    while (getline(myFile, line))
    {
        if (line.empty() || line[0] == '#') // Ignore empty lines and lines starting with '#'
            continue;
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