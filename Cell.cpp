#include "Cell.h"
CellString::CellString() {
    char niz[5] = "NULL";
    this->info = new char[strlen(niz) + 1];
    strcpy(this->info, niz);
    this->len = 5;
    this->ID = 1;

}

CellString::CellString(string info) {
    char* str = new char[info.length() + 1];
    strcpy(str, info.c_str());
    this->info = str;
    this->len = info.length() + 1;
}

CellString::CellString(const CellString& other) {
    this->ID = other.ID;
    this->len = other.len;
    info = new char[strlen(other.info) + 1];
    strcpy(info, other.info);
}

CellString& CellString::operator=(const CellString& other) {

    if (this != &other)
    {
        delete[] info;
        this->ID = other.ID;
        this->len = other.len;
        info = new char[strlen(other.info) + 1];
        strcpy(info, other.info);
    }
    return *this;
}

CellString::~CellString() {
    delete[] info;
}

char* CellString::getString() {
    if (strlen(info) == 0) {
        char info[] = "NULL";
        return info;
    }
    return info;
}

void CellString::printCell(bool isNewLineNeeded) {

    if (isNewLineNeeded) {
        if (strlen(info) == 0) {
            cout << "NULL |\n";

        }
        else {
            cout << info << " | \n";
        }

    }
    else {
        if (strlen(info) == 0) {
            cout << "NULL |";

        }
        else {
            cout << info << " | ";
        }

    }
}

void CellString::setInfo(char* string) {

    this->info = new char[strlen(string) + 1];
    strcpy(this->info, string);

}

void CellString::setID(int cellId) {
    this->ID = cellId;
}

int CellString::getDataLength() {
    return this->len;
}