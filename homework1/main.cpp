#include "head.h"

using namespace std;

int main()
{
    char nowword;

    freopen("demo.c","r",stdin);
    freopen("tokens.txt","w",stdout);

    wordlength = 0;
    while(cin>>nowword)
    {
            token[wordlength] = nowword;
            wordlength++;
    }

    analyze();

    fclose(stdin);
    fclose(stdout);
    return 0;
}