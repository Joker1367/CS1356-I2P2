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
Symbol table[TBLSIZE];
int sbcount = 0;

typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NAN} ErrorType;

 typedef struct _Node {
	char lexeme[MAXLEN];
	TokenSet token;
	int val;
	struct _Node *left, *right;
} BTNode;

TokenSet lookahead;
char lexeme[MAXLEN];

TokenSet getToken(void);
int match (TokenSet token);
void advance(void);
char* getLexeme(void);
int getval();
int setval(char* str, int val);
void statement(void);
BTNode* expr(void);
BTNode* term(void);
BTNode* factor(void);
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

BTNode* makenode(TokenSet tok, const char* lexeme){
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexeme);
    node->token = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode* root){
    if(root == NULL){
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void preorder(BTNode* root){
    if(root == NULL){
        return;
    }
    printf("%s ", root->lexeme);
    preorder(root->left);
    preorder(root->right);
}

int EvaluateTree(BTNode* root){
    int lv, rv, res;
    if(root != NULL){
        switch(root->token){
            case ID:
            case INT:
                return root->val;
                break;
            case MULDIV:
            case ADDSUB:
            case ASSIGN:
                lv = EvaluateTree(root->left);
                rv = EvaluateTree(root->right);
                if(strcmp(root->lexeme, "+") == 0){
                    res = lv + rv;
                }
                else if(strcmp(root->lexeme, "-") == 0){
                    res = lv - rv;
                }
                else if(strcmp(root->lexeme, "*") == 0){
                    res = lv * rv;
                }
                else if(strcmp(root->lexeme, "/") == 0){
                    if(rv == 0){
                        error(NAN);
                    }
                    else{
                        res = lv / rv;
                    }
                }
                else if(strcmp(root->lexeme, "=") == 0){
                    res = setval(root->left->lexeme, rv);
                }
                break;
            default:
                res = 0;
        }
    }
    return res;
}

void statement(void){
    BTNode* root;
    if (match(END)) {
        printf(">> ");
        advance();
    } else {
        root = expr();
        if(match(END)){
            printf("%d\n", EvaluateTree(root));
            preorder(root);
            printf("\n");
            freeTree(root);
            printf(">> ");
            advance();
        }
    }
}

BTNode* expr(void){
    BTNode* root;
    BTNode* left;
    root = left = term();
    while(match(ADDSUB)){
        root = makenode(ADDSUB, getLexeme());
        root->left = left;
        advance();
        root->right = term();
        left = root;
    }
    return root;
}

BTNode* term(void) 
{
    BTNode* root;
    BTNode* left;
    root = left = factor();
    while(match(MULDIV)){
        root = makenode(MULDIV, getLexeme());
        root->left = left;
        advance();
        root->right = factor();
        left = root;
    }
    return root;
}

BTNode* factor(void)
{
    BTNode* root;
    int val;
    char str[MAXLEN];

    if (match(INT)) {
        root = makenode(INT, getLexeme());
        root->val = getval();
        advance();
    } 
    else if (match(ADDSUB)) {
        strcpy(str, getLexeme());
        advance();
        if (match(INT) || match(ID)) {
            root = makenode(ADDSUB, str);
            if(match(INT)){
                root->right = makenode(INT, getLexeme());
            }
            else{
                root->right = makenode(ID, getLexeme());
            }
            root->right->val = getval();
            root->left = makenode(INT, "0");
            root->left->val = 0;
            advance();
        }
        else {
            free(root);
            error(NOTNUMID);
        }
    } 
    else if (match(ID)) {
        BTNode* left = makenode(ID, getLexeme());
        left->val = getval();
        strcpy(str, getLexeme());
        advance();
        if (match(ASSIGN)) {
            root = makenode(ASSIGN, getLexeme());
            root->left = left;
            advance();
            root->right = expr();
        }
        else{
            root = left;
        }
    } 
    else if (match(LPAREN)) {
        advance();
        root = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    }
    else{
        free(root);
        error(NOTNUMID);
    }
    return root;
}

void error(ErrorType errorNum)
{
    switch (errorNum) {
    case MISPAREN:
        fprintf(stderr, "Mismatched parenthesis\n");
        break;
    case NOTNUMID:
        fprintf(stderr, "Number or identifier expected\n");
        break;
    case NOTFOUND:
        fprintf(stderr, "%s not defined\n", getLexeme());
        break;
    case RUNOUT:
        fprintf(stderr, "Out of memory\n");
        break;
    case NAN:
        fprintf(stderr, "Not a number\n");
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
