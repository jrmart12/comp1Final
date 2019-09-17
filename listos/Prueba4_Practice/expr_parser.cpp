#include <vector>
#include "expr_parser.h"

struct Rule {
    Symbol lhs;
    std::vector<Symbol> rhs;
    bool isEmpty() const { return rhs.empty(); }
};

Rule rule0{Symbol::SPrime, {Symbol::S}};
Rule rule1{Symbol::S, {Symbol::OpenBrace, Symbol::L, Symbol::CloseBrace}};
Rule rule2{Symbol::L, {Symbol::L, Symbol::Comma, Symbol::Id}};
Rule rule3{Symbol::L, {Symbol::Id}};
Rule none;

enum ActionType { Accept, Shift, Reduce, Empty };
struct Action {
    Action(): 
        type(ActionType::Empty),
        state(-1),
        rule(none) {}

    Action(ActionType type):
        type(type),
        state(-1),
        rule(none) {}
    
    Action(unsigned state):
        type(ActionType::Shift),
        state(state),
        rule(none) {}
    
    Action(Rule& rule):
        type(ActionType::Reduce),
        state(-1),
        rule(rule) {}

    Action(Symbol s):
        type(ActionType::Shift),
        sym(s),
        state(-1),
        rule(none) {}
    ActionType type;
    int state;
    Rule& rule;
    Symbol sym;
    bool isSymbol() { return state == -1; }
};

Action empty;
Action s1(1);
Action s3(3);
Action s5(5);
Action s6(6);
Action s7(7);
Action r0(rule0); // Reduce rule 0: S' -> S
Action r1(rule1); // Reduce rule 1: S -> { L }
Action r2(rule2); // Reduce rule 2: L -> L , id
Action r3(rule3); // Reduce rule 3: L -> id
Action accept(ActionType::Accept);

                /* { } , Id $ */
std::vector<std::vector<Action>> lr0_action = {
    /* State 0 */{s1,empty,empty,empty,empty},
    /* State 1 */{empty,empty,empty,s3,empty},
    /* State 2 */{empty,empty,empty,empty,accept},
    /* State 3 */{r3,r3,r3,r3,r3},
    /* State 4 */{empty,s6,s5,empty,empty},
    /* State 5 */{empty,empty,empty,s7,empty},
    /* State 6 */{r1,r1,r1,r1,r1},
    /* State 7 */{r2,r2,r2,r2,r2}
};

/* SPrime S L */
std::vector<std::vector<int>> lr0_goto = {
    /* State 0 */{ -1, 2, -1 }, 
    /* State 1 */{ -1, -1, 4 },
    /* State 2 */{ -1, -1, -1 },
    /* State 3 */{ -1, -1, -1 },
    /* State 4 */{ -1, -1, -1 },
    /* State 5 */{ -1, -1, -1 },
    /* State 6 */{ -1, -1, -1 },
    /* State 7 */{ -1, -1, -1 }
};


int Parser::parse(int count[4]){
     for (int i=0; i < 4; ++i)
        count[i] = 0;
    list<Action> stack;
    Symbol tk = lexer.getNextToken();

    Action primerNum(0);
    stack.push_front(primerNum);
    
    while (true) {
        Action actual = stack.front();        

        if (actual.isSymbol()) {
            std::cout<<"entroSymbol: "<<tokenToString(tk)<<actual.state<<std::endl;
            int temp = indexOf(actual.sym);
            auto it = std::next(stack.begin(), 1);
            Action nuevo(lr0_goto[it->state][temp]);
            stack.push_front(nuevo);
        } else if (actual.state != -1) {
            Action temp = lr0_action[actual.state][indexOf(tk)];
            if (temp.type == ActionType::Reduce) {
                std::cout<<"entroTk: "<<tokenToString(tk)<<temp.state<<std::endl;
                int cant = temp.rule.rhs.size();
                cant = cant << 1;
                for (int i=0; i < cant; i++)
                    stack.pop_front();
                Action nuevo(temp.rule.lhs);
                stack.push_front(nuevo);
                if (temp.rule.lhs == rule1.lhs)
                    count[0]++;
                else if (temp.rule.rhs == rule2.rhs)
                    count[2]++;
                else if (temp.rule.lhs == rule3.lhs)
                    count[1]++;
            }else if (temp.type == ActionType::Shift) {
                std::cout<<"entroTkSift: "<<tokenToString(tk)<<temp.state<<std::endl;
                Action nuevo(tk);
                stack.push_front(nuevo);
                Action nuevo1(temp.state);
                stack.push_front(nuevo1);
                tk = lexer.getNextToken();
                std::cout<<"TokenNext: "<<tokenToString(tk)<<temp.state<<std::endl;
            }
            else if (temp.type == ActionType::Accept) {
                count[3]++;
                return 1;
            }
        }
    }
}