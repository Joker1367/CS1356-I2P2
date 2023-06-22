#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLEN 256
#define TBLSIZE 65535

typedef enum {UNKNOWN, END, INT, ID, ADDSUB, 
              MULDIV, ASSIGN, LPAREN, RPAREN} TokenSet;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;

typedef enum {MISPAREN, NOTNUMID,
 NOTFOUND, RUNOUT} ErrorType;

Symbol table[TBLSIZE];
int sbcount = 0;
TokenSet lookahead = UNKNOWN;
char lexeme[MAXLEN];

TokenSet getToken(void);
int match (TokenSet token);
void advance(void);
char* getLexeme(void);
int getval();
int setval(char* str, int val);
void statement(void);
int expr(void);
int term(void);
int factor(void);
void error(ErrorType errorNum);

TokenSet getToken(void){
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // �����ťզr��
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } 
	else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } 
	else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } 
	else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } 
    else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } 
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } 
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } 
    else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } 
    else {
        return UNKNOWN;
    }
}

void advance(){
    lookahead = getToken();
}

int match (TokenSet token){
    if(lookahead == UNKNOWN){
        advance();
    }
    return token == lookahead;
}

char* getLexeme(void){
    return lexeme;
}

int getval(){
    int val, i, find;
    if(match(INT)){
        val = atoi(getLexeme());
    }
    else if(match(ID)){
        i = 0;
        find = 0;
        val = 0;
        while(i < sbcount && !find){
            if(strcmp(table[i].name, getLexeme()) == 0){
                val = table[i].val;
                find = 1;
                break;
            }
            else{
                i++;
            }
        }
        if(!find){
            if(sbcount < TBLSIZE){
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            }
            else{
                error(RUNOUT);
            }
        }
    }
    return val;
}

int setval(char* str, int num){
    int i, val;
    i = 0;
    while(i < sbcount){
        if(strcmp(table[i].name, str) == 0){
            table[i].val = num;
            val = num;
            break;
        }
        else{
            i++;
        }
    }
    return val;
}

void statement(void){
    int val;
    if (match(END)) {
        printf(">> ");
        advance();
    } else {
        val = expr();
        if(match(END)){
            printf("%d\n", val);
            printf(">> ");
        }
        advance();
    }
}

int expr(void){
    int val;
    val = term();
    while(match(ADDSUB)){
        if(strcmp(getLexeme(), "+") == 0){
            advance();
            val += term();
        }
        else if(strcmp(getLexeme(), "-") == 0){
            advance();
            val -= term();
        }
    }
    return val;
}

int term(void) 
{
    int val;
    val = factor();
    while(match(MULDIV)){
        if(strcmp(getLexeme(), "*") == 0){
            advance();
            val = val * term();
        }
        else if(strcmp(getLexeme(), "/") == 0){
            advance();
            val = val / term();
        }
    }
    return val;
}

int factor(void)
{
    int val;
    char str[MAXLEN];

    if (match(INT)) {
        val = getval();
        advance();
    } 
    else if (match(ADDSUB)) {
        strcpy(str, getLexeme());
        advance();
        if (match(INT) || match(ID)) {
            val = getval();
            if(strcmp(str, "-") == 0){
                val = -1 * val;
            }
            advance();
        }
        else {
            error(NOTNUMID);
        }
    } 
    else if (match(ID)) {
        val = getval();
        strcpy(str, getLexeme());
        advance();
        if (match(ASSIGN)) {
            advance();
            val = expr();
            val = setval(str, val);
        }
    } 
    else if (match(LPAREN)) {
        advance();
        val = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    }
    else{
        error(NOTNUMID);
    }
    return val;
}

void error(ErrorType errorNum)
{
    switch (errorNum) {
    case MISPAREN:
        fprintf(stderr, 
          "Mismatched parenthesis\n");
        break;
    case NOTNUMID:
        fprintf(stderr, 
          "Number or identifier expected\n");
        break;
    case NOTFOUND:
        fprintf(stderr, 
          "%s not defined\n", getLexeme());
        break;
    case RUNOUT:
        fprintf(stderr,
          "Out of memory\n");
    }
    exit(0);
}

int main()
{
    printf(">> ");
    while(1){
       statement(); 
    }
    return 0;
}
