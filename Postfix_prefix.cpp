//
// Created by Lam Vu on 20/05/2023.
//

#include "Postfix_prefix.h"

int preference(const char& mathOperator) {
    switch (mathOperator) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return -1;
    }
}
bool isOperand(const char& symbol) {
    return symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7' || symbol == '8' || symbol == '9';
}
bool isOperator (const char& symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}
string Infix2Postfix(const string& infix_notation) {
    stack <string> newStack;
    string postfix_notation;
    for (size_t i = 0; i < infix_notation.size(); i++) {
        char symbol = infix_notation[i];
        if(isOperand(symbol)) {
            string stringNumber;
            while (isOperand(infix_notation[i]) && i < infix_notation.size()) {
                stringNumber += string(1,infix_notation[i]);
                ++i;
            }
            stringNumber += " ";
            postfix_notation += stringNumber;
            symbol =  infix_notation[i];
        }
        if(symbol == '(') {
            newStack.emplace("(");
        }
        if(symbol == ')') {
            while (!newStack.empty() && newStack.top()!="(") {
                postfix_notation+=newStack.top();
                postfix_notation+=" ";
                newStack.pop();
            }
            if (!newStack.empty() && newStack.top() == "(") {
                newStack.pop();
            }
        }
        if(isOperator(symbol)) {
            while (!newStack.empty() && preference(newStack.top()[0]) >= preference(symbol)) {
                postfix_notation += newStack.top();
                postfix_notation+=" ";
                newStack.pop();
            }
            newStack.emplace(1, symbol);
        }
    }
    while (!newStack.empty()) {
        postfix_notation += newStack.top();
        postfix_notation+=" ";
        newStack.pop();
    }
    postfix_notation.erase(postfix_notation.size()-1);
    return postfix_notation;
}
string Infix2Prefix(string infix_notation){
    stack <string> newStack;
    string prefix_notation;
    reverse(infix_notation.begin(),infix_notation.end());
//    cout << "After reverse: " << infix_notation << endl;
    size_t length = infix_notation.size();
    for(std::size_t i = 0; i < length; i++) {
        char symbol = infix_notation[i];
        if(isOperand(symbol)) {
            string stringNumber;
            while (isOperand(infix_notation[i]) && i < infix_notation.size()) {
                stringNumber += string(1,infix_notation[i]);
                ++i;
            }
            stringNumber += " ";
            prefix_notation += stringNumber;
            symbol =  infix_notation[i];
        }
        if(symbol == ')') {
            newStack.emplace("(");
        }
        if(symbol == '(') {
            while (!newStack.empty() && newStack.top()!="(") {
                prefix_notation+=newStack.top();
                prefix_notation+=" ";
                newStack.pop();
            }
            if (!newStack.empty() && newStack.top() == "(") {
                newStack.pop();
            }
        }
        if(isOperator(symbol)) {
            if(newStack.empty())
                newStack.emplace(1, symbol);
            else if (preference(symbol) > preference(newStack.top()[0])) {
                newStack.emplace(1, symbol);
            }
            else if (preference(symbol) == preference(newStack.top()[0]) && symbol == '^') {
                while (preference(symbol) == preference(newStack.top()[0]) && symbol == '^') {
                    prefix_notation += newStack.top();
                    prefix_notation +=" ";
                    newStack.pop();
                }
                newStack.emplace(1,symbol);
            }
            else if (preference(symbol) == preference((newStack.top()[0]))) {
                newStack.emplace(1,symbol);
            }
            else if (preference(symbol) < preference(newStack.top()[0])) {
                while (!newStack.empty() && preference(symbol) < preference(newStack.top()[0]) ) {
                    prefix_notation += newStack.top();
                    prefix_notation +=" ";
                    newStack.pop();
                }
                newStack.emplace(1,symbol);
            }
        }
    }
    while (!newStack.empty()) {
        prefix_notation += newStack.top();
        prefix_notation+=" ";
        newStack.pop();
    }
    prefix_notation.erase(prefix_notation.size()-1);
    reverse(prefix_notation.begin(), prefix_notation.end());
    return prefix_notation;
}
string PostfixPrefixCalculator(const string& expression) {
    stack <double> newStack;
    // postfix evaluating
    if (isOperand(expression[0])) {
        for(size_t i = 0; i < expression.size(); i++) {
            char symbol = expression[i];
            if(symbol == ' ') continue;
            if(isOperand(symbol)) {
                string stringNumber;
                while (isOperand(expression[i]) && i < (int)expression.size()) {
                    stringNumber += string(1,expression[i]);
                    ++i;
                }
                newStack.push(stoi(stringNumber));
                symbol =  expression[i];
            }
            if(isOperator(symbol)) {
                 double before = newStack.top(); newStack.pop();
                 double after = newStack.top(); newStack.pop();
                switch (symbol) {
                    case '+' : {
                        newStack.push(after+before); break;
                    }
                    case '-' : {
                        newStack.push(after-before); break;
                    }
                    case '*' : {
                        newStack.push(after*before); break;
                    }
                    case '/' : {
                        newStack.push(after/before); break;
                    }
                    case '^': {
                        newStack.push(pow(after,before)); break;
                    }
                }
            }
        }
    }
    else if (isOperator(expression[0])) {
        for(int i = (int)expression.size() - 1; i >= 0 ; i--) {
            char symbol = expression[i];
            if(symbol == ' ') continue;
            if(isOperand(symbol)) {
                string stringNumber;
                while (isOperand(expression[i]) && i < expression.size()) {
                    stringNumber += string(1,expression[i]);
                    i--;
                }
                reverse(stringNumber.begin(),stringNumber.end());
                newStack.push(stoi(stringNumber));
                symbol =  expression[i];
            }
            if(isOperator(symbol)) {
                double before = newStack.top(); newStack.pop();
                double after = newStack.top(); newStack.pop();
//                cout << "Before: " << before << endl;
//                cout << "After: " << after << endl;
//                cout << "Operator: " << symbol << endl;
                switch (symbol) {
                    case '+' : {
                        newStack.push(before+after); break;
                    }
                    case '-' : {
                        newStack.push(before-after); break;
                    }
                    case '*' : {
                        newStack.push(before*after); break;
                    }
                    case '/' : {
                        newStack.push(before/after); break;
                    }
                    case '^': {
                        newStack.push(pow(before,after)); break;
                    }
                }
            }
        }
    }
    else {
        clog << "Invalid expression\n";
        return "0";
    }
    stringstream result;
    double doubleResult = round(newStack.top()*pow(10,4))/pow(10,4);
    result << fixed << setprecision(4) << doubleResult;
    string stringResult = result.str();
    while(stringResult[stringResult.size()-1]== '0') {
        stringResult.erase(stringResult.size()-1);
    }
    if(stringResult[stringResult.size()-1]== '.') {
        stringResult.erase(stringResult.size()-1);
    }
    return stringResult;
}
