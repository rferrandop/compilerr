#pragma once

#include "token.h"

struct Scanner {
    char *ip;
    char *start;

    unsigned int size;
    unsigned int capacity;
    struct Token **tokens;
};
