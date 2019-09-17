#ifndef _AST_H
#define _AST_H
#include  <memory>
#include <string>
#include <unordered_map>
#include <iostream>

class ASTNode {
    public:
        virtual ~ASTNode(){}
        virtual std::string toString() = 0;
        virtual int eval(std::unordered_map<std::string, int>& vars) = 0;
};

using PASTNode = ASTNode *;

#define BINARY_EXPR(name, op) \
    class name##Expr : public ASTNode { \
        public : \
        name##Expr(PASTNode expr1, PASTNode expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)) {} \
        int eval(std::unordered_map<std::string, int>& vars) { \
            return expr1->eval(vars) op expr2->eval(vars); \
        }\
        std::string toString() { \
            return "(" + expr1->toString() +")" + #op + "(" + expr2->toString() +")";\
        } \
    PASTNode expr1;\
    PASTNode expr2;\
    };

BINARY_EXPR(And, &&);
BINARY_EXPR(Or, ||);
BINARY_EXPR(GT, >);
BINARY_EXPR(GTE, >=);
BINARY_EXPR(LT, <);
BINARY_EXPR(LTE, <=);
BINARY_EXPR(EQ, ==);
BINARY_EXPR(NEQ, !=);
BINARY_EXPR(Add, +);
BINARY_EXPR(Sub, -);
BINARY_EXPR(Div, /);
BINARY_EXPR(Mul, *);
BINARY_EXPR(Mod, %);

class IdentExpr : public ASTNode {
    public: 
    IdentExpr(std::string var) {
        name = var;
    }
    int eval(std::unordered_map<std::string, int>& vars){ return vars[name]; }
    std::string toString() { return name; }
    std::string name;
};

class NumExpr : public ASTNode{
    public:
    NumExpr(int value ) : value(value) {}
    int eval(std::unordered_map<std::string, int>& vars) { return value;}
    std::string toString() { return std::to_string(value); }
    int value;
};

class AssignStmt : public ASTNode{
public:
    AssignStmt(std::string id, PASTNode expr) :
        id(id), expr(std::move(expr)) {}
    int eval(std::unordered_map<std::string, int>& vars) { 
        vars[id] = expr->eval(vars);
        return 0;
    }
    std::string toString() { return id+ "=" + expr->toString();}
    std::string id;
    PASTNode expr;
};

class IfStmt : public ASTNode{
public:
    IfStmt(PASTNode cond, PASTNode sT, PASTNode sF) :
        cond(std::move(cond)), sT(std::move(sT)), sF(std::move(sF)) {}
    
    int eval(std::unordered_map<std::string, int>& vars) { 
        if( cond->eval(vars))
            sT->eval(vars);
        else 
            sF->eval(vars);
        return 0;
    }

    std::string toString() { 
        return "if (" + cond->toString()+ ") {\n" +  sT->toString() + "\n} else {\n" + sF->toString() + "\n}";
    }
    std::string id;
    PASTNode cond, sT, sF;
};

class WhileStmt : public ASTNode{
public:
    WhileStmt(PASTNode cond, PASTNode stmt) :
        cond(std::move(cond)), stmt(std::move(stmt)) {}
    
    int eval(std::unordered_map<std::string, int>& vars) { 
        while( cond->eval(vars))
            stmt->eval(vars);
        return 0;
    }
    
    std::string toString() { 
        return "while (" + cond->toString()+ ") {\n" +  stmt->toString() + "\n}" ;
    }
    std::string id;
    PASTNode cond, stmt;
};


#endif