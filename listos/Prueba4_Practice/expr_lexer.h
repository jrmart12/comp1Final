#ifndef _LEXER_H
#define _LEXER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <functional>
enum class Symbol: unsigned {
    SPrime,
    S,
    L,
    OpenBrace,
    CloseBrace,
    Comma,
    Id,
    Eof,
    state0=0 ,
    state1=1 ,   
    state2=2 ,
    state3=3 ,
    state4=4 ,
    state5=5 ,
    state6=6 ,
    state7=7 
};

static inline unsigned indexOf(Symbol s) {
    unsigned index = static_cast<unsigned>(s);
    if (index < 3) return index;
    else return (index - 3);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 3;
}

static inline std::string tokenToString(Symbol s) {
    switch (s) {
        case Symbol::OpenBrace: return "OpenBrace";
        case Symbol::CloseBrace: return "CloseBrace";
        case Symbol::Comma: return "Comma";
        case Symbol::Id: return "Id";
        case Symbol::Eof: return "Eof";
        default:
            return "Unknown";
    }
}

using SymbolInfo = std::pair<Symbol, std::string>;

class Lexer {
public:
    Lexer(const std::vector<SymbolInfo>& tklst): tklist(tklst) {
        it = tklist.begin();
    }

    Symbol getNextToken() {
        if (it == tklist.end()) {
            return Symbol::Eof;
        }
        Symbol tk = it->first;
        text = it->second;
        it++;
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }
    std::string getText() { return text; }
    std::string toString() {
        auto it2 = it;
        std::ostringstream out;

        out << "{";
        while (it2 != tklist.end()) {
            out << tokenToString(it2->first) << ",";
            it2++;
        }
        out << "}";
        return out.str();
    }

private:
    std::string text;
    std::vector<SymbolInfo> tklist;
    std::vector<SymbolInfo>::iterator it;
};

#endif
