#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <unordered_map>
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
    std::unordered_map<std::string, int> vars1 = { {"x", 5}, {"y", 9}};
    std::unordered_map<std::string, int> vars2 = { {"x", 12}, {"y", 0}};
    ASTNode *e = AND(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 1);
    CHECK(e->eval(vars2) == 0);
}

TEST_CASE("Or expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 0}, {"y", 0}};
    std::unordered_map<std::string, int> vars2 = { {"x", 15}, {"y", 0}};
    ASTNode *e = OR(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 0);
    CHECK(e->eval(vars2) == 1);
}

TEST_CASE("Greater Than expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 10}, {"y", 30}};
    std::unordered_map<std::string, int> vars2 = { {"x", 30}, {"y", 10}};
    ASTNode *e = GT(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 0);
    CHECK(e->eval(vars2) == 1);
}

TEST_CASE("Greater Or Equal expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 10}, {"y", 30}};
    std::unordered_map<std::string, int> vars2 = { {"x", 30}, {"y", 10}};
    std::unordered_map<std::string, int> vars3 = { {"x", 30}, {"y", 30}};
    ASTNode *e = GTE(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 0);
    CHECK(e->eval(vars2) == 1);
    CHECK(e->eval(vars3) == 1);
}

TEST_CASE("Less Than expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 10}, {"y", 30}};
    std::unordered_map<std::string, int> vars2 = { {"x", 30}, {"y", 10}};
    ASTNode *e = LT(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 1);
    CHECK(e->eval(vars2) == 0);
}

TEST_CASE("Less Or Equal expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 10}, {"y", 30}};
    std::unordered_map<std::string, int> vars2 = { {"x", 30}, {"y", 10}};
    std::unordered_map<std::string, int> vars3 = { {"x", 30}, {"y", 30}};
    ASTNode *e = LTE(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 1);
    CHECK(e->eval(vars2) == 0);
    CHECK(e->eval(vars3) == 1);
}

TEST_CASE("Equal expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 10}, {"y", 30}};
    std::unordered_map<std::string, int> vars2 = { {"x", 10}, {"y", 10}};
    ASTNode *e = EQ(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 0);
    CHECK(e->eval(vars2) == 1);
}

TEST_CASE("Not Equal expression") {
    std::unordered_map<std::string, int> vars1 = { {"x", 10}, {"y", 30}};
    std::unordered_map<std::string, int> vars2 = { {"x", 10}, {"y", 10}};
    ASTNode *e = NEQ(ID(x), ID(y));
    
    CHECK(e->eval(vars1) == 1);
    CHECK(e->eval(vars2) == 0);
}

TEST_CASE("Add expression") {
    std::unordered_map<std::string, int> vars = { {"x", 50} };
    ASTNode *e = ADD(ID(x), NUM(10));
    
    CHECK(e->eval(vars) == 60);
}

TEST_CASE("Sub expression") {
    std::unordered_map<std::string, int> vars = { {"x", 50} };
    ASTNode *e = SUB(ID(x), NUM(10));
    
    CHECK(e->eval(vars) == 40);
}

TEST_CASE("Mult expression") {
    std::unordered_map<std::string, int> vars = { {"x", 50} };
    ASTNode *e = MUL(ID(x), NUM(10));
    
    CHECK(e->eval(vars) == 500);
}

TEST_CASE("Div expression") {
    std::unordered_map<std::string, int> vars = { {"x", 50} };
    ASTNode *e = DIV(ID(x), NUM(10));
    
    CHECK(e->eval(vars) == 5);
}

TEST_CASE("Mod expression") {
    std::unordered_map<std::string, int> vars = { {"x", 100} };
    ASTNode *e = MOD(ID(x), NUM(3));
    
    CHECK(e->eval(vars) == 1);
}

TEST_CASE("Combined expression (Add/Sub)") {
    std::unordered_map<std::string, int> vars = { {"x", 570}, {"y", 60} };
    ASTNode *e = MUL(ADD(NUM(10), ID(y)), SUB(ID(x), NUM(580)));
    
    CHECK(e->eval(vars) == -700);
}

TEST_CASE("Combined expression (Div/Mod)") {
    std::unordered_map<std::string, int> vars = { {"x", 570}, {"y", 60} };
    ASTNode *e = MOD(DIV(ADD(ID(x), NUM(10)), ID(y)), NUM(13));
    
    CHECK(e->eval(vars) == 9);
}

TEST_CASE("Assign Statement") {
    std::unordered_map<std::string, int> vars = { {"z", 10}, {"y", 60} };
    ASTNode *e = ASSIGN("x", ADD(ID(y), ID(z)));
    e->eval(vars);
    
    CHECK(vars["x"] == 70);
}

TEST_CASE("If Statement") {
    std::unordered_map<std::string, int> vars = { {"x", 570}, {"y", 60}, {"z", 10} };
    ASTNode *e = IF(GT(ID(x), ID(y)), ASSIGN("x", ADD(ID(y), ID(z))), ASSIGN("x", SUB(ID(y), NUM(10))));
    e->eval(vars);

    CHECK(vars["x"] == 70);
}

TEST_CASE("While Statement") {
    std::unordered_map<std::string, int> vars = { {"x", 0}, {"y", 15} };
    ASTNode *e = WHILE(LT(ID(x), ID(y)), ASSIGN("x", ADD(ID(x), NUM(1))));
    
    e->eval(vars);
    CHECK(vars["x"] == 15);
}