#pragma once

typedef enum {
    T_INT,
    T_BOOL,
    T_CHAR,
    T_FLOAT,
    T_DOUBLE,

    T_INTKEY,
    T_BOOLKEY,
    T_CHARKEY,
    T_FLOATKEY,
    T_DOUBLEKEY,
    T_IFKEY,
    T_ELSEKEY,
    T_DEFKEY,
    T_STRUCTKEY,

    T_COLON, // :
    T_SEMICOLON, // ;

    T_EOF,
    T_ERROR
} token_type;

typedef struct {
    token_type type;

    char *start;
    char *end;
} Token;
