
#include "Catalogue.h"
int main()
{

    Catalogue* myCatalog = new Catalogue();

    char tableName[] = "MoniTable";
    char tableName2[] = "MoniTable1";
    char joinedTable[] = "JoinedTable";
    char tablePath[] = "C:\\Simona\\table1.csv";
    char tablePath2[] = "C:\\Simona\\table2.csv";
    char word[] = "simona";
    char op[] = "sum";
    char number[] = "2.5";
    char number2[] = "3.0";

    myCatalog->import(tableName, tablePath);
    myCatalog->import(tableName2, tablePath2);

    myCatalog->innerJoin(tableName, 2, tableName2, 2);
    myCatalog->print(joinedTable);

}
