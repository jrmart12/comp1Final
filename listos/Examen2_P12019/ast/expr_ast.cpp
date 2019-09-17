#include "expr_ast.h"

std::string AddExpr::toString(){
	return "("+expr1->toString()+")"+"+"+"("+expr2->toString()+")";
}

std::string SubExpr::toString(){
	return "("+expr1->toString()+")"+"-"+"("+expr2->toString()+")";
}

std::string MulExpr::toString(){
	return "("+expr1->toString()+")"+"*"+"("+expr2->toString()+")";
}

std::string DivExpr::toString(){
	return "("+expr1->toString()+")"+"/"+"("+expr2->toString()+")";
}

std::string ModExpr::toString(){
	return "("+expr1->toString()+")"+"%"+"("+expr2->toString()+")";
}

std::string AndExpr::toString(){
    return "("+expr1->toString()+")"+"&&"+"("+expr2->toString()+")";
}

std::string OrExpr::toString(){
    return "("+expr1->toString()+")"+"||"+"("+expr2->toString()+")";
}

std::string GTExpr::toString(){
    return "("+expr1->toString()+")"+">"+"("+expr2->toString()+")";
}

std::string GTEExpr::toString(){
    return "("+expr1->toString()+")"+">="+"("+expr2->toString()+")";
}

std::string LTExpr::toString(){
    return "("+expr1->toString()+")"+"<"+"("+expr2->toString()+")";
}

std::string LTEExpr::toString(){
    return "("+expr1->toString()+")"+"<="+"("+expr2->toString()+")";
}

std::string EQExpr::toString(){
    return "("+expr1->toString()+")"+"=="+"("+expr2->toString()+")";
}

std::string NEQExpr::toString(){
    return "("+expr1->toString()+")"+"!="+"("+expr2->toString()+")";
}


std::string AssignStmt::toString(){
    return id+"="+val->toString();
}

std::string IfStmt::toString(){
    return "if ("+e->toString()+") {\n"+st1->toString()+"\n}"+" else {\n"+st2->toString()+"\n}";
}

std::string WhileStmt::toString(){
    return "while ("+e->toString()+") {\n"+st1->toString()+"\n}";
}