#include <stdio.h>
#include <stdlib.h>

void get_token();
void term();
void factor();
void error(int);

enum {null, PLUS, MINUS, STAR, SLASH, PERCENT, NUMBER, LPAREN, RPAREN, END} token;

void get_token(){
    // token = next token of input
    char ch = getchar();
    printf("%c", ch);

    if(ch == '+')
        token = PLUS;
    else if (ch == '-')
        token = MINUS;
    else if (ch == '*')
        token = STAR;
    else if (ch == '/')
        token = SLASH;
    else if (ch == '%')
        token = PERCENT;
    else if (ch == '(')
        token = LPAREN;
    else if (ch == ')')
        token = RPAREN;
    else if (ch == '\n')
        token = END;
    else if (ch >= '0' && ch <= '9')
        token = NUMBER;
}

void expression(){
    term();
    while(token == PLUS || token == MINUS){
        get_token();
        term();
    }
}

void term(){
    factor();
    while(token == STAR || token == SLASH || token == PERCENT){
        get_token();
        factor();
    }
}

void factor(){
    if(token == NUMBER)
        get_token();
    else if (token == LPAREN){
        get_token();
        expression();
        if (token == RPAREN)
            get_token();
        else
            error(1);
    }
    else error(2);
}

int main(void){
    get_token();
    expression();
    if(token != END)
        error(3);

    printf("Correct Expression\n");
}

void error(int num) {
    //error handling
    printf("%d: Wrong Expression\n", num);
    exit(1);
}