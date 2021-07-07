#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileReader {
public:
    FileReader();

    virtual ~FileReader();

    static string getValue(string line, int col) {
        string word = "";
        int counter = 0;
        int currentColumn = col;
        for (auto x : line) {
            if (x == ',' && counter != currentColumn) {
                word = "";
                counter++;
            }
            else if (x == ',' && (counter == currentColumn)) {
                //cout << word << endl;
                return word;
                word = "";
            }
            else {
                word = word + x;
            }
        }
        return word;
        //cout << word << endl;
    }

    static int countCols(string line) {
        int counter = 0;
        for (auto x : line) {
            if (x == ',') {
                counter++;
            }
        }
        if (counter == 0) {
            return 0;
        }

        counter++;
        return counter;
    }

    static int countRows(string line) {
        int counter = 0;
        string word = "";
        for (auto x : line) {
            if (x == ',') {
                counter++;
                word = "";
            }
            else {
                word = word + x;
            }
        }
        counter++;
        return counter;
    }

    static int getRowCount(char* filePath) {
        ifstream myfile;
        myfile.open(filePath);
        string line;
        int rowCount = 0;
        while (getline(myfile, line)) {
            rowCount++;
        }
        return rowCount;
    }

    static int getColumnCount(char* filePath) {
        ifstream myfile;
        string line;
        myfile.open(filePath);
        int columnCount = 0;
        while (getline(myfile, line)) {
            columnCount = countCols(line);
            break;
        }
        return columnCount;
    }

    static string getColumnType(char* filePath, int columnIndex) {
        ifstream myfile;
        string line;
        myfile.open(filePath);
        while (getline(myfile, line)) {
            return getValue(line, columnIndex);
        }
        return "Column type not found";
    }
};


