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
    std::string symboltable[41] = {"(", ")", "[", "]", "->", ".", "!", "~",
                                   "++", "--", "-", "*", "&", "/", "%", "+",
                                   "<<", ">>", "<", "<=", ">", ">=", "==", "!=",
                                   "^", "|", "&&", "||", "?:", "=", "+=", "-=",
                                   "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=",
                                   ","};
    int symboltype[41] = {38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78};
    std::string keytable[32] = {"auto", "break", "case", "char",
                                "const", "continue", "default", "do",
                                "double", "else", "enum", "extern",
                                "float", "for", "goto", "if",
                                "int","long","register","return",
                                "short","signed","sizeof","static",
                                "struct","switch","typedef","union",
                                "unsigned","void","volatile","while"};
    int keytype[32] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
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
    
    void gettoken();

    char getnextchar();

};


