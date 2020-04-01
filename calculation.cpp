#include "calculation.h"

Calculation::Calculation() {

}


QString Calculation::getCalculation(){
    return m_calculation.join(" ");
}


void Calculation::clear() {
    m_calculation.clear();
}


void Calculation::addDigit(QString digit) { 
   m_calculation.append(digit);
}


bool Calculation::canAddOperator() {
    return !m_calculation.isEmpty() && !this->isOperator(m_calculation.last());
}


void Calculation::addOperator(Operator op) {
    switch(op) {
        case Operator::ADDITION:
            m_calculation.append("+");
            break;
        case Operator::SUBTRACTION:
            m_calculation.append("-");
            break;
        case Operator::MULTIPLICATION:
            m_calculation.append("×");
            break;
        case Operator::DIVISION:
            m_calculation.append("÷");
            break;
    }
}


bool Calculation::canCalculate() {
    return !m_calculation.isEmpty();
}


QString Calculation::calculate() {
    QStringList rpn = this->convertToReversePolishNotation(m_calculation);

    return this->calculateFromReversePolishNotation(rpn);
}

bool Calculation::isDigit(QString digit) {
    return (
        digit.contains("0") || digit.contains("1") || digit.contains("2") || digit.contains("3") || digit.contains("4") ||
        digit.contains("5") || digit.contains("6") || digit.contains("7") || digit.contains("8") || digit.contains("9")
    );
}

bool Calculation::isOperator(QString op) {
    return op == "+" || op == "-" || op == "×" || op == "÷";
}


QStringList Calculation::convertToReversePolishNotation(const QStringList expression) {
    // Associativity --> Left: 0, Right: 1
    std::map<QString, std::map<QString, int>> op_info {
        {"^", {{"precedence", 4}, {"associativity", 1}}},
        {"×", {{"precedence", 3}, {"associativity", 0}}},
        {"÷", {{"precedence", 3}, {"associativity", 0}}},
        {"+", {{"precedence", 2}, {"associativity", 0}}},
        {"-", {{"precedence", 2}, {"associativity", 0}}}
    };

    auto i = 0;
    auto output_stack = QStringList();
    auto operator_stack = QStringList();

    // Loop over each part of the expression
    while (i < expression.length()) {
        auto token = expression[i];

        if (this->isOperator(token)) { // If the token is an operator
            // Check whether the condition is correct to add the operator to the outut stack
            while (
                  (operator_stack.length() != 0 && operator_stack.last() != "(") &&
                  (
                      operator_stack.last() != "(" &&
                      (
                          op_info[operator_stack.last()]["precedence"] > op_info[token]["precedence"] ||
                          (
                              op_info[operator_stack.last()]["precedence"] == op_info[token]["precedence"] &&
                              op_info[token]["associativity"] == 0
                          )
                      )
                 )
            ) {
                output_stack.append(operator_stack);
                operator_stack.clear();
            }

            operator_stack.append(token);
        } else if (token == "(") {
            operator_stack.append(token);
        } else if (token == ")") {
            // Keep adding operators to the output stack until a left parentheses
            while (operator_stack.last() != "(") {
                output_stack.append(operator_stack.last());
                operator_stack.pop_back();
            }
        } else { // Else the token is a digit
            output_stack.append(token);
        }

        i++;
    }

    while (operator_stack.length() > 0) {
        output_stack.append(operator_stack.last());
        operator_stack.pop_back();
    }


    return output_stack;
}


QString Calculation::calculateFromReversePolishNotation(const QStringList expression) {
    auto calculation = QStringList();

    for (auto token : expression) {
        if (this->isOperator(token)) { // If the token is an operator
            auto op_2 = calculation.last();
            calculation.pop_back();
            auto op_1 = calculation.last();
            calculation.pop_back();

            // Work out the correct calculation then perform it
            if (token == "+") {
                auto value = op_1.toFloat() + op_2.toFloat();
                calculation.append(QString::number(value));
            } else if (token == "-") {
                auto value = op_1.toFloat() - op_2.toFloat();
                calculation.append(QString::number(value));
            } else if (token == "×") {
                auto value = op_1.toFloat() * op_2.toFloat();
                calculation.append(QString::number(value));
            } else if (token == "÷") {
                auto value = op_1.toFloat() / op_2.toFloat();
                calculation.append(QString::number(value));
            }
        } else { // Else token is a digit
            calculation.append(token);
        }
    }

    return calculation.last();
}

