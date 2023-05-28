//
// Created by Lam Vu on 28/05/2023.
//

#include "submit.h"
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
bool isAvailableInput(const string& input) {
    //Check double **, //, ^^
    for(size_t i = 0; i < input.size()-2; i++) {
        if(input[i] == '*' && input[i+1] == '*') { cout << "undefined error\n";return false;}
        if(input[i] == '/' && input[i+1] == '/') { cout << "undefined error\n";return false;}
        if(input[i] == '^' && input[i+1] == '^') { cout << "undefined error\n";return false;}
        if(input[i] == '*' && input[i+1] == '/') { cout << "undefined error\n";return false;}
        if(input[i] == '*' && input[i+1] == '^') { cout << "undefined error\n";return false;}
        if(input[i] == '/' && input[i+1] == '*') { cout << "undefined error\n";return false;}
        if(input[i] == '/' && input[i+1] == '^') { cout << "undefined error\n";return false;}
        if(input[i] == '^' && input[i+1] == '*') { cout << "undefined error\n";return false;}
        if(input[i] == '^' && input[i+1] == '/') { cout << "undefined error\n";return false;}
    }
    //Floating point
    for(size_t i = 0; i < input.size()-2; i++) {
        if(input[i] == '.' && input[i+1] == '.') { cout << "syntax error\n";return false;}
        if(input[i] == '.' && isOperator(input[i+1])) { cout << "syntax error\n";return false;}
    }
    //Parenthesis
    for(size_t i = 0; i < input.size()-3; i++) {
        if(isOperand(input[i])&&input[i+1] == '('&&input[i+2] != ')') { cout << "syntax error\n";return false;}
        if(isOperator(input[i])&&input[i+1] == ')'&&input[i+2] == '(') { cout << "syntax error\n";return false;}
    }
    return true;
}
string Infix2Postfix(const string& infix_notation) {
    if(!isAvailableInput(infix_notation)) {
        return "";
    }
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
            string openBracket = "(";
            newStack.push(openBracket);
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
            string str_symbol(1,symbol);
            newStack.push( str_symbol);
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
    if(!isAvailableInput(infix_notation)) {
        return "";
    }
    stack <string> newStack;
    string prefix_notation;
    reverse(infix_notation.begin(),infix_notation.end());
//    cout << "After reverse: " << infix_notation << endl;
    size_t length = infix_notation.size();
    for(std::size_t i = 0; i < length; i++) {
        if(isOperand(infix_notation[i])) {
            string stringNumber;
            while (isOperand(infix_notation[i]) && i < infix_notation.size()) {
                stringNumber += string(1,infix_notation[i]);
                ++i;
            }
            stringNumber += " ";
            prefix_notation += stringNumber;
        }
        if(i < infix_notation.size()) {
            char symbol = infix_notation[i];
//            if(symbol== ' ') continue;
            if(symbol == ')') {
                string openBracket = "(";
                newStack.push(openBracket);
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
                if(newStack.empty()) {
                    string str_symbol(1,symbol);
                    newStack.push( str_symbol);
                }
                else if (!newStack.empty() && preference(symbol) > preference(newStack.top()[0])) {
                    string str_symbol(1,symbol);
                    newStack.push( str_symbol);
                }
                else if (!newStack.empty() && preference(symbol) == preference(newStack.top()[0]) && symbol == '^') {
                    while (!newStack.empty() && preference(symbol) == preference(newStack.top()[0]) && symbol == '^') {
                        prefix_notation += newStack.top();
                        prefix_notation +=" ";
                        newStack.pop();
                    }
                    string str_symbol(1,symbol);
                    newStack.push( str_symbol);
                }
                else if (!newStack.empty() && preference(symbol) == preference((newStack.top()[0]))) {
                    string str_symbol(1,symbol);
                    newStack.push( str_symbol);
                }
                else if (!newStack.empty() && preference(symbol) < preference(newStack.top()[0])) {
                    while (!newStack.empty() && preference(symbol) < preference(newStack.top()[0]) ) {
                        prefix_notation += newStack.top();
                        prefix_notation +=" ";
                        newStack.pop();
                    }
                    string str_symbol(1,symbol);
                    newStack.push( str_symbol);
                }
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
        for(int i = 0; i < (int)expression.size(); i++) {
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
                while (isOperand(expression[i]) && i < (int)expression.size()) {
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
//      LOGICAL
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
int preferenceLogic(const string& symbol) {
    if(symbol == "~") return 4;
    if(symbol == "&" || symbol == "|") return 3;
    if(symbol == "->") return 2;
    if(symbol == "<->") return 1;
    else return 0;
}
bool isOperatorLogic(const string & symbol) {
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
            if(isOperatorLogic(symbol)) {
                while (!newStack.empty() && preferenceLogic(newStack.top()) >= preferenceLogic(symbol)) {
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
            if(isOperatorLogic(symbol)) {
                if(newStack.empty()) {
                    newStack.push(symbol);
                }
                else if(preferenceLogic(symbol) > preferenceLogic(newStack.top())) {
                    newStack.push(symbol);
                }
                else if (preferenceLogic(symbol) == preferenceLogic(newStack.top()) && symbol == "~") {
                    while(preferenceLogic(symbol) == preferenceLogic(newStack.top()) && symbol == "~") {
                        prefix_notation+=newStack.top();
                        newStack.pop();
                    }
                    newStack.push(symbol);
                }
                else if (preferenceLogic(symbol) == preferenceLogic(newStack.top())) {
                    newStack.push(symbol);
                }
                else if (preferenceLogic(symbol) < preferenceLogic(newStack.top())) {
                    while (!newStack.empty() && preferenceLogic(symbol) < preferenceLogic(newStack.top())) {
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
    if(!isOperatorLogic(firstSymbol)) {
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
            if(isOperatorLogic(symbol)) {
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
    else if(isOperatorLogic(firstSymbol)) {
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