#include "Table.h"
#include "FileReader.h"
#include "TypeConverter.h"

class Catalogue {
private:
    int capacity;
    int current;
    char* file;
    Table** tables;

    void Resize();

    void Free();

    void CopyFrom(const Catalogue& other);

public:
    Catalogue();

    Catalogue(Table** tables, char* file, char* name, int capacity, int count);

    Catalogue(const Catalogue& other);

    Catalogue& operator=(const Catalogue& other);

    ~Catalogue();

    int countLines(string name);

    void import(char* tableName, char* filePath);

    void exportTable(char* tableName, string fileName);

    void showTables();

    void print(char* name);

    void select(char* name, char* value);

    void count(char* name, int columnIndex, char* value);

    void deleteRows(char* name, int columnIndex, char* value);

    void update(char* nameTable, int indexOfColumn, char* value, int indexOfTarget, char* targetValue);

    void aggregate(char* nameTable, int indexOfColumn, char* value, int indexOfTarget, char* operation);

    void describe(char* name);

    void rename(char* oldName, char* newName);

    void addColumn(char* tableName, char* columnType);

    void innerJoin(char* sourceTable, int sourceColumnIndex, char* targetTable, int targetColumnIndex);

    bool valueExists(char* tableName, char* value);

    void Write(const string& fileName, const string& data);

    Table* getTableByName(char* name);

    int getTableIndex(char* name);

    bool tableExists(char* name);
};







