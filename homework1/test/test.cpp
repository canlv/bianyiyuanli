#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main()
{
    string digit = "1";
    string alpha = "bss";
    string key[2] = {"bss","nb"};
    char test[4] = "bss";

    const char* cdigit = digit.c_str();
    const char* calpha = alpha.c_str();

    cout<<key[1].c_str()<<endl;

    cout << strcmp(test, key[0].c_str()) << endl;
    cout << strcmp(test, key[1].c_str()) << endl;
}