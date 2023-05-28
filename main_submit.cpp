//
// Created by Lam Vu on 28/05/2023.
//
#include "submit.h"
int main() {
    string infix_arithmetic = "1+2";
    string infix_logical = "A&B";
    cout << "\t\tARITHMETIC\n";
    cout << "Infix: " << infix_arithmetic << endl;
    cout << "Postfix: " << Infix2Postfix(infix_arithmetic) << endl;
    cout << "Prefix: " << Infix2Prefix(infix_arithmetic) << endl;
    cout << "Result:" << PostfixPrefixCalculator(Infix2Prefix(infix_arithmetic)) << endl;
    cout << "\t\tLOGICAL\n";
    cout << "Infix: " << infix_logical << endl;
    cout << "Postfix: " << LogicInfix2Postfix(infix_logical) << endl;
    cout << "Prefix: " << LogicInfix2Prefix(infix_logical) << endl;
    cout << "Value: A B 1 1\n";
    cout << "Result: " << LogicPostfixPrefixCalculator(LogicInfix2Postfix(infix_logical),"A B 1 1") << endl;
    return 0;
}