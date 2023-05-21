//
// Created by Lam Vu on 20/05/2023.
//

#ifndef PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_POSTFIX_PREFIX_H
#define PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_POSTFIX_PREFIX_H
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
#endif //PREFIX_POSTFIX_LOGICAL_EXPRESSION_EVALUATING_POSTFIX_PREFIX_H
