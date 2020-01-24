#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QVector>

enum class TokenType {
    NUMBER,
    OPERATOR,
    LEFT_BRACKET,
    RIGHT_BRACKET,
};

enum class OperatorType {
    PLUS,
    MINUS,
    MUL,
    DIV,
    POW,
    SQRT,
    MOD
};

enum class OperatorAssociativity {
    LEFT,
    RIGHT
};

struct Token {
    TokenType type;
    double numberValue;
    OperatorType opType;
    int opArguments;
    OperatorAssociativity opAssoc;
    int opPrecedence;
    QVector<Token> opChildren;
};

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
        B_PLUS,
        B_MINUS,
        B_MUL,
        B_DIV,
        B_MOD,
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
    bool isCharNumberRelated(const Calculation::Char c, QVector<Token> *tokens, int numBuffLength) const;
    void processChars(QVector<Token> *tokens, bool *ok);
    void tokensToPostfix(QVector<Token> *tokens);
    Token* buildTreeStructure(QVector<Token> *tokens, Token *token, bool *ok);
    void addInputNumber(double num);
    double evaluateToken(Token token);
};

#endif // CALCULATION_H
