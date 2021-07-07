#include <stdlib.h>
#include <string>

using namespace std;

class TypeConverter {

public:
    TypeConverter();

    static int charArrToInt(char* input) {
        return atoi(input);
    }
    static double charArrToDouble(char* input) {
        return atof(input);
    }
    static char* IntToCharArray(int number) {
        string input = to_string(number);
        char* wanted = new char[input.length() + 1];
        strcpy(wanted, input.c_str());
        return wanted;
    }
    static char* DoubleToCharArray(int number) {
        string input = to_string(number);
        char* wanted = new char[input.length() + 1];
        strcpy(wanted, input.c_str());
        return wanted;
    }


};

