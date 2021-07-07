#include "Column.h"
BaseColumn::BaseColumn() {
    this->ID = 0;
    this->capacity = 8;
    this->count = 0;
    cells = new CellString * [capacity];

}

BaseColumn::BaseColumn(int ID, int capacity, CellString* cells) {
    this->ID = ID;
    this->capacity = capacity;
    this->count = count;
    cells = new CellString[capacity];
    for (int i = 0; i < capacity; i++) {
        this->cells[i] = &cells[i];
    }


}

BaseColumn::BaseColumn(int ID, int capacity) {

    this->ID = ID;
    this->capacity = capacity;
    this->count = count;
    cells = new CellString * [capacity];
}

int BaseColumn::getID() const {
    return ID;
}

int BaseColumn::getCapacity() const {
    return capacity;
}

void BaseColumn::setID(int ID) {
    this->ID = ID;
}

void BaseColumn::setCapacity(int capacity) {
    this->capacity = capacity;
}

void BaseColumn::CopyFrom(const BaseColumn& other) {
    ID = other.ID;
    capacity = other.capacity;
    count = other.count;
    cells = new CellString * [other.capacity];
    for (int i = 0; i < capacity; i++)
        cells[i] = other.cells[i];
}

void BaseColumn::Free() {

    delete[] cells;
}

BaseColumn::BaseColumn(const BaseColumn& other) {
    CopyFrom(other);
}

BaseColumn& BaseColumn::operator=(const BaseColumn& other) {
    if (this != &other) {
        Free();
        CopyFrom(other);
    }
    return *this;
}

BaseColumn::~BaseColumn() {
    Free();
}

void BaseColumn::Resize() {
    capacity *= 2;
    CellString** helper = new CellString * [capacity];
    for (int i = 0; i < count; i++) {
        helper[i] = cells[i];
    }

    delete[] cells;
    cells = helper;

}

void BaseColumn::addCell(CellString* cell) {
    if (count == capacity) {
        Resize();
    }
    cell->setID(count);
    cells[count] = cell;
    count++;
}

CellString*& BaseColumn::getCell(int index) {
    for (int i = 0; i < capacity; i++) {
        if (i == index) {
            return cells[i];
        }
    }
}

char* BaseColumn::getInfo(int index) {
    for (int i = 0; i < capacity - 1; i++) {
        if (i == index) {
            return cells[i]->getString();
        }
    }
}

void BaseColumn::printRow(int index, bool isNewLineNeeded) {
    cells[index]->printCell(isNewLineNeeded);

}
////////////////////////////////////////////////////////////
ColumnOfTypeInt::ColumnOfTypeInt() {
    char type[8] = "Integer";
    strcpy(this->type, type);
}

ColumnOfTypeInt::ColumnOfTypeInt(int ID, int capacity) {
    char type[8] = "Integer";
    strcpy(this->type, type);
    this->capacity = capacity;
    this->ID = ID;
    this->cells = new CellString * [capacity];
}

ColumnOfTypeInt::ColumnOfTypeInt(int ID, int capacity, CellString* cells) : BaseColumn(ID, capacity, cells) {

    char type[8] = "Integer";
    strcpy(this->type, type);
}

ColumnOfTypeInt* ColumnOfTypeInt::clone() {
    return new ColumnOfTypeInt(*this);
}

void ColumnOfTypeInt::Print() {
    for (int i = 0; i < capacity; i++) {
        cout << cells[i]->getString();
    }
}

char* ColumnOfTypeInt::GetType() {

    return type;
}
///////////////////////////////////////////////////
ColumnOfTypeDouble::ColumnOfTypeDouble() {
    char type[8] = "Double";
    strcpy(this->type, type);
}

ColumnOfTypeDouble::ColumnOfTypeDouble(int ID, int capacity) : BaseColumn(ID, capacity) {
    char type[7] = "Double";
    strcpy(this->type, type);
    this->capacity = capacity;
    this->ID = ID;
    this->count = 0;
    this->cells = new CellString * [capacity];
}

ColumnOfTypeDouble::ColumnOfTypeDouble(int ID, int capacity, CellString* cells) : BaseColumn(ID, capacity, cells) {
    char type[7] = "Double";
    strcpy(this->type, type);
}

ColumnOfTypeDouble* ColumnOfTypeDouble::clone() {
    return new ColumnOfTypeDouble(*this);
}

void ColumnOfTypeDouble::Print() {
    for (int i = 0; i < capacity; i++) {
        cout << cells[i]->getString();
    }
}

char* ColumnOfTypeDouble::GetType() {

    return type;
}
///////////////////////////////////////////
ColumnOfTypeString::ColumnOfTypeString() {

    /*char info[] = "String";
    strcpy(this->type, info);*/


}

ColumnOfTypeString::ColumnOfTypeString(int ID, int capacity) : BaseColumn(ID, capacity) {
    char type[7] = "String";
    strcpy(this->type, type);
    this->capacity = capacity;
    this->ID = ID;
    this->count = 0;
    this->cells = new CellString * [capacity];
}

ColumnOfTypeString* ColumnOfTypeString::clone() {
    return new ColumnOfTypeString(*this);
}

void ColumnOfTypeString::Print() {
    for (int i = 0; i < capacity; i++) {
        cout << cells[i]->getString();
    }
}

char* ColumnOfTypeString::GetType() {

    return type;
}