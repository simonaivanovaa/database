
#include "Cell.h"

class BaseColumn {
protected:

    int ID;
    int capacity;
    int count;

    CellString** cells;

    void CopyFrom(const BaseColumn& other);

    void Free();

    void Resize();


public:
    BaseColumn();

    BaseColumn(int ID, int capacity, CellString* cells);

    BaseColumn(int ID, int capacity);

    BaseColumn(const BaseColumn& other);

    BaseColumn& operator=(const BaseColumn& other);

    ~BaseColumn();



    void addCell(CellString* cell);

    CellString*& getCell(int index);

    char* getInfo(int index);

    int getID() const;

    int getCapacity() const;

    void setID(int ID);

    void setCapacity(int capacity);

    void printRow(int index, bool isNewLineNeeded);

    virtual char* GetType() = 0;

    virtual BaseColumn* clone() = 0;

    virtual void Print() = 0;
};


/////////////////////////////////////////////
class ColumnOfTypeInt : public BaseColumn {
private:

    char type[8];

public:
    ColumnOfTypeInt();

    ColumnOfTypeInt(int ID, int capacity, CellString* cells);

    ColumnOfTypeInt* clone();

    void Print();

    char* GetType();

    ColumnOfTypeInt(int id, int capacity);
};


////////////////////////////////////////////

class ColumnOfTypeDouble : public BaseColumn {
private:
    char type[7];

public:
    ColumnOfTypeDouble();

    ColumnOfTypeDouble(int ID, int capacity, CellString* cells);

    ColumnOfTypeDouble(int ID, int capacity);


    ColumnOfTypeDouble* clone();

    void Print();

    char* GetType();
};


////////////////////////////////////////////////////////////////////////
class ColumnOfTypeString : public BaseColumn {
private:

    char type[7] = "String";

public:
    ColumnOfTypeString();

    ColumnOfTypeString* clone();

    void Print();

    char* GetType();

    ColumnOfTypeString(int ID, int capacity);
};


