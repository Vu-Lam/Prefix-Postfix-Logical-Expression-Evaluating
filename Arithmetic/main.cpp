//
// Created by Lam Vu on 20/05/2023.
//
#include "Postfix_prefix.h"
#include "Logical.h"
int main() {
    cout << "\n\t\t STRING TEST\n";
    string infix_notation = "(11+2)*3";
    cout << "Postfix notation: " <<Infix2Postfix("2//3") << endl;
    cout << "Prefix notation: " <<Infix2Prefix(infix_notation) << endl;
    cout << "calculate from postfix: " << PostfixPrefixCalculator(Infix2Postfix("2/3*2")) << endl;
    cout << "calculate from prefix: " << PostfixPrefixCalculator("/ ^ * + 123 456 - 789 321 2 + 654 321") << endl;
    cout << "\t\t TEST LOGICAL EXPRESSION\n ";
    string Logical_infix_notation = "r|(p&q)";
    cout << LogicInfix2Postfix(Logical_infix_notation) << endl;
    return 0;
}