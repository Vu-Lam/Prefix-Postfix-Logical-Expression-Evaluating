//
// Created by Lam Vu on 28/05/2023.
//

#ifndef PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_SUBMIT_H
#define PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_SUBMIT_H


#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <stack>
#include <algorithm>
#include <iomanip>
using namespace std;
int preference (const char& mathOperator);
bool isOperand(const char& symbol);
bool isOperator (const char& symbol);
bool isAvailableInput(const string& input);
string Infix2Postfix(const string& infix_notation);
string Infix2Prefix(string infix_notation);
string PostfixPrefixCalculator (const string& expression);
struct Variable {
    int boolean_number;
    string character;
};
bool isAvailableLogic(const string& input);
bool isLogicOperand (const string& input);
int preferenceLogic(const string & symbol);
bool isOperatorLogic(const string & symbol);
string LogicInfix2Postfix(const string& infix_notation);
string LogicInfix2Prefix(string infix_notation);
string LogicPostfixPrefixCalculator(string expression, const string& value);
#endif //PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_SUBMIT_H
