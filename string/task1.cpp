#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream inFile;
    inFile.open("data.txt");

    if (!inFile)
    {
        cerr << "Невозможно открыть файл!";
        exit(1);
    }

    int maxLineNumber = 0;
    int maxLineLength = 0;

    string line;
    int lineNumber = 1;

    while (getline(inFile, line))
    {
        int lineLength = line.length();

        if (lineLength > maxLineLength)
        {

            maxLineLength = lineLength;
            maxLineNumber = lineNumber;
        }

        lineNumber++;
    }

    cout << "Номер самой длинной строки: " << maxLineNumber << endl;
    cout << "Длина самой длинной строки: " << maxLineLength << endl;

    inFile.close();

    return 0;
}
