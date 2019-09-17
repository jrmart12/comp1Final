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

int AddExpr::eval(){
	int x = expr1->eval();
	int y = expr2->eval();
	int res = x + y;
	return res;
}

int SubExpr::eval(){
	int x = expr1->eval();
	int y = expr2->eval();
	int res = x - y;
	return res;
}

int MulExpr::eval(){
	int x = expr1->eval();
	int y = expr2->eval();
	int res = x * y;
	return res;
}

int DivExpr::eval(){
	int x = expr1->eval();
	int y = expr2->eval();
	int res = x / y;
	return res;
}

int ModExpr::eval(){
	int x = expr1->eval();
	int y = expr2->eval();
	int res = x % y;
	return res;
}