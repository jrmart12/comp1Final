#ifndef _AST_H
#define _AST_H

#include <string>
#include <memory>
#include <iostream>

class ASTNode {
    public:
        ASTNode(){}
        virtual std::string toString() = 0;
        virtual int eval() = 0;
};

class NumExpr : public ASTNode {
public:
    NumExpr(int val): value(val){}
    std::string toString(){
        return std::to_string(value);
    };
    int eval(){return value;};
    int value;
};

class BinaryExpr : public ASTNode { 
    public:
        BinaryExpr(ASTNode * expr1, ASTNode * expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)){}
        ASTNode * expr1, * expr2;
        std::string toString(){};
        int eval(){};
};

#define DEFINE_BINARY_EXPR(name) \  
class name##Expr : public BinaryExpr { \
    public: \
        name##Expr (ASTNode * expr1, ASTNode * expr2): \
        BinaryExpr(std::move(expr1),std::move(expr2)){}; \
        std::string toString(); \
        int eval(); \
}; \

DEFINE_BINARY_EXPR(Add);
DEFINE_BINARY_EXPR(Sub);
DEFINE_BINARY_EXPR(Mul);
DEFINE_BINARY_EXPR(Div);
DEFINE_BINARY_EXPR(Mod);

class IdExpr : public ASTNode {
public:
    IdExpr(std::string name) : name(name){}
    std::string name;
    std::string toString(){
        return name;
    };
    int eval(){return 1;};
};

class PrintExpr : public ASTNode {
public:
    PrintExpr(ASTNode * exp) : exp(exp){}
    ASTNode * exp;
    std::string toString(){
        std::cout << "print(\""<< exp->toString()<< "\")"<<std::endl;
        return "print(\""+exp->toString()+ "\")";
    };
    int eval(){};
};


#endif
