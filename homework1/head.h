#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


class scanner{
private:
    int state;
    int type;
    int pos;
    std::string buffer;
    const char* filename;
    std::ifstream infile;
    char symboltable[17] = {'+','-','*','/',
                            '>','<','=',';',
                            '!','[',']','{',
                            '}','(',')','"',
                            ','};
    int symbolnum[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    std::string keytable[32] = {"auto", "break", "case", "char",
                                "const", "continue", "default", "do",
                                "double", "else", "enum", "extern",
                                "float", "for", "goto", "if",
                                "int","long","register","return",
                                "short","signed","sizeof","static",
                                "struct","switch","typedef","union",
                                "unsigned","void","volatile","while"};
    int keynum[32] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
public:
    scanner(const char* s)
    {
        state = 0;
        type = -1;
        pos = 0;
        filename = s;
        infile.open(filename);
    }

    ~scanner()
    {
        infile.close();
    }

    void goback();

    int ifsymbol(char ch);

    void gettoken();

    char getnextchar();

};


