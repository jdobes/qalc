#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QVector>

class Calculation
{
public:
    enum class Char {
        B_0,
        B_1,
        B_2,
        B_3,
        B_4,
        B_5,
        B_6,
        B_7,
        B_8,
        B_9,
        B_COMMA,
        B_PERCENT,
        B_PLUS,
        B_MINUS,
        B_MUL,
        B_DIV,
        B_DEL,
        B_CLEAR,
        B_LEFT_BRACKET,
        B_RIGHT_BRACKET,
        B_POW,
        B_SQRT,
        B_RESULT,
        ERR
    };
    Calculation();
    QString getExpressionString() const;
    void addInputChar(const Calculation::Char c);
    void deleteLast();
    void deleteAll();
    void evaluate();
private:
    QVector<Calculation::Char> *inputSequence;
    bool needReset;
    QString getCharString(const Calculation::Char c) const;
    bool isCharNumberRelated(const Calculation::Char c, int numBuffLength) const;
    void preProcessChars(QVector<QString> *preProcessed, bool *ok);
    void addInputNumber(double num);
};

#endif // CALCULATION_H
