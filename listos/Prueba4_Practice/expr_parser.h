#ifndef _PARSER_H
#define _PARSER_H

#include <iosfwd>
#include <iostream>
#include "expr_lexer.h"
#include <stack>
#include <list>
#include <vector>
#include <utility>
using namespace std;
class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    int parse(int count[4]);
private:
    Lexer& lexer;
    void init();
    Symbol symbol;
    std::vector<Symbol> stack;
    std::vector<Symbol> input;
};

#endif
