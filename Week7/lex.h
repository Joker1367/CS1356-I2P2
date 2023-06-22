#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 256
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, 
MULDIV, ASSIGN, LPAREN, RPAREN} TokenSet;

extern int match (TokenSet token);
extern void advance(void);
extern char* getLexeme(void);
void statement();
void expr();
void expr_tail();
void term();
void term_tail();
void factor();

// statement := END | expr END

// expr := term expr_tail

// expr_tail := ADDSUB term expr_tail | NIL

// term := factor term_tail

// term_tail := MULDIV factor term_tail | NIL

// factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN

void statement(){
    if(match(END)){
        advance();
    }
    else{
        expr();
        match(END);
        advance();
    }
}

void expr(){
    term();
    expr_tail();
}

void expr_tail(){
    if(match(ADDSUB)){
        printf("ADDSUB: %s\n", getLexeme());
        advance();
        term();
        expr_tail();
    }
}

void term(){
    factor();
    term_tail();
}

void term_tail(){
    if(match(MULDIV)){
        printf("MULDIV: %s\n", getLexeme());
        advance();
        factor();
        term_tail();
    }
}

void factor(){
    if(match(INT)){
        printf("INT: %s\n", getLexeme());
        advance();
    }
    else if(match(ADDSUB)){
        printf("ADDSUB: %s\n", getLexeme());
        advance();
        if(match(INT)){
            printf("INT: %s\n", getLexeme());
            advance();
        }
        else if(match(ID)){
            printf("ID: %s\n", getLexeme());
            advance();
        }
    }
    else if(match(ID)){
        printf("ID: %s\n", getLexeme());
        advance();
        if(match(ASSIGN)){
            printf("ASSIGN: %s\n", getLexeme());
            advance();
            expr();
        }
    }
    else if(match(LPAREN)){
        printf("LPAREN: %s\n", getLexeme());
        advance();
        expr();
        if(match(RPAREN)){
            printf("RPAREN: %s\n", getLexeme());
            advance();
        }
        else{
            printf("Wrong Intput!!!\n");
        }
    }
}
