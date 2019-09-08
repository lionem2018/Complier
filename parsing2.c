#include <stdio.h>
#include <stdlib.h>

void get_token();
void term();
void factor();
void error(int);

enum {null, PLUS, MINUS, STAR, SLASH, PERCENT, NUMBER, LPAREN, RPAREN, END} token;

char input[100];
int index = 0;

void get_token(){
    // token = next token of input
    // char ch = getchar();
    // printf("%c\n", input[index]);

    if(input[index] == '+')
    {
        token = PLUS;
        index++;
    }
    else if (input[index] == '-')
    {
        token = MINUS;
        index++;
    }
    else if (input[index] == '*')
    {
        token = STAR;
        index++;
    }
    else if (input[index] == '/')
    {
        token = SLASH;
        index++;
    }
    else if (input[index] == '%')
    {
        token = PERCENT;
        index++;
    }
    else if (input[index] == '(')
    {
        token = LPAREN;
        index++;
    }
    else if (input[index] == ')')
    {
        token = RPAREN;
        index++;
    }
    else if (input[index] == '\n' || input[index] == '\0')
    {
        token = END;
        index++;
    }

    else if (input[index] >= '0' && input[index] <= '9')
        if (input[index+1] >= '0' && input[index+1] <= '9')
        {
            index++;
            get_token();
        }
        else
        {
            token = NUMBER;
            index++;
        }
    else
        error(0);
    
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
    scanf("%s", input);
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