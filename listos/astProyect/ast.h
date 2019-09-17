#include <memory>
#include <string>
#include <math.h>
#include <vector>
#include <iostream>
#include <unordered_map>

using std::move;
using std::to_string;
using std::string;
using std::vector;
using std::cout;
using std::shared_ptr;
using std::unordered_map;

#define UNINITIALIZED -73

struct entry {
    string tipo;
    int value;
};
struct Context {
    unordered_map<string, entry> vars;
    unordered_map<string, vector<entry>> arreglos;
    unordered_map<string, int> size_arreglos;
};
class ASTNode {
    public:
        virtual string toString() = 0;
};

class Expr : public ASTNode {
    public:
        virtual int eval(Context&) = 0;
        int8_t getPrec() { return prec; }

    protected:
        int8_t prec;
};
using EXPR = shared_ptr<Expr>;

class BinExpr : public Expr {
    public:
        BinExpr(EXPR&&, EXPR&&, int8_t);

    protected:
        EXPR expr1;
        EXPR expr2;
};


#define DEFINE_BINARY_EXPR(name, oper, prec) \
class name##Expr : public BinExpr { \
    public: \
        name##Expr(EXPR e1, EXPR e2) : BinExpr(move(e1), move(e2), prec) {} \
        int eval(Context& ctx) override {  \
                return expr1->eval(ctx) oper expr2->eval(ctx); \
        } \
        string toString() override { \
            return expr1->toString() + #oper + expr2->toString(); \
        } \
};
class PowExpr : public BinExpr {
    public:
        PowExpr(EXPR, EXPR);
        int eval(Context&) override;
        string toString() override;
};

class NegExpr : public Expr {
    public:
        NegExpr(EXPR);
        int eval(Context&) override;
        string toString() override;

    private:
        EXPR expr;
};

class NotExpr : public Expr {
    public:
        NotExpr(EXPR);
        int eval(Context&) override;
        string toString() override;

    private:
        EXPR expr;
};

DEFINE_BINARY_EXPR(Equals,==,5);
DEFINE_BINARY_EXPR(NotEquals,!=,5);
DEFINE_BINARY_EXPR(LessThan,<,5);
DEFINE_BINARY_EXPR(GreatherThan,>,5);
DEFINE_BINARY_EXPR(LessThanEQ,<=,5);
DEFINE_BINARY_EXPR(GreatherThanEQ,>=,5);
DEFINE_BINARY_EXPR(Add,+,4);
DEFINE_BINARY_EXPR(sub,-,4);
DEFINE_BINARY_EXPR(Or,||,4);
DEFINE_BINARY_EXPR(Mult,*,3);
DEFINE_BINARY_EXPR(Div,/,3);
DEFINE_BINARY_EXPR(Mod,%,3);
DEFINE_BINARY_EXPR(And,&&,3);

#define DEFINE_CONSTEXPR(name, type)                     \
class name##Expr : public Expr {                         \
    public:                                              \
        name##Expr(type val) : value(val) {              \
            prec = -1;                                   \
        }                                                \
        int eval(Context&) override { return value; }    \
        string toString() override {                     \
            return to_string(value);                     \
        }                                                \
        type getValue() { return value; }                \
    private:                                             \
        type value;                                      \
};

class IdentExpr : public Expr {
    public:
        IdentExpr(string, EXPR);
        int eval(Context&) override;
        string toString() override;
        string getType(Context&);
    private:
        string id;
        EXPR array_expr;
};

DEFINE_CONSTEXPR(Num, int);
DEFINE_CONSTEXPR(Char, char);
DEFINE_CONSTEXPR(Bool, bool);


class Statement : public ASTNode {
    public:
        virtual void exec(Context&) = 0;
};

using STATEMENTP = shared_ptr<Statement>;
using STATEMENT = vector<STATEMENTP>;

class WriteStmt : public Statement {
    public:
        WriteStmt(vector<string>&, vector<EXPR>&);
        void exec(Context&) override;
        string toString() override;

    private:
        vector<string> exprs_type;
        vector<EXPR> exprs;
};

class DeclareStmt : public Statement {
    public:
        DeclareStmt(vector<string>&, string);
        void exec(Context&) override;
        string toString() override;

    private:
        vector<string> ids;
        string tipo;
};

class AssignStmt : public Statement {
    public:
        AssignStmt(string, EXPR);
        void exec(Context&) override;
        string toString() override;
        string getId() { return id; }
    
    private:
        string id;
        EXPR val;
};

class WhileStmt : public Statement {
    public:
        WhileStmt(EXPR, STATEMENT&);
        void exec(Context&) override;
        string toString() override;

    private:
        EXPR expr;
        STATEMENT list;
};

class IfStmt : public Statement {
    public:
        IfStmt(EXPR, STATEMENT&, vector<EXPR>&, vector<STATEMENT>&,
               STATEMENT&);
        void exec(Context&) override;
        string toString() override;

    private:
        EXPR expr_if;
        STATEMENT stmts_if;
        vector<EXPR> expr_elsif;
        vector<STATEMENT> stmts_elsif;
        STATEMENT stmts_else;
};

class ForStmt : public Statement {
    public:
        ForStmt(shared_ptr<AssignStmt>&, EXPR, STATEMENT&);
        void exec(Context&) override;
        string toString() override;

    private:
        shared_ptr<AssignStmt> inicio;
        EXPR breque;
        STATEMENT stmts;
};

class DoWhileStmt : public Statement {
    public:
        DoWhileStmt(EXPR, STATEMENT&);
        void exec(Context&) override;
        string toString() override;

    private:
        EXPR expr;
        STATEMENT lista;
};