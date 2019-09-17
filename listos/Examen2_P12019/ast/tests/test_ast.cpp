#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "expr_ast.h"

#define AND(x, y) (new AndExpr((x), (y)))
#define OR(x, y) (new OrExpr((x), (y)))
#define GT(x, y) (new GTExpr((x), (y)))
#define GTE(x, y) (new GTEExpr((x), (y)))
#define LT(x, y) (new LTExpr((x), (y)))
#define LTE(x, y) (new LTEExpr((x), (y)))
#define EQ(x, y) (new EQExpr((x), (y)))
#define NEQ(x, y) (new NEQExpr((x), (y)))
#define ADD(x, y) (new AddExpr((x), (y)))
#define SUB(x, y) (new SubExpr((x), (y)))
#define MUL(x, y) (new MulExpr((x), (y)))
#define DIV(x, y) (new DivExpr((x), (y)))
#define MOD(x, y) (new ModExpr((x), (y)))
#define NUM(n) (new NumExpr((n)))
#define ID(x) (new IdentExpr(#x))

#define ASSIGN(lhs, rhs) (new AssignStmt((lhs), (rhs)))
#define IF(c, t, f) (new IfStmt((c), (t), (f)))
#define WHILE(c, b) (new WhileStmt((c), (b)))

TEST_CASE("And expression") {
    ASTNode *e = AND(ID(x),ID(y));
    
    CHECK(e->toString() == "(x)&&(y)");
}

TEST_CASE("Or expression") {
    ASTNode *e = OR(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)||(y)");
}

TEST_CASE("Greater Than expression") {
    ASTNode *e = GT(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)>(y)");
}

TEST_CASE("Greater Or Equal expression") {
    ASTNode *e = GTE(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)>=(y)");
}

TEST_CASE("Less Than expression") {
    ASTNode *e = LT(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)<(y)");
}

TEST_CASE("Less Or Equal expression") {
    ASTNode *e = LTE(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)<=(y)");
}

TEST_CASE("Equal expression") {
    ASTNode *e = EQ(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)==(y)");
}

TEST_CASE("Not Equal expression") {
    ASTNode *e = NEQ(ID(x), ID(y));
    
    CHECK(e->toString() == "(x)!=(y)");
}

TEST_CASE("Add expression") {
    ASTNode *e = ADD(ID(x), NUM(10));
    
    CHECK(e->toString() == "(x)+(10)");
}

TEST_CASE("Sub expression") {
    ASTNode *e = SUB(ID(x), NUM(10));
    
    CHECK(e->toString() == "(x)-(10)");
}

TEST_CASE("Mult expression") {
    ASTNode *e = MUL(ID(x), NUM(10));
    
    CHECK(e->toString() == "(x)*(10)");
}

TEST_CASE("Div expression") {
    ASTNode *e = DIV(ID(x), NUM(10));
    
    CHECK(e->toString() == "(x)/(10)");
}

TEST_CASE("Mod expression") {
    ASTNode *e = MOD(ID(x), NUM(10));
    
    CHECK(e->toString() == "(x)%(10)");
}

TEST_CASE("Combined expression (Add/Sub)") {
    ASTNode *e = MUL(ADD(NUM(10), ID(y)), SUB(ID(x), NUM(580)));
    
    CHECK(e->toString() == "((10)+(y))*((x)-(580))");
}

TEST_CASE("Combined expression (Div/Mod)") {
    ASTNode *e = MOD(DIV(ADD(ID(x), NUM(10)), ID(y)), NUM(13));
    
    CHECK(e->toString() == "(((x)+(10))/(y))%(13)");
}

TEST_CASE("Assign Statement") {
    ASTNode *e = ASSIGN("x", ADD(ID(y), ID(z)));
    
    CHECK(e->toString() == "x=(y)+(z)");
}

TEST_CASE("If Statement") {
    ASTNode *e = IF(GT(ID(x), ID(y)), ASSIGN("x", ADD(ID(y), ID(z))), ASSIGN("x", SUB(ID(y), NUM(10))));
    
    CHECK(e->toString() == "if ((x)>(y)) {\nx=(y)+(z)\n} else {\nx=(y)-(10)\n}");
}
 
TEST_CASE("While Statement") {
    ASTNode *e = WHILE(LT(ID(x), ID(y)), ASSIGN("x", ADD(ID(x), NUM(1))));
    
    CHECK(e->toString() == "while ((x)<(y)) {\nx=(x)+(1)\n}");
}
