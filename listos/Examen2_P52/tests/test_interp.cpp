#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <cstring>
#include <string>
#include "doctest.h"
#include "spl_ast.h"

#define ADD(x, y) (std::make_unique<AddExpr>((x), (y)))
#define SUB(x, y) (std::make_unique<SubExpr>((x), (y)))
#define MUL(x, y) (std::make_unique<MulExpr>((x), (y)))
#define DIV(x, y) (std::make_unique<DivExpr>((x), (y)))
#define MOD(x, y) (std::make_unique<ModExpr>((x), (y)))
#define NUM(n) (std::make_unique<NumExpr>((n)))
#define ID(i) (std::make_unique<IdExpr>(i))
#define ASSIGN(id, e) (std::make_unique<AssignStmt>(id, e))
#define IF(e, st1, st2) (std::make_unique<IfStmt>(e, st1, st2))
#define BLOCK(l) (std::make_unique<BlockStmt>(std::move(l)))

TEST_CASE("Assign Statement") {
    StmtList l;

    l.push_back(ASSIGN("x", ADD(NUM(100), NUM(20))));
    l.push_back(ASSIGN("y", SUB(NUM(10), NUM(20))));
    l.push_back(ASSIGN("z", ADD(ID("x"), ID("y"))));
    PStmt stmt = BLOCK(l);
    Context ctx;

    stmt->exec(ctx);
    REQUIRE(ctx.vars.size() == 3);
    CHECK(ctx.vars["x"] == 120);
    CHECK(ctx.vars["y"] == -10);
    CHECK(ctx.vars["z"] == 110);
}

TEST_CASE("If Statement") {
    PStmt stmt = IF(ID("c"),
                    ASSIGN("z", MUL(ID("x"), ID("y"))),
                    ASSIGN("z", DIV(ID("x"), ID("y")))
                   );

    Context ctx1;
    ctx1.vars["x"] = 100;
    ctx1.vars["y"] = 33;
    ctx1.vars["c"] = 1;

    stmt->exec(ctx1);
    REQUIRE(ctx1.vars.size() == 4);
    CHECK(ctx1.vars["z"] == 3300);

    Context ctx2;
    ctx2.vars["x"] = 100;
    ctx2.vars["y"] = 33;
    ctx2.vars["c"] = 0;

    stmt->exec(ctx2);
    REQUIRE(ctx2.vars.size() == 4);
    CHECK(ctx2.vars["z"] == 3);
}
