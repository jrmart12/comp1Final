#ifndef _AST_H
#define _AST_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class Expr;
class Stmt;
using PExpr = std::unique_ptr<Expr>;
using ExprList = std::vector<PExpr>; //CAMBIIO
using PStmt = std::unique_ptr<Stmt>;
using StmtList = std::vector<PStmt>;

class Context {
public:
    Context(){};
    std::unordered_map<std::string,int> vars;
};


class ASTNode {
public:
    ASTNode() {}
    virtual ~ASTNode() {}
};

class Expr: public ASTNode {
public:
    Expr(){};
    virtual std::string getType() = 0;
    virtual int eval(Context& ctx) = 0;
};

class AddExpr: public Expr {
public:
    AddExpr(PExpr expr1, PExpr expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)){};
    int eval(Context& ctx){
        int ex1 = expr1->eval(ctx);
        int ex2 = expr2->eval(ctx);
        int res = ex1 + ex2;
        return res;
    };
    std::string getType(){return "Num";};
    PExpr expr1, expr2;
};

class SubExpr: public Expr {
public:
    SubExpr(PExpr expr1, PExpr expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)){};
    int eval(Context& ctx){
        int ex1 = expr1->eval(ctx);
        int ex2 = expr2->eval(ctx);
        int res = ex1 - ex2;
        return res;
    };
    std::string getType(){return "Num";};
    PExpr expr1, expr2;
};

class MulExpr: public Expr {
public:
    MulExpr(PExpr expr1, PExpr expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)){};

    int eval(Context& ctx){
        int ex1 = expr1->eval(ctx);
        int ex2 = expr2->eval(ctx);
        int res = ex1 * ex2;
        return res;
    };
    std::string getType(){return "Num";};
    PExpr expr1, expr2;
};

class DivExpr: public Expr {
public:
    DivExpr(PExpr expr1, PExpr expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)){};

    int eval(Context& ctx){
        int ex1 = expr1->eval(ctx);
        int ex2 = expr2->eval(ctx);
        int res = ex1 / ex2;
        return res;
    };
    std::string getType(){return "Num";};
    PExpr expr1, expr2;
};

class IdExpr: public Expr {
public:
    IdExpr(std::string name) : name(name){};
    int eval(Context& ctx){
        return ctx.vars.operator[](name);
    };
    std::string getType(){return "Id";};
    std::string name;
};

class NumExpr: public Expr {
public:
    NumExpr(int value) : value(value){};
    int eval(Context& ctx){return value;};
    std::string getType(){return "Num";};
    int value;
};

class Stmt: public ASTNode {
public:
    Stmt(){};
    virtual void exec(Context& ctx) = 0;
};

class AssignStmt : public Stmt {
public:
    AssignStmt(std::string id, PExpr val): id(id),val(std::move(val)){};
    void exec(Context& ctx){
        int valor = val->eval(ctx);
        std::cout << "VALUE: " << valor << std::endl;
        ctx.vars.emplace(id,valor);
    };
    PExpr val;
    std::string id;
};

class IfStmt : public Stmt {
public:
    IfStmt(PExpr e, PStmt st1, PStmt st2):e(std::move(e)),st1(std::move(st1)),st2(std::move(st2)){};
    void exec(Context& ctx){
        int valor = e->eval(ctx);
	if(valor)
		st1->exec(ctx);
	st2->exec(ctx);
    };
    PExpr e;
    PStmt st1, st2;
};

class BlockStmt: public Stmt {
public:
    BlockStmt(StmtList stmt_list): stmt_list(std::move(stmt_list)){};
    void exec(Context& ctx){
        //std::cout << "SIZE: " <<stmt_list.size() << std::endl;
        for(int a = 0; a < stmt_list.size(); a++){
            stmt = std::move(stmt_list.at(a));
            stmt->exec(ctx);
        }     
    };
    PStmt stmt;
    StmtList stmt_list;
};

/*
#define ASSIGN(id, e) (std::make_unique<AssignStmt>(id, e))
#define IF(e, st1, st2) (std::make_unique<IfStmt>(e, st1, st2))
#define BLOCK(l) (std::make_unique<BlockStmt>(std::move(l)))


*/
#endif
