#ifndef _AST_H
#define _AST_H

#include <string>
#include <memory>
#include <iostream>

class ASTNode {
    public:
        ASTNode(){}
        virtual std::string toString() = 0;
};

class NumExpr : public ASTNode {
public:
    NumExpr(int val): value(val){}
    std::string toString(){
        return std::to_string(value);
    };
    int value;
};

class BinaryExpr : public ASTNode { 
    public:
        BinaryExpr(ASTNode * expr1, ASTNode * expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)){}
        ASTNode * expr1, * expr2;
        std::string toString(){};
};

#define DEFINE_BINARY_EXPR(name) \  
class name##Expr : public BinaryExpr { \
    public: \
        name##Expr (ASTNode * expr1, ASTNode * expr2): \
        BinaryExpr(std::move(expr1),std::move(expr2)){}; \
        std::string toString(); \
}; \

DEFINE_BINARY_EXPR(Add);
DEFINE_BINARY_EXPR(Sub);
DEFINE_BINARY_EXPR(Mul);
DEFINE_BINARY_EXPR(Div);
DEFINE_BINARY_EXPR(Mod);
DEFINE_BINARY_EXPR(And);
DEFINE_BINARY_EXPR(Or);
DEFINE_BINARY_EXPR(GT);
DEFINE_BINARY_EXPR(GTE);
DEFINE_BINARY_EXPR(LT);
DEFINE_BINARY_EXPR(LTE);
DEFINE_BINARY_EXPR(EQ);
DEFINE_BINARY_EXPR(NEQ);

class IdentExpr : public ASTNode {
public:
    IdentExpr(std::string name) : name(name){}
    std::string name;
    std::string toString(){
        return name;
    };
};


class AssignStmt : public ASTNode {
public:
    AssignStmt(std::string id, ASTNode * val): id(id),val(std::move(val)){};
    ASTNode * val;
    std::string id;
    std::string toString();
};

class IfStmt : public ASTNode {
public:
    IfStmt(ASTNode * e, ASTNode * st1, ASTNode * st2):e(std::move(e)),st1(std::move(st1)),st2(std::move(st2)){};

    ASTNode * e;
    ASTNode * st1;
    ASTNode * st2;
    std::string toString();
};

class WhileStmt : public ASTNode {
public:
    WhileStmt(ASTNode * e, ASTNode * st1):e(std::move(e)),st1(std::move(st1)){};

    ASTNode * e;
    ASTNode * st1;
    std::string toString();
};


#endif

