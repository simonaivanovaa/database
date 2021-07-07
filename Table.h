#include "Column.h"

class Table {
private:

    BaseColumn** cols;
    char* name;
    int capacity;
    int count;

    void Add(BaseColumn* currentColumn);

    void Free();

    void CopyFrom(const Table& other);

public:

    void Resize();

    Table();

    Table(const Table& other);

    Table& operator=(const Table& other);

    ~Table();


    BaseColumn& GetColumn(int index);

    char* getType(int index);

    char* getName();///add in constructor

    int getColumnCount();

    int getRowCount();

    BaseColumn* getColumn(int index);

    void insertIntColumn(int index, int len);

    void insertDoubleColumn(int index, int len);

    void insertStringColumn(int index, int len);

    void printRows();

    void printRowsWithSuchValues(char* value);

    Table(char* tableName, int rowCount);

    void rename(char* newTableName);

    void setCapacity(int rows);
};



