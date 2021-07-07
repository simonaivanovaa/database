#include "Catalogue.h"
void Catalogue::CopyFrom(const Catalogue& other) {
    capacity = other.capacity;
    file = new char[strlen(other.file) + 1];
    strcpy(file, other.file);


    tables = new Table * [other.capacity];
    capacity = other.capacity;

    for (int i = 0; i < capacity; i++)
        tables[i] = other.tables[i];
}

void Catalogue::Free() {

    delete[]file;
    for (int i = 0; i < capacity; ++i) {
        delete tables[i];
    }
    delete[] tables;
}

Catalogue::Catalogue() {
    this->capacity = 8;
    this->current = 0;
    tables = new Table * [capacity];
}

Catalogue::Catalogue(Table** tables, char* file, char* name, int capacity, int count) {
    this->capacity = capacity;
    this->current = count;

    this->file = new char[strlen(file) + 1];
    strcpy(this->file, file);

    tables = new Table * [capacity];

}

Catalogue::Catalogue(const Catalogue& other) {
    CopyFrom(other);
}

Catalogue& Catalogue::operator=(const Catalogue& other) {
    if (this != &other) {
        Free();
        CopyFrom(other);
    }
    return *this;
}

Catalogue::~Catalogue() {
    Free();
}

void Catalogue::Resize() {
    capacity *= 2;
    Table* helper = new Table[capacity];
    for (int i = 0; i < current; i++) {
        helper[i] = *tables[i];
    }

    delete[] tables;
    tables = &helper;

}

int Catalogue::getTableIndex(char* name) {
    for (int i = 0; i < capacity; ++i) {
        if (strcmp(tables[i]->getName(), name) == 0) {
            return i;
        }
    }
}

void Catalogue::showTables() {
    for (int i = 0; i < current; i++) {
        cout << tables[i]->getName() << "\n";
    }
}

void Catalogue::print(char* name) {
    if (!tableExists(name)) {
        cout << "No table with name:" << name;
        return;
    }
    Table* table = getTableByName(name);
    table->printRows();      
    
}

void Catalogue::select(char* name, char* value) {
    Table* table = getTableByName(name);
    table->printRowsWithSuchValues(value);
}

void Catalogue::import(char* tableName, char* filePath) {
    if (tableExists(tableName)) {
        cout << "Table already loaded in memory!\n";
    }
    else {
        string line;
        ifstream myfile;
        myfile.open(filePath);

        if (!myfile.is_open()) {
            perror("Error open");
            exit(EXIT_FAILURE);
        }

        int rowCount = FileReader::getRowCount(filePath);
        Table* table = new Table(tableName, rowCount);
        if (rowCount > 0) {
            int columnCount = FileReader::getColumnCount(filePath);

            //construct columns
            if (columnCount > 0) {
                for (int m = 0; m < columnCount; m++) {
                    if (FileReader::getColumnType(filePath, m) == "integer") {
                        table->insertIntColumn(m, rowCount);
                    }
                    else if (FileReader::getColumnType(filePath, m) == "double") {
                        table->insertDoubleColumn(m, rowCount);
                    }
                    else if (FileReader::getColumnType(filePath, m) == "string") {
                        table->insertStringColumn(m, rowCount);
                    }
                }
            }

            //add cells to each column
            for (int k = 0; k < columnCount; k++) {
                ifstream myfile;
                myfile.open(filePath);
                //remove first line that consists of column types
                getline(myfile, line);

                while (getline(myfile, line)) {
                    string info = FileReader::getValue(line, k);
                    CellString* cell = new CellString(info);
                    table->GetColumn(k).addCell(cell);
                }
            }
            tables[current] = table;
            this->current++;
        }
    }
}

void Catalogue::exportTable(char* tableName, string fileName) {
    if (tableExists(tableName)) {
        Table* tableToExport = getTableByName(tableName);

        int columns = tableToExport->getColumnCount();
        int rows = tableToExport->getRowCount();

        string dataToWrite = "";

        for (int i = 0; i < current; i++) {
            if (strcmp(tables[i]->getName(), tableName) == 0) {
                for (int h = 0; h < tables[i]->getColumnCount(); h++) {
                    char* cellData = tables[i]->getType(h);
                    const char comma[] = ",";
                    char* concatenated = (char*)malloc(1 + strlen(cellData) + strlen(comma));
                    strcpy(concatenated, cellData);
                    strcat(concatenated, comma);
                    dataToWrite.append(concatenated);
                }
                string s = dataToWrite.substr(0, dataToWrite.size() - 1);
                dataToWrite = s;
                dataToWrite.append("\n");

                break;
            }
        }

        for (int i = 0; i < rows - 1; i++) {
            for (int m = 0; m < columns; m++) {
                if (m % columns == columns - 1 && m != 0) {
                    char* cellData = tableToExport->getColumn(m)->getCell(i)->getString();
                    const char newLine[] = "\n";
                    char* concatenated = (char*)malloc(1 + strlen(cellData) + strlen(newLine));
                    strcpy(concatenated, cellData);
                    strcat(concatenated, newLine);
                    dataToWrite.append(concatenated);
                }
                else {
                    char* cellData = tableToExport->getColumn(m)->getCell(i)->getString();
                    const char comma[] = ",";
                    char* concatenated = (char*)malloc(1 + strlen(cellData) + strlen(comma));
                    strcpy(concatenated, cellData);
                    strcat(concatenated, comma);
                    dataToWrite.append(concatenated);
                }
            }
        }
        Write(fileName, dataToWrite);
    }
}

void Catalogue::Write(std::string const& fileName, std::string const& data) {
    std::ofstream binFile(fileName, std::ios::out | std::ios::binary);
    if (binFile.is_open()) {
        size_t len = data.size();
        //binFile.write((char*)&len, sizeof(len));
        binFile.write((char*)&data[0], len);

        binFile.close();
        // No need. The file will be closed when the function returns.
        // binFile.close();
    }
}

bool Catalogue::tableExists(char* name) {
    for (int i = 0; i < current; i++) {
        if (strcmp(tables[i]->getName(), name) == 0) {
            return true;
        }
    }
    return false;
}

Table* Catalogue::getTableByName(char* name) {    
    for (int i = 0; i < current; i++) {
        if (strcmp(tables[i]->getName(), name) == 0) {
            return tables[i];
        }
    }
}

void Catalogue::describe(char* name) {
    for (int i = 0; i < current; i++) {
        if (strcmp(tables[i]->getName(), name) == 0) {
            for (int h = 0; h < tables[i]->getColumnCount(); h++) {
                cout << "Column " << h << ": " << tables[i]->getType(h) << "\n";
            }
            break;
        }
    }
}

void Catalogue::addColumn(char* tableName, char* columnType) {
    if (tableExists(tableName)) {
        Table* table = getTableByName(tableName);

        if (strcmp(columnType, "integer") == 0) {
            int columnIndex = table->getColumnCount();
            int rows = table->getRowCount();
            table->insertIntColumn(columnIndex, rows);
            for (int i = 0; i < rows; i++) {
                CellString* cell = new CellString("NULL");
                table->GetColumn(columnIndex).addCell(cell);
            }
            table->getColumnCount();
        }
        else if (strcmp(columnType, "double") == 0) {
            int columnIndex = table->getColumnCount() + 1;
            int rows = table->getRowCount();
            table->insertDoubleColumn(columnIndex, rows);
            for (int i = 0; i < rows; i++) {
                CellString* cell = new CellString("NULL");
                table->GetColumn(columnIndex).addCell(cell);
            }
        }
        else if (strcmp(columnType, "string") == 0) {
            int columnIndex = table->getColumnCount() + 1;
            int rows = table->getRowCount();
            table->insertStringColumn(columnIndex, rows);
            for (int i = 0; i < rows; i++) {
                CellString* cell = new CellString("NULL");
                table->GetColumn(columnIndex).addCell(cell);
            }
        }
    }
}

void Catalogue::count(char* name, int columnIndex, char* value) {
    Table* table = getTableByName(name);
    int counter = 0;
    if (table->getColumnCount() - 1 < columnIndex) {
        cout << "No column at such index!";
        return;
    }
    int rows = table->getColumn(columnIndex)->getCapacity() - 1;
    for (int i = 0; i < rows; ++i) {
        if (strcmp(table->getColumn(columnIndex)->getCell(i)->getString(), value) == 0) {
            counter++;
        }
    }
    cout << counter;
}

void Catalogue::rename(char* oldName, char* newName) {
    if (tableExists(oldName)) {
        if (tableExists(newName)) {
            cout << "This name is not unique!";
        }
        else {
            Table* table = getTableByName(oldName);
            table->rename(newName);
            cout << table->getName();
        }
    }
}

void Catalogue::deleteRows(char* name, int columnIndex, char* value) {
    Table* table = getTableByName(name);
    if (table->getColumnCount() - 1 < columnIndex) {
        cout << "No column at such index!";
        return;
    }

    int cols = table->getColumnCount();
    int rowsOfOld = table->getRowCount();
    Table* newTable = new Table(name, rowsOfOld);
    int rows = table->getColumn(columnIndex)->getCapacity() - 1;
    if (cols > 0) {
        for (int m = 0; m < cols; m++) {
            if (strcmp(table->getType(m), "Integer") == 0) {
                newTable->insertIntColumn(m, rowsOfOld);
            }
            else if (strcmp(table->getType(m), "Double") == 0) {
                newTable->insertDoubleColumn(m, rowsOfOld);
            }
            else if (strcmp(table->getType(m), "String") == 0) {
                newTable->insertStringColumn(m, rowsOfOld);
            }
        }
    }

    int newCapacity = 0;
    for (int i = 0; i < rows; ++i) {
        newCapacity--;
        for (int j = 0; j < cols; j++) {
            if (strcmp(table->getColumn(columnIndex)->getCell(i)->getString(), value) < 0 ||
                strcmp(table->getColumn(columnIndex)->getCell(i)->getString(), value) > 0) {
                CellString* cell = new CellString(table->getColumn(j)->getCell(i)->getString());
                newTable->getColumn(j)->addCell(cell);
                newCapacity++;
            }
        }
    }

    table[getTableIndex(name)] = *newTable;
    table->setCapacity(newCapacity);
    delete newTable;
}

void Catalogue::update(char* nameTable, int indexOfColumn, char* value, int indexOfTarget, char* targetValue) {
    Table* table = getTableByName(nameTable);
    int cols = table->getColumnCount() - 1;
    int rows = table->getRowCount() - 1;
    if ((indexOfColumn > cols || indexOfColumn < 0) && (indexOfTarget > cols || indexOfTarget < 0)) {
        cout << "There is not such column at this index!";
        return;
    }
    for (int i = 0; i < rows; ++i) {
        if (strcmp(table->GetColumn(indexOfColumn).getCell(i)->getString(), value) == 0) {
            table->GetColumn(indexOfTarget).getCell(i)->setInfo(targetValue);
        }
    }

}

void Catalogue::aggregate(char* nameTable, int indexOfColumn, char* value, int indexOfTarget, char* operation) {
    Table* table = getTableByName(nameTable);
    int cols = table->getColumnCount() - 1;
    int rows = table->getRowCount() - 1;
    if ((indexOfColumn > cols || indexOfColumn < 0) && (indexOfTarget > cols || indexOfTarget < 0)) {
        cout << "There is not such column at this index!";
        return;
    }
    for (int i = 0; i < rows; ++i) {
        if (strcmp(table->GetColumn(indexOfColumn).getCell(i)->getString(), value) == 0) {
            if (!strcmp(table->GetColumn(indexOfTarget).getCell(i)->getString(), "NULL") > 0 ||
                !strcmp(table->GetColumn(indexOfTarget).getCell(i)->getString(), "NULL") < 0) {
                return;
            }
            if (strcmp(table->GetColumn(indexOfTarget).GetType(), "Integer") == 0) {
                int number1 = TypeConverter::charArrToInt(table->GetColumn(indexOfColumn).getCell(i)->getString());
                int number2 = TypeConverter::charArrToInt(table->GetColumn(indexOfTarget).getCell(i)->getString());
                if (strcmp(operation, "sum") == 0) {
                    int result = number1 + number2;
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::IntToCharArray(result));
                }
                else if (strcmp(operation, "product") == 0) {
                    int result = number1 * number2;
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::IntToCharArray(result));
                }
                else if (strcmp(operation, "minimum") == 0) {
                    int result;
                    if (number1 > number2) {
                        result = number2;
                    }
                    else {
                        result = number1;
                    }
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::IntToCharArray(result));
                }
                else if (strcmp(operation, "maximum") == 0) {
                    int result;
                    if (number1 < number2) {
                        result = number2;
                    }
                    else {
                        result = number1;
                    }
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::IntToCharArray(result));
                }
                else {
                    cout << "Invalid operation";
                }
            }
            else if (strcmp(table->GetColumn(indexOfTarget).GetType(), "Double") == 0) {
                double number1 = TypeConverter::charArrToDouble(
                    table->GetColumn(indexOfColumn).getCell(i)->getString());
                double number2 = TypeConverter::charArrToDouble(
                    table->GetColumn(indexOfTarget).getCell(i)->getString());
                if (strcmp(operation, "sum") == 0) {
                    double result = number1 + number2;
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::DoubleToCharArray(result));
                }
                else if (strcmp(operation, "product") == 0) {
                    double result = number1 * number2;
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::DoubleToCharArray(result));
                }
                else if (strcmp(operation, "minimum") == 0) {
                    double result;
                    if (number1 > number2) {
                        result = number2;
                    }
                    else {
                        result = number1;
                    }
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::DoubleToCharArray(result));
                }
                else if (strcmp(operation, "maximum") == 0) {
                    double result;
                    if (number1 < number2) {
                        result = number2;
                    }
                    else {
                        result = number1;
                    }
                    table->GetColumn(indexOfTarget).getCell(i)->setInfo(TypeConverter::DoubleToCharArray(result));
                }
                else {
                    cout << "Invalid operation";
                }


            }
            else {
                cout << "This column is not from type Integer or Double";
            }
        }
    }
}
void Catalogue::innerJoin(char* sourceTable, int sourceColumnIndex, char* targetTable, int targetColumnIndex) {
    if (!tableExists(sourceTable)) {
        cout << "The source table does not exist!\n";
        return;
    }
    if (!tableExists(targetTable)) {
        cout << "The target table does not exist!\n";
        return;
    }

    Table* srcTable = getTableByName(sourceTable);
    Table* tarTable = getTableByName(targetTable);

    int srcTableRows = srcTable->getRowCount() - 1;
    if (sourceColumnIndex > srcTable->getColumnCount() - 1) {
        cout << "There is no such column in table: " << srcTable->getName();
        return;
    }
    if (targetColumnIndex > tarTable->getColumnCount() - 1) {
        cout << "There is no such column in table: " << tarTable->getName();
        return;
    }

    BaseColumn* srcColumn = srcTable->getColumn(sourceColumnIndex);
    char* srcColumnType = srcColumn->GetType();

    int tarTableRows = tarTable->getRowCount() - 1;
    BaseColumn* tarColumn = tarTable->getColumn(targetColumnIndex);
    char* tarColumnType = tarColumn->GetType();

    if (!strcmp(srcColumnType, tarColumnType) == 0) {
        cout << "Cant join columns from different types";
        return;
    }
    char joinedTable[] = "JoinedTable";
    Table* table = new Table(joinedTable, srcTableRows);

    if (strcmp(srcColumnType, "Integer") == 0) {
        table->insertIntColumn(0, 1);
    }
    else if (strcmp(srcColumnType, "Double") == 0) {
        table->insertDoubleColumn(0, 1);
    }
    else if (strcmp(srcColumnType, "String") == 0) {
        table->insertStringColumn(0, 1);
    }

    for (int i = 0; i < srcTableRows; i++) {
        for (int j = 0; j < tarTableRows; j++) {
            if (strcmp(srcColumn->getCell(i)->getString(),
                tarColumn->getCell(j)->getString()) == 0) {
                if (strcmp(srcColumnType, "Integer") == 0) {
                    CellString* cell = new CellString(srcColumn->getCell(i)->getString());
                    if (!valueExists(table->getName(), cell->getString())) {
                        table->getColumn(0)->addCell(cell);
                    }
                }
                else if (strcmp(srcColumnType, "Double") == 0) {
                    CellString* cell = new CellString(srcColumn->getCell(i)->getString());
                    if (!valueExists(table->getName(), cell->getString())) {
                        table->getColumn(0)->addCell(cell);
                    }
                }
                else if (strcmp(srcColumnType, "String") == 0) {
                    CellString* cell = new CellString(srcColumn->getCell(i)->getString());
                    if (!valueExists(table->getName(), cell->getString())) {
                        table->getColumn(0)->addCell(cell);
                    }
                }

            }
        }
    }

    tables[current] = table;
    this->current++;
}

bool Catalogue::valueExists(char* tableName, char* value) {
    if (tableExists(tableName)) {
        Table* table = getTableByName(tableName);

        BaseColumn* column = table->getColumn(0);
        int tableRows = table->getRowCount() - 1;
        for (int i = 0; i < tableRows; i++) {
            if (strcmp(value, column->getCell(i)->getString()) == 0) {
                return true;
            }
        }
        return false;
    }
}