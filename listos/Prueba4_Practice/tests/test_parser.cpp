#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "expr_lexer.h"
#include "expr_parser.h"

std::vector<SymbolInfo> error = {
    std::make_pair(Symbol::Id, "x"),
    std::make_pair(Symbol::Eof, "EOF")
};

std::vector<SymbolInfo> test1 = {
    std::make_pair(Symbol::OpenBrace, "{"),
    std::make_pair(Symbol::Id, "x"),
    std::make_pair(Symbol::CloseBrace, "}"),
    std::make_pair(Symbol::Eof, "EOF")
};

std::vector<SymbolInfo> test2 = {
    std::make_pair(Symbol::OpenBrace, "{"),
    std::make_pair(Symbol::Id, "x"),
    std::make_pair(Symbol::Comma, ","),
    std::make_pair(Symbol::Id, "y"),
    std::make_pair(Symbol::CloseBrace, "}"),
    std::make_pair(Symbol::Eof, "EOF")
};

std::vector<SymbolInfo> test3 = {
    std::make_pair(Symbol::OpenBrace, "{"),
    std::make_pair(Symbol::Id, "x"),
    std::make_pair(Symbol::Comma, ","),
    std::make_pair(Symbol::Id, "y"),
    std::make_pair(Symbol::Comma, ","),
    std::make_pair(Symbol::Id, "z"),
    std::make_pair(Symbol::CloseBrace, "}"),
    std::make_pair(Symbol::Eof, "EOF")
};

bool throwOnError() {
    Lexer l(error);
    Parser p(l); 

    bool throwException = false;
    int count[4];
    try {
        p.parse(count);
    } catch (...) {
        throwException = true;
    }
    return throwException;
}

TEST_CASE("Test1 {x}") {
    REQUIRE(throwOnError);
    int count[4];

    Lexer l(test1);
    Parser p(l);

    bool parseSuccess = false;
    try {
        p.parse(count);
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);
    std::string str = l.toString();
    INFO(str);
    REQUIRE(!l.hasTokens());
    CHECK(count[0] == 1);
    CHECK(count[1] == 1);
    CHECK(count[2] == 0);
    CHECK(count[3] == 1);
}

TEST_CASE("test2 {x, y}") {
    REQUIRE(throwOnError);

    Lexer l(test2);
    Parser p(l);

    bool parseSuccess = false;
    int count[4];
    try {
        p.parse(count);
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);

    std::string str = l.toString();
    INFO(str);
    REQUIRE(!l.hasTokens());
    CHECK(count[0] == 1);
    CHECK(count[1] == 1);
    CHECK(count[2] == 1);
    CHECK(count[3] == 1);
}

TEST_CASE("Test3 {x, y, z}") {
    REQUIRE(throwOnError);

    Lexer l(test3);
    Parser p(l);

    bool parseSuccess = false;
    int count[4];
    try {
        p.parse(count);
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(parseSuccess);

    std::string str = l.toString();
    INFO(str);
    REQUIRE(!l.hasTokens());
    CHECK(count[0] == 1);
    CHECK(count[1] == 1);
    CHECK(count[2] == 2);
    CHECK(count[3] == 1);
}
