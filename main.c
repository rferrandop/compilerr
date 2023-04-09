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
    scanner.tokens = (Token **) malloc(scanner.capacity * sizeof(Token *));
}

Token *create_token(token_type type, int offset) {
    Token *t = malloc(sizeof(Token));
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

int match(char *str, int len) {
  for (int i = 0; i < len; i++) {
    char c = next();
    if (c != str[i]) {
      scanner.ip -= i;
      return 0;
    } 
  }
  return 1;
}

Token *scan_token(void) {
    char c = next();
    scanner.start = scanner.ip;

    switch (c) {
      case 'i':
        if (match("nt", 2)) return create_token(T_INTKEY, 2);
        break;
      case EOF:
        return create_token(T_EOF, 0);
      default:
        break;
    }
    return create_token(T_ERROR, 0);
}

void add_token(Token *t) {
    if (scanner.size >= scanner.capacity) {
        scanner.capacity *= 2;
    }
    scanner.tokens[scanner.size++] = t;
}

void scan(void) {
    Token *t;
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
