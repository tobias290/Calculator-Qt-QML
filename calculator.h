#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>

#include "calculation.h"

class Calculator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString calculation READ calculationDisplay WRITE setCalculationDisplay NOTIFY calculationDisplayChanged)
    Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY displayChanged)

public:
    explicit Calculator(QObject *parent = nullptr);

    QString calculationDisplay();
    void setCalculationDisplay(const QString value);

    QString display();
    void setDisplay(const QString value);

    Q_INVOKABLE void clear(bool clearAll = false);
    Q_INVOKABLE void back();
    Q_INVOKABLE void numberButtonClick(const QString value);
    Q_INVOKABLE void add();
    Q_INVOKABLE void subtract();
    Q_INVOKABLE void multiply();
    Q_INVOKABLE void divide();
    Q_INVOKABLE void equals();
    Q_INVOKABLE void addFloatingPoint();
    Q_INVOKABLE void switchSign();

signals:
    void calculationDisplayChanged();
    void displayChanged();

private:
    void addOperator(Calculation::Operator op);

    Calculation m_calculation;
    QString m_calculationDisplay;
    QString m_display = "0";

};

#endif // CALCULATOR_H
