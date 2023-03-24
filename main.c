#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "scanner.h"

struct Scanner scanner;

void init_scanner(char *src) {
    scanner.ip = src;
    scanner.start = src;

    scanner.size = 0;
    scanner.capacity = 4;
    scanner.tokens = (struct Token **) malloc(scanner.capacity * sizeof(struct Token *));
}

struct Token *create_token(token_type type, int offset) {
    struct Token *t = malloc(sizeof(struct Token));
    t->type = type;
    t->start = scanner.start;
    
    scanner.ip += offset;
    t->end = scanner.ip;
    return t;
}

void ignore() {
    while (*scanner.ip == ' ' || *scanner.ip == '\t')
        scanner.ip++;
}

char next() {
    ignore();
    return *(scanner.ip++);
}

struct Token *scan_token(void) {
    char c = next();
    scanner.start = scanner.ip;

    switch (c) {
        case 'i':
            return create_token(T_I, 0);
        case 'n':
            return create_token(T_N, 0);
        case 't':
            return create_token(T_T, 0);
        case EOF:
            return create_token(T_EOF, 0);
        default:
            break;
    }
    return create_token(T_ERROR, 0);
}

void add_token(struct Token *t) {
    if (scanner.size >= scanner.capacity) {
        scanner.capacity *= 2;
    }
    scanner.tokens[scanner.size++] = t;
}

void scan(void) {
    struct Token *t;
    do {
        t = scan_token();
        add_token(t);
    } while (t->type != T_EOF && t->type != T_ERROR);
}

int main(int argc, char **argv) {
    char buffer[100];
    
    FILE *fp = fopen("test.b", "r");
    if (fp == NULL) perror("Error opening file");
    else {
        while (!feof(fp)) {
            if (fgets(buffer, 100, fp) == NULL) break;
        }
        fclose(fp);
    }
    
    init_scanner(buffer);
    scan();

    return 0;
}
