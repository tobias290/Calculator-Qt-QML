#ifndef CALCULATION_H
#define CALCULATION_H

#include <ctype.h>
#include <map>
#include <math.h>
#include <vector>

#include <QString>
#include <QStringList>


class Calculation {

public:
    Calculation();

    enum class Operator {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
    };

    bool canCalculate();
    QString getCalculation();

    void clear();

    void addDigit(QString digit);

    bool canAddOperator();
    void addOperator(Operator op);

    QString calculate();

private:
    QStringList m_calculation;

    bool isDigit(QString digit);
    bool isOperator(QString op);

    QStringList convertToReversePolishNotation(const QStringList expression);
    QString calculateFromReversePolishNotation(const QStringList expression);
};

#endif // CALCULATION_H
