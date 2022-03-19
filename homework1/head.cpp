#include "head.h"

using namespace std;

void scanner::goback()
{
    pos--;
}

int scanner::ifsymbol(char ch)
{
    switch(ch){
        case '+':
            token[tokenpos++] = ch;
            ch = getnextchar();
            if(isdigit(ch))
                return 28;
            else
            {
                pos--;
                type = 
            }
    }
}

char scanner::getnextchar()
{
    if(pos < buffer.length())
    {
        return buffer[pos++];
    }
    else
    {
        if (getline(infile, buffer))
        {
            buffer.push_back('\n');
        }
        else
        {
            return EOF;
        }
        pos = 0;
        return buffer[pos++];
    }
}

void scanner::gettoken()
{
    char ch;
    constexpr int tokenlength = 256;
    char token[tokenlength];
    memset(token, 0, tokenlength);
    int tokenpos = 0;
    ofstream outfile("token.txt");
    while ((ch = getnextchar()) != EOF)
    {
        while(state!=100)
        {
            switch(state){
                case 0:
                    if(isalpha(ch))
                        state = 1;
                    else if(isdigit(ch))
                        state = 4;
                    else if(ispunct(ch))
                        state = 6;
                    else
                        state = -1;
                case 1:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if(isalpha(ch)||isdigit(ch))
                        state = 1;
                    else
                    {
                        pos--;
                        state = 5;
                    }
                case 5:
                    int i;
                    for(i = 0;i<32;i++)
                    {
                        if(strcmp(token, keytable[i].c_str()) == 0)
                        {
                            state = 100;
                            type = keynum[i];
                            break;
                        }
                    }
                    if(i == 32)
                    {
                        state = 100;
                        type = 1;
                    }
                    break;

            }
        }
    }
}