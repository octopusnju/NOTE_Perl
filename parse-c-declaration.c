#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENS   100
#define MAXTOKENLEN 64

enum type_tag {
    IDENTIFIER,
    QUALIFIER,
    TYPE
};

struct token {
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;

struct token stack[MAXTOKENS];
struct token this;

#define pop     (stack[top--])
#define push(s) (stack[++top] = (s))

enum type_tag classify_string(void)
{
    char *s = this.string;
    if (!strcmp(s, "const"))    { strcpy(s, "read-only"); return QUALIFIER; }
    if (!strcmp(s, "volatile")) { return QUALIFIER; }
    if (!strcmp(s, "void"))     { return TYPE; }
    if (!strcmp(s, "char"))     { return TYPE; }
    if (!strcmp(s, "signed"))   { return TYPE; }
    if (!strcmp(s, "unsigned")) { return TYPE; }
    if (!strcmp(s, "short"))    { return TYPE; }
    if (!strcmp(s, "int"))      { return TYPE; }
    if (!strcmp(s, "long"))     { return TYPE; }
    if (!strcmp(s, "float"))    { return TYPE; }
    if (!strcmp(s, "double"))   { return TYPE; }
    if (!strcmp(s, "struct"))   { return TYPE; }
    if (!strcmp(s, "union"))    { return TYPE; }
    if (!strcmp(s, "enum"))     { return TYPE; }
    return IDENTIFIER;
}

void gettoken(void)
{
    char *p = this.string;

    //skip blank
    while((*p = getchar()) == ' ');

    if (isalnum(*p)) { //if alphabeta or number
        while(isalnum(*++p = getchar())); //read till not alphabeta or number
        ungetc(*p, stdin); //put last char back
        *p = '\0'; //conpose a string
        this.type = classify_string(); //parse type of the string
        return;
    } else if (*p == '*') { //if pointer
        strcpy(this.string, "pointers to");
        this.type = '*';
        return;
    } else { //else
        this.string[1] = '\0';
        this.type = *p;
        return;
    }
}

void read_to_first_identifier(void)
{
    gettoken();
    while (this.type != IDENTIFIER) {
        push(this);
        gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
}

void deal_with_arrays(void)
{
    while (this.type == '[') {
        printf("array ");
        gettoken();
        if (isdigit(this.string[0])) {
            printf("0..%d ", atoi(this.string) - 1);
            gettoken();
        }
        gettoken();
        printf("of ");
    }
}

void deal_with_function_args(void)
{
    while (this.type != ')') {
        gettoken();
    }
    gettoken();
    printf("function returning ");
}

void deal_with_pointers(void)
{
    while (stack[top].type == '*') {
        printf("%s ", pop.string);
    }
}

void deal_with_declarator(void)
{
    switch (this.type) {
        case '[':
            deal_with_arrays();
            break;
        case '(':
            deal_with_function_args();
            break;
    }

    deal_with_pointers();

    while (top >= 0) {
        if (stack[top].type == '(') {
            pop;
            gettoken();
            deal_with_declarator();
        } else {
            printf("%s ", pop.string);
        }
    }
}

int main(void)
{
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");
    return 0;
}
