#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CellString {
    char* info;
    int len;
    int ID;
public:
    CellString();

    CellString(const CellString& other);

    CellString& operator=(const CellString& other);

    ~CellString();

    char* getString();

    void printCell(bool isNewLineNeeded);

    void setInfo(char* string);

    CellString(string basicString);

    void setID(int cellId);

    int getDataLength();
};

