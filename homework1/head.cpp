#include "head.h"

using namespace std;

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
                    else if (ch == ' ' || ch == '\t' || ch == '\n')
                        state = 100;
                    else
                        state = -1;
                case 1:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if (isalpha(ch) || isdigit(ch))
                        state = 1;
                    else
                    {
                        pos--;
                        state = 5;
                    }
                    break;
                case 2:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if(ch == '\'')
                    {
                        state = 100;
                        type = 2;
                    }
                    else
                    {
                        token[tokenpos++] = ch;
                        ch = getnextchar();
                        if (ch == '\'')
                        {
                            state = 100;
                            type = 2;
                        }
                        else
                        {
                            pos--;
                            state = -1;
                        }
                    }
                    break;
                case 3:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if (ch == '"')
                        state = 12;
                    else
                        state = 3;
                    break;
                case 4:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if (isdigit(ch))
                        state = 4;
                    else if (ch == '.')
                        state = 7;
                    else
                    {
                        pos--;
                        state = 100;
                        type = 4;
                    }
                    break;    
                case 5:
                    int i;
                    for (i = 0;i<32;i++)
                    {
                        if (strcmp(token, keytable[i].c_str()) == 0)
                        {
                            state = 100;
                            type = keytype[i];
                            break;
                        }
                    }
                    if(i == 32)
                    {
                        state = 100;
                        type = 1;
                    }
                    break;
                case 6:
                    if (ch == '\'')
                        state = 2;
                    else if (ch == '"')
                        state = 3;
                    else if (ch == '/')
                        state = 11;
                    else
                    {
                        int i;
                        for (i = 0; i < 41; i++)
                        {
                            if(strcmp(token, symboltable[i].c_str()) == 0)
                            {
                                state = 100;
                                type = symboltype[i];
                                break;
                            }
                        }
                        if(i == 41)
                        {
                            state = -1;
                        }
                    }
                    break;
                case 7:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if (isdigit(ch))
                        state = 7;
                    else if (ch == 'e')
                        state = 8;
                    else
                    {
                        pos--;
                        state = 100;
                        type = 37;
                    }
                    break;
                case 8:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if(isdigit(ch))
                        state = 9;
                    else if(ch == '-')
                        state = 10;
                    else
                    {
                        pos--;
                        state = -1;
                    }
                    break;
                case 9:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if(isdigit(ch))
                        state = 9;
                    else
                    {
                        pos--;
                        state = 100;
                        type = 37;
                    }
                    break;
                case 10:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if (isdigit(ch))
                        state = 9;
                    else
                    {
                        pos--;
                        state = -1;
                    }
                    break;
                case 11:
                    token[tokenpos++] = ch;
                    ch = getnextchar();
                    if (ch == '/')
                        state = 13;
                    else if(ch == '*')
                        state = 14;
                    else
                    {
                        pos--;
                        state = 100;
                        type = symboltype[13];
                    }
                    break;
                case 12:
                    token[tokenpos++] = ch;
                    state = 100;
                    type = 3;
                    break;
                case 13:
                    while((ch = getnextchar()) != '\n');
                    state = 100;
                    type = 79;
                    break;
                case 14:
                    ch = getnextchar();
                    if(ch == '*')
                        state = 15;
                    else
                        state = 14;
                    break;
                case 15:
                    ch = getnextchar();
                    if (ch == '*')
                        state = 15;
                    else if(ch == '/')
                        state = 16;
                    else
                        state = 14;
                    break;
                case 16:
                    state = 100;
                    type = 80;
                    break;
                case -1:
                    cout<<"error"<<endl;
                    std::cout << (int)ch << " " << ch << std::endl;
				    ch = getnextchar();
				    while (ch != ' '&&ch != '\t'&&ch != '\n'&&ch != ';') 
                        ch = getnextchar();
                    pos--;
                    state = 100;
                    type = -1;
            }
            if(state = 100 && type != -1)
            {
                outfile<<"("<<token<<","<<type<<")"<<endl;
                memset(token, 0, tokenlength);
                tokenpos = 0;
                state = 0;
                type = -1;
            }
        }
        if (state == 100)
            state = 0;
    }
    outfile.close();
}