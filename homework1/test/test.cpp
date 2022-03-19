#include <iostream>
#include <cctype>

using namespace std;

int main()
{
    string digit = "1";
    string alpha = "bss";

    const char* cdigit = digit.c_str();
    const char* calpha = alpha.c_str();



    cout<<cdigit<<isdigit(*cdigit)<<endl;
    cout<<calpha<<isalpha(*calpha)<<endl;
}