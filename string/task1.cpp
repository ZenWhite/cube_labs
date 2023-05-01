#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream file;
    file.open("data.txt");

    if (!file)
    {
        cerr << "Невозможно открыть файл!";
        exit(1);
    }

    int maxLineNumber = 0;
    int maxLineLength = 0;

    string line;
    int lineNumber = 1;

    while (getline(file, line))
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

    file.close();

    return 0;
}
