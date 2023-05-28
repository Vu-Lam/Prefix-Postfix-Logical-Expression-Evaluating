//
// Created by Lam Vu on 21/05/2023.
//

#ifndef PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_LOGICAL_H
#define PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_LOGICAL_H
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <stack>
#include <algorithm>
#include <iomanip>
using namespace std;
struct Variable {
    int boolean_number;
    string character;
};
bool isAvailableLogic(const string& input);
bool isLogicOperand (const string& input);
int preference(const string & symbol);
bool isOperator(const string & symbol);
string LogicInfix2Postfix(const string& infix_notation);
string LogicInfix2Prefix(string infix_notation);
string LogicPostfixPrefixCalculator(string expression, const string& value);
#endif //PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_LOGICAL_H
