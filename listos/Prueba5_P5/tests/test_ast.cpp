#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "expr_ast.h"

#define ADD(x, y) (new AddExpr((x), (y)))
#define SUB(x, y) (new SubExpr((x), (y)))
#define MUL(x, y) (new MulExpr((x), (y)))
#define DIV(x, y) (new DivExpr((x), (y)))
#define MOD(x, y) (new ModExpr((x), (y)))
#define NUM(n) (new NumExpr((n)))
#define ID(i) (new IdExpr((i)))
#define PRINT(a) (new PrintExpr(a))


TEST_CASE("Simple expression") {
    ASTNode *e = ADD(NUM(10), NUM(20));
    
    CHECK(e->toString() == "(10)+(20)");
    CHECK(e->eval() == 30);
}

TEST_CASE("Add expression") {
    ASTNode *e = ADD(ID("s"), ADD(NUM(100), NUM(200)));
    
    CHECK(e->toString() == "(s)+((100)+(200))");
    CHECK(e->eval() == 301);
}

TEST_CASE("Sub expression") {
    ASTNode *e = SUB(ID("s"), SUB(NUM(100), NUM(200)));
    
    CHECK(e->toString() == "(s)-((100)-(200))");
    CHECK(e->eval() == 101);
}

TEST_CASE("Mult expression") {
    ASTNode *e = MUL(ID("s"), MUL(NUM(100), NUM(200)));
    
    CHECK(e->toString() == "(s)*((100)*(200))");
}

TEST_CASE("Div expression") {
    ASTNode *e = DIV(ID("s"), DIV(NUM(100), NUM(200)));
    
    CHECK(e->toString() == "(s)/((100)/(200))");
}

TEST_CASE("Mod expression") {
    ASTNode *e = MOD(ID("s"), MOD(NUM(100), NUM(200)));
    
    CHECK(e->toString() == "(s)%((100)%(200))");
}

TEST_CASE("Combined expression (Add/Sub)") {
    ASTNode *e = MUL( ADD(NUM(10), NUM(20)),
                      SUB(NUM(567), NUM(560)) );
    
    CHECK(e->toString() == "((10)+(20))*((567)-(560))");
}

TEST_CASE("Combined expression (Div/Mod)") {
    ASTNode *e = MOD( DIV( ADD(NUM(10), NUM(20)), NUM(5) ), NUM(13) );
    
    CHECK(e->toString() == "(((10)+(20))/(5))%(13)");
}

TEST_CASE("Print expression") {
    ASTNode * e = PRINT(NUM(10));
    
    CHECK(e->toString() == "print(\"10\")");
}
