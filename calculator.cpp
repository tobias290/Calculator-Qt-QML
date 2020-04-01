#include "calculator.h"

Calculator::Calculator(QObject *parent) : QObject(parent) {
}


QString Calculator::calculationDisplay() {
    return m_calculationDisplay;
}


void Calculator::setCalculationDisplay(const QString value) {
    m_calculationDisplay = value;
    emit calculationDisplayChanged();
}


QString Calculator::display() {
    return m_display;
}


void Calculator::setDisplay(const QString value) {
    m_display = value;
    emit displayChanged();
}


void Calculator::clear(bool clearAll) {
    if (clearAll) {
        m_calculation.clear();
        this->setCalculationDisplay(m_calculation.getCalculation());
        this->setDisplay("0");
    } else {
        this->setDisplay("0");
    }
}


void Calculator::back() {
    // The back button can only be used if there is something in the display
    if (m_display.length() == 0)
        return;

    if (m_display.length() >= 2)
        m_display.remove(m_display.length() - 1, 1);
    else
        m_display = "0";

    emit displayChanged();
}


void Calculator::numberButtonClick(const QString value) {
    if (m_display == "0")
        this->setDisplay(value);
    else
        this->setDisplay(m_display + value);
}

void Calculator::add() {
    this->addOperator(Calculation::Operator::ADDITION);
}


void Calculator::subtract() {
    this->addOperator(Calculation::Operator::SUBTRACTION);
}


void Calculator::multiply() {
    this->addOperator(Calculation::Operator::MULTIPLICATION);
}


void Calculator::divide() {
    this->addOperator(Calculation::Operator::DIVISION);
}


void Calculator::addOperator(Calculation::Operator op) {
    // If display is not empty (i.e. "0") then add the display's content to the calculation
   if (m_display != "0") {
       m_calculation.addDigit(m_display);
       this->setCalculationDisplay(m_calculation.getCalculation());
       m_display = "0"; // Reset display but don't update the UI
   }

    // Only if the previous part of the calculation is a number can we add an operator
    if (m_calculation.canAddOperator()) {
        m_calculation.addOperator(op);
        this->setCalculationDisplay(m_calculation.getCalculation());
    }
}

void Calculator::equals() {
    if (!m_calculation.canCalculate())
        return;

    // Add whats in the display to the calculation
    m_calculation.addDigit(m_display);
    this->setCalculationDisplay(m_calculation.getCalculation());
    this->setDisplay(m_calculation.calculate());

    m_calculation.clear();

    // Reset calculation display but don't update the UI
    m_calculationDisplay = "";
}


void Calculator::addFloatingPoint() {
    if (m_display.back() == ".")
        return;

    this->setDisplay(m_display + ".");
}


void Calculator::switchSign() {
    if (m_display == "0")
        return;

    if (m_display.front() != "-")
        m_display.push_front("-");
     else
        m_display.remove(0, 1);

    emit displayChanged();
}
