#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QVector>

class Calculation
{
public:
    enum class Token {
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
    void addToken(const Calculation::Token token);
    void deleteLast();
    void deleteAll();
    void evaluate();
private:
    QVector<Calculation::Token> *input;
    bool needReset;
    QString getTokenString(const Calculation::Token token) const;
    bool isNumberToken(const Calculation::Token token, int numBuffLength) const;
};

#endif // CALCULATION_H
