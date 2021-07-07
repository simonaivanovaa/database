#include "Table.h"
Table::Table() {
    char name[] = "Basic name";
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->capacity = 8;
    this->count = 0;
    cols = new BaseColumn * [capacity];
}

Table::Table(char* tableName, int rowCount) {
    this->name = new char[strlen(tableName) + 1];
    strcpy(this->name, tableName);
    this->capacity = rowCount;
    this->count = 0;
    cols = new BaseColumn * [capacity];
}

Table::Table(const Table& other) {
    CopyFrom(other);
}

Table& Table::operator=(const Table& other) {
    if (this != &other) {
        Free();
        CopyFrom(other);
    }
    return *this;
}
void Table::Free() {
    for (int i = 0; i < count; i++)
        delete cols[i];

    delete[] cols;
    delete[] name;
}

void Table::CopyFrom(const Table& other) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    cols = new BaseColumn * [other.capacity];
    capacity = other.capacity;
    count = other.count;
    for (int i = 0; i < count; i++)
        cols[i] = other.cols[i]->clone();
}

Table::~Table() {
    Free();
}

void Table::Resize() {
    int desiredColumnCount = count * 2;
    BaseColumn** temp = new BaseColumn * [desiredColumnCount * 2];

    for (int i = 0; i < count; i++)
        temp[i] = cols[i];

    delete[] cols;
    cols = temp;
}

BaseColumn& Table::GetColumn(int index) {
    for (int i = 0; i < count; i++) {
        if (i == index) {
            return *cols[i];
        }
    }
}

char* Table::getType(int index) {
    return GetColumn(index).GetType();
}

char* Table::getName() {
    return this->name;
}

int Table::getColumnCount() {
    return this->count;
}

int Table::getRowCount() {
    return this->capacity;
}

BaseColumn* Table::getColumn(int index) {
    return cols[index];
}

void Table::insertIntColumn(int index, int len) {
    ColumnOfTypeInt* current = new ColumnOfTypeInt(index, len);
    Add(current);

}

void Table::insertDoubleColumn(int index, int len) {
    ColumnOfTypeDouble* current = new ColumnOfTypeDouble(index, len);
    Add(current);
}

void Table::insertStringColumn(int index, int len) {
    ColumnOfTypeString* current = new ColumnOfTypeString(index, len);
    Add(current);
}

void Table::Add(BaseColumn* currentColumn) {
    if (count == capacity)
        Resize();
    cols[count++] = currentColumn;
}

void Table::printRows() {
    for (int i = 0; i < capacity - 1; i++) {
        for (int m = 0; m < count; m++) {
            cols[m]->printRow(i, m % count == count - 1 && m != 0);
            /*if(m % current == current - 1 && m != 0) {
                cols[m]->printRow(i, true);
            } else {
                cols[m]->printRow(i, false);
            }*/
        }
    }
}

void Table::printRowsWithSuchValues(char* value) {
    for (int i = 0; i < capacity - 1; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (strcmp(cols[j]->getInfo(i), value) == 0) {
                for (int k = 0; k < count; k++) {
                    //cols[k]->printRow(i, j % current == current - 1 && j != 0);
                    cols[k]->getCell(i)->printCell(k % count == count - 1 && k != 0);
                }

            }
        }
    }
}

void Table::rename(char* newTableName) {
    this->name = new char[strlen(newTableName) + 1];
    strcpy(this->name, newTableName);
}

void Table::setCapacity(int rows) {
    this->capacity = rows;
}