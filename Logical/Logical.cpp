//
// Created by Lam Vu on 21/05/2023.
//
#include "Logical.h"
bool isAvailableLogic(const string& input) {
    for(size_t i = 0; i < input.size()-2; i++) {
        if(input[i] == '|' && input[i+1] == '|') { cout << "undefined error\n";return false;}
        if(input[i] == '&' && input[i+1] == '&') { cout << "undefined error\n";return false;}
        if(input[i] == '|' && input[i+1] == '&') { cout << "undefined error\n";return false;}
        if(input[i] == '&' && input[i+1] == '|') { cout << "undefined error\n";return false;}
    }
    return true;
}
bool isLogicOperand(const string& input) {
    return ("a" <= input && input <= "z") || ("A" <= input && input <= "Z");
}
int preference(const string& symbol) {
    if(symbol == "~") return 4;
    if(symbol == "&" || symbol == "|") return 3;
    if(symbol == "->") return 2;
    if(symbol == "<->") return 1;
    else return 0;
}
bool isOperator(const string & symbol) {
    return symbol == "~" || symbol == "&" || symbol == "|" || symbol == "->" || symbol == "<->";
}
string LogicInfix2Postfix(const string& infix_notation) {
    if(!isAvailableLogic(infix_notation)) {
        return "";
    }
    stack <string> newStack;
    string postfix_notation;
    for (size_t i = 0; i < infix_notation.size(); i++) {
        string symbol(1,infix_notation[i]);
        if(isLogicOperand(symbol)) {
            postfix_notation += symbol;
        }
        if(symbol == "(") {
            string openBracket = "(";
            newStack.push(openBracket);
        }
        if(symbol == ")") {
            while (!newStack.empty() && newStack.top()!="(") {
                postfix_notation+=newStack.top();
                newStack.pop();
            }
            if (!newStack.empty() && newStack.top() == "(") {
                newStack.pop();
            }
        }
        if(!isLogicOperand(symbol)) {
            if(symbol == "-") {symbol = "->"; i++;}
            if(symbol == "<") {symbol = "<->"; i+=2;}
            if(isOperator(symbol)) {
                while (!newStack.empty() && preference(newStack.top()) >= preference(symbol)) {
                    postfix_notation+=newStack.top();
                    newStack.pop();
                }
                newStack.push(symbol);
            }
        }
    }
    while (!newStack.empty()) {
        postfix_notation+=newStack.top();
        newStack.pop();
    }
    return postfix_notation;
}
string LogicInfix2Prefix(string infix_notation) {
    if(!isAvailableLogic(infix_notation)) {
        return "";
    }
    stack <string> newStack;
    string prefix_notation;
    reverse(infix_notation.begin(),infix_notation.end());
//    cout << "Infix after reverse: " << infix_notation << endl;
    //Repair string <->, ->
    for(size_t i = 0; i < infix_notation.size()-2; i++) {
        if(infix_notation[i] == '>' && infix_notation[i+1] == '-' && infix_notation[i+2] == '<' ) {
            infix_notation[i] = '<';
            infix_notation[i+2] = '>';
        }
        if(infix_notation[i] == '>' && infix_notation[i+1] == '-' && infix_notation[i+2] != '<') {
            infix_notation[i] = '-';
            infix_notation[i+1] = '>';
        }
    }
//    cout << "Infix after reverse and change direction: " << infix_notation << endl;
    for (size_t i = 0; i < infix_notation.size(); i++) {
        string symbol(1,infix_notation[i]);
        if(isLogicOperand(symbol)) {
            prefix_notation += symbol;
        }
        if(symbol == ")") {
            string openBracket = "(";
            newStack.push(openBracket);
        }
        if(symbol == "(") {
            while (!newStack.empty() && newStack.top()!="(") {
                prefix_notation+=newStack.top();
                newStack.pop();
            }
            if (!newStack.empty() && newStack.top() == "(") {
                newStack.pop();
            }
        }
        if(!isLogicOperand(symbol)) {
            if(symbol == "-") {symbol = "->"; i++;}
            if(symbol == "<") {symbol = "<->"; i+=2;}
            if(isOperator(symbol)) {
                if(newStack.empty()) {
                    newStack.push(symbol);
                }
                else if(preference(symbol) > preference(newStack.top())) {
                    newStack.push(symbol);
                }
                else if (preference(symbol) == preference(newStack.top()) && symbol == "~") {
                    while(preference(symbol) == preference(newStack.top()) && symbol == "~") {
                        prefix_notation+=newStack.top();
                        newStack.pop();
                    }
                    newStack.push(symbol);
                }
                else if (preference(symbol) == preference(newStack.top())) {
                    newStack.push(symbol);
                }
                else if (preference(symbol) < preference(newStack.top())) {
                    while (!newStack.empty() && preference(symbol) < preference(newStack.top())) {
                        prefix_notation+=newStack.top();
                        newStack.pop();
                    }
                    newStack.push(symbol);
                }
            }
        }
    }
    while (!newStack.empty()) {
        prefix_notation+=newStack.top();
        newStack.pop();
    }
    reverse(prefix_notation.begin(), prefix_notation.end());
    //Repair string <->, ->
    for(size_t i = 0; i < prefix_notation.size()-2; i++) {
        if(prefix_notation[i] == '>' && prefix_notation[i+1] == '-' && prefix_notation[i+2] == '<' ) {
            prefix_notation[i] = '<';
            prefix_notation[i+2] = '>';
        }
        if(prefix_notation[i] == '>' && prefix_notation[i+1] == '-' && prefix_notation[i+2] != '<') {
            prefix_notation[i] = '-';
            prefix_notation[i+1] = '>';
        }
    }
    return prefix_notation;
}
string LogicPostfixPrefixCalculator(string expression, const string& value) {
    //Replace variable to boolean number
    // First step: create an arr to get character and its value
    int totalVariable = 0;
    for(size_t i = 0; i < value.size(); i++) {
        string symbol(1,value[i]);
        if(isLogicOperand(symbol)) totalVariable++;
    }
    Variable arr[totalVariable];
    int count = 0;
    int count1 = 0;
    for(size_t i = 0; i < value.size(); i++) {
        if(value[i] == ' ') continue;
        string symbol(1,value[i]);
        if(isLogicOperand(symbol)) {
            arr[count].character = symbol;
            count++;
        }
        if(!isLogicOperand(symbol)) {
            arr[count1].boolean_number = stoi(symbol);
            count1++;
        }
    }
    // Second step: change the value in the expression
    for(size_t i = 0; i < expression.size(); i++) {
        string symbol(1,expression[i]);
        if(isLogicOperand(symbol)) {
            for(int j = 0; j < totalVariable; j++) {
                if(symbol == arr[j].character) {
                    expression[i] = arr[j].boolean_number==1? '1' : '0';
                }
            }
        }
    }
//    cout <<"Expression after change: "<< expression << endl;
    stack <bool> operands_stack;
    string firstSymbol(1,expression[0]);
    if(firstSymbol == "-") firstSymbol = "->";
    if(firstSymbol == "<") firstSymbol = "<->";
    //Postfix calculate
    if(!isOperator(firstSymbol)) {
        for(size_t i = 0; i < expression.size(); i++) {
            string symbol(1,expression[i]);
            if(symbol == "0") {
                operands_stack.push(false);
            }
            if(symbol == "1") {
                operands_stack.push(true);
            }
            if(symbol == "<") { symbol = "<->"; i+=2;}
            if(symbol == "-") { symbol = "->"; i++;}
            if(isOperator(symbol)) {
               if(symbol == "~") {
                   if(operands_stack.empty()) return "FALSE";
                   bool operand =  operands_stack.top();
                   operands_stack.pop();
                   operands_stack.push(!operand);
               }
               if(symbol == "|") {
                   if(operands_stack.size() < 2) return "FALSE";
                   bool operand1 = operands_stack.top();
                   operands_stack.pop();
                   bool operand2 = operands_stack.top();
                   operands_stack.pop();
                   operands_stack.push(operand1||operand2);
               }
                if(symbol == "&") {
                    if(operands_stack.size() < 2) return "FALSE";
                    bool operand1 = operands_stack.top();
                    operands_stack.pop();
                    bool operand2 = operands_stack.top();
                    operands_stack.pop();
                    operands_stack.push(operand1&&operand2);
                }
                if(symbol == "->") {
                    if(operands_stack.size() < 2) return "FALSE";
                    bool operand1 = operands_stack.top();
                    operands_stack.pop();
                    bool operand2 = operands_stack.top();
                    operands_stack.pop();
                    operands_stack.push(!operand2||operand1);
                }
                if(symbol == "<->") {
                    if(operands_stack.size() < 2) return "FALSE";
                    bool operand1 = operands_stack.top();
                    operands_stack.pop();
                    bool operand2 = operands_stack.top();
                    operands_stack.pop();
                    operands_stack.push((operand1 && operand2) || (!operand1 && !operand2));
                }
            }
        }
    }
    //Prefix calculate
    else if(isOperator(firstSymbol)) {
        //change direction of implication from -> to <-
        if(expression[0] == '-' && expression[1] == '>') {
            expression[0] = '<';
            expression[1] = '-';
        }
        for(size_t i = 2; i < expression.size()-1; i++) {
            if(expression[i] == '-' && expression[i+1] == '>' && expression[i-1] != '<') {
                expression[i] = '<';
                expression[i+1] = '-'; i++;  // Skip the next character '-'
            }
        }
//        cout << "After change direction of implication: " << expression << endl;
        //Calculate
        for(int i = (int)expression.size()-1; i >=0; i--) {
            string symbol(1,expression[i]);
//            cout << "Symbol tracked: " << symbol << endl;
            if(symbol == "0") operands_stack.push(false);
            if(symbol == "1") operands_stack.push(true);
            if(symbol == "~") {
                if(operands_stack.empty()) return "FALSE ~";
                    bool operand = operands_stack.top();
                    operands_stack.pop();
                    operands_stack.push(!operand);
            }
            if(symbol == "|") {
                if(operands_stack.size() < 2) return "FALSE |";
                bool operand1 = operands_stack.top();
                operands_stack.pop();
                bool operand2 = operands_stack.top();
                operands_stack.pop();
                operands_stack.push(operand1||operand2);
            }
            if(symbol == "&") {
                if(operands_stack.size() < 2) return "FALSE &";
                bool operand1 = operands_stack.top();
                operands_stack.pop();
                bool operand2 = operands_stack.top();
                operands_stack.pop();
                operands_stack.push(operand1&&operand2);
            }
            if(symbol == "-") {
                i--;
                if(operands_stack.size() < 2) return "FALSE -";
                bool operand1 = operands_stack.top();
                operands_stack.pop();
                bool operand2 = operands_stack.top();
                operands_stack.pop();
                operands_stack.push(!operand1||operand2);
            }
            if(symbol == ">") {
                i-=2;
                if(operands_stack.size() < 2) return "FALSE <";
                bool operand1 = operands_stack.top();
                operands_stack.pop();
                bool operand2 = operands_stack.top();
                operands_stack.pop();
                operands_stack.push((operand1 && operand2) || (!operand1 && !operand2));
            }
        }
    }
    return operands_stack.top() ? "TRUE" : "FALSE";
}