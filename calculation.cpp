#include <cmath>

#include <QtMath>
#include <QStack>

#include "calculation.h"

Calculation::Calculation()
{
    this->inputSequence = new QVector<Calculation::Char>;
    this->needReset = false;
}

QString Calculation::getCharString(const Calculation::Char c) const
{
    switch (c) {
        case Calculation::Char::B_0:
            return "0";
        case Calculation::Char::B_1:
            return "1";
        case Calculation::Char::B_2:
            return "2";
        case Calculation::Char::B_3:
            return "3";
        case Calculation::Char::B_4:
            return "4";
        case Calculation::Char::B_5:
            return "5";
        case Calculation::Char::B_6:
            return "6";
        case Calculation::Char::B_7:
            return "7";
        case Calculation::Char::B_8:
            return "8";
        case Calculation::Char::B_9:
            return "9";
        case Calculation::Char::B_COMMA:
            return ".";
        case Calculation::Char::B_MOD:
            return " mod ";
        case Calculation::Char::B_PLUS:
            return "+";
        case Calculation::Char::B_MINUS:
            return "-";
        case Calculation::Char::B_MUL:
            return "×";
        case Calculation::Char::B_DIV:
            return "÷";
        case Calculation::Char::B_LEFT_BRACKET:
            return "(";
        case Calculation::Char::B_RIGHT_BRACKET:
            return ")";
        case Calculation::Char::B_POW:
            return "²";
        case Calculation::Char::B_SQRT:
            return "√";
        case Calculation::Char::ERR:
            return "ERROR";
        default:
            return "";
    }
}

bool Calculation::isCharNumberRelated(const Calculation::Char c, QVector<Token> *tokens, int numBuffLength) const
{
    bool canStartWithSign = true;
    if (!tokens->isEmpty()) {
        Token last = tokens->last();
        if (last.type == TokenType::OPERATOR && (last.opArguments == 1 || last.opType == OperatorType::RIGHT_BRACKET)) {
            canStartWithSign = false;
        }
    }
    switch (c) {
        case Calculation::Char::B_0:
        case Calculation::Char::B_1:
        case Calculation::Char::B_2:
        case Calculation::Char::B_3:
        case Calculation::Char::B_4:
        case Calculation::Char::B_5:
        case Calculation::Char::B_6:
        case Calculation::Char::B_7:
        case Calculation::Char::B_8:
        case Calculation::Char::B_9:
        case Calculation::Char::B_COMMA:
            return true;
        case Calculation::Char::B_PLUS:
        case Calculation::Char::B_MINUS:
            return (numBuffLength == 0 and canStartWithSign);
        default:
            return false;
    }
}

QString Calculation::getExpressionString() const
{
    QString output = "";
    for (int i = 0; i < this->inputSequence->count(); i++) {
        output += this->getCharString(this->inputSequence->at(i));
    }
    return output;
}

void Calculation::addInputChar(const Calculation::Char c)
{
    if (!this->needReset) {
        this->inputSequence->append(c);
    }
}

void Calculation::deleteLast()
{
    if (this->inputSequence->count() > 0) {
        this->inputSequence->removeLast();
    }
    if (this->inputSequence->count() == 0) {
        this->needReset = false;
    }
}

void Calculation::deleteAll()
{
    this->inputSequence->clear();
    this->needReset = false;
}

void Calculation::addInputNumber(double num)
{
    QString numStr = QString::number(num, 'f', 9).remove(QRegExp("\\.?0+$"));

    QChar c;
    for (int i = 0; i < numStr.size(); i++) {
        c = numStr.at(i);
        if (c == QChar('-')) {
            this->inputSequence->append(Calculation::Char::B_MINUS);
        }
        else if (c == QChar('0')) {
            this->inputSequence->append(Calculation::Char::B_0);
        }
        else if (c == QChar('1')) {
            this->inputSequence->append(Calculation::Char::B_1);
        }
        else if (c == QChar('2')) {
            this->inputSequence->append(Calculation::Char::B_2);
        }
        else if (c == QChar('3')) {
            this->inputSequence->append(Calculation::Char::B_3);
        }
        else if (c == QChar('4')) {
            this->inputSequence->append(Calculation::Char::B_4);
        }
        else if (c == QChar('5')) {
            this->inputSequence->append(Calculation::Char::B_5);
        }
        else if (c == QChar('6')) {
            this->inputSequence->append(Calculation::Char::B_6);
        }
        else if (c == QChar('7')) {
            this->inputSequence->append(Calculation::Char::B_7);
        }
        else if (c == QChar('8')) {
            this->inputSequence->append(Calculation::Char::B_8);
        }
        else if (c == QChar('9')) {
            this->inputSequence->append(Calculation::Char::B_9);
        }
        else if (c == QChar('.')) {
            this->inputSequence->append(Calculation::Char::B_COMMA);
        }
    }
}

void Calculation::processChars(QVector<Token> *tokens, bool *ok)
{
    QString numBuff = "";
    Calculation::Char c;
    for (int i = 0; i < this->inputSequence->count(); i++) {
        c = this->inputSequence->at(i);
        if (isCharNumberRelated(c, tokens, numBuff.length())) {
            numBuff += getCharString(c);
        }
        else {
            // flush number to token
            if (numBuff != "") {
                double num = numBuff.toDouble(ok);
                if (!*ok) {
                    return;
                }
                Token t;
                t.type = TokenType::NUMBER;
                t.numberValue = num;
                tokens->append(t);
                numBuff = "";
            }
            // ignoring termination character
            if (c == Calculation::Char::B_PLUS) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 2;
                t.opType = OperatorType::PLUS;
                t.opPrecedence = 1;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_MINUS) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 2;
                t.opType = OperatorType::MINUS;
                t.opPrecedence = 1;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_MUL) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 2;
                t.opType = OperatorType::MUL;
                t.opPrecedence = 2;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_DIV) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 2;
                t.opType = OperatorType::DIV;
                t.opPrecedence = 2;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_MOD) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 2;
                t.opType = OperatorType::MOD;
                t.opPrecedence = 2;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_POW) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 1;
                t.opType = OperatorType::POW;
                t.opPrecedence = 3;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_SQRT) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 1;
                t.opType = OperatorType::SQRT;
                t.opPrecedence = 3;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_LEFT_BRACKET) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 0;
                t.opType = OperatorType::LEFT_BRACKET;
                t.opPrecedence = 0;
                tokens->append(t);
            }
            else if (c == Calculation::Char::B_RIGHT_BRACKET) {
                Token t;
                t.type = TokenType::OPERATOR;
                t.opArguments = 0;
                t.opType = OperatorType::RIGHT_BRACKET;
                t.opPrecedence = 0;
                tokens->append(t);
            }
        }
    }
}

void Calculation::tokensToPostfix(QVector<Token> *tokens, bool *ok)
{
    QVector<Token> newTokens;
    QStack<Token> tmpOperatorStack;
    Token t;
    while(!tokens->isEmpty()) {
        t = tokens->at(0);
        tokens->removeAt(0);
        if (t.type == TokenType::NUMBER) {
            newTokens.append(t);
        }
        else if (t.type == TokenType::OPERATOR) {
            if (t.opType == OperatorType::LEFT_BRACKET) {
                tmpOperatorStack.push(t);
            }
            else if (t.opType == OperatorType::RIGHT_BRACKET && !tmpOperatorStack.isEmpty()) {
                Token popped = tmpOperatorStack.pop();
                while ((!tmpOperatorStack.isEmpty()) && (popped.opType != OperatorType::LEFT_BRACKET))
                {
                    newTokens.append(popped);
                    popped = tmpOperatorStack.pop();
                }
            }
            else {
                while ((!tmpOperatorStack.isEmpty()) && (t.opPrecedence <= tmpOperatorStack.last().opPrecedence))
                {
                       newTokens.append(tmpOperatorStack.pop());
                }
                tmpOperatorStack.push(t);
            }
        }
    }
    while(!tmpOperatorStack.isEmpty()) {
        newTokens.append(tmpOperatorStack.pop());
    }

    // save back
    for (int i = 0; i < newTokens.count(); i++) {
        t = newTokens.at(i);
        tokens->append(t);
    }
    // catch input like ()
    if (tokens->isEmpty()) {
        *ok = false;
    }
}

Token* Calculation::buildTreeStructure(QVector<Token> *tokens, Token *token, bool *ok)
{
    if (token->type == TokenType::OPERATOR) {
        Token child;
        for (int i = 0; i < token->opArguments; i++) {
            if (tokens->isEmpty()) {
                *ok = false;
                return token;
            }
            child = tokens->last();
            tokens->removeLast();
            // recursion
            if (child.type == TokenType::OPERATOR) {
                this->buildTreeStructure(tokens, &child, ok);
            }
            token->opChildren.append(child);
        }
    }
    return token;
}

double Calculation::evaluateToken(Token token, bool *ok)
{
    if (token.type == TokenType::NUMBER) {
        return token.numberValue;
    }
    else if (token.type == TokenType::OPERATOR) {
        QVector<double> results;
        for (int i = 0; i < token.opChildren.count(); i++) {
            results.append(this->evaluateToken(token.opChildren.at(i), ok));
        }
        if (token.opType == OperatorType::PLUS) {
            return results.at(1) + results.at(0);
        }
        else if (token.opType == OperatorType::MINUS) {
            return results.at(1) - results.at(0);
        }
        else if (token.opType == OperatorType::MUL) {
            return results.at(1) * results.at(0);
        }
        else if (token.opType == OperatorType::DIV) {
            if (results.at(0) == 0.0) { // div by zero
                *ok = false;
            }
            return results.at(1) / results.at(0);
        }
        else if (token.opType == OperatorType::POW) {
            return results.at(0) * results.at(0);
        }
        else if (token.opType == OperatorType::SQRT) {
            return qSqrt(results.at(0));
        }
        else if (token.opType == OperatorType::MOD) {
            if (results.at(0) == 0.0) { // div by zero
                *ok = false;
            }
            return fmod(results.at(1), results.at(0));
        }
    }
    *ok = false;
    return 0;
}

void Calculation::evaluate()
{
    // don't evaluate again until reset
    if ((this->needReset) || (this->inputSequence->isEmpty())) {
        return;
    }

    // add termination character
    addInputChar(Calculation::Char::B_RESULT);

    bool ok = true;
    QVector<Token> tokens;

    // convert button chars to numbers and operations
    this->processChars(&tokens, &ok);
    if (!ok) {
        this->inputSequence->clear();
        this->inputSequence->append(Calculation::Char::ERR);
        this->needReset = true;
        return;
    }

    // shunting yard algorithm
    this->tokensToPostfix(&tokens, &ok);
    if (!ok) {
        this->inputSequence->clear();
        this->inputSequence->append(Calculation::Char::ERR);
        this->needReset = true;
        return;
    }

    // create tree for evaluation
    Token lastToken = tokens.last();
    tokens.removeLast();
    Token *rootToken = this->buildTreeStructure(&tokens, &lastToken, &ok);
    if (!ok) {
        this->inputSequence->clear();
        this->inputSequence->append(Calculation::Char::ERR);
        this->needReset = true;
        return;
    }

    // go through tree and get result
    double result = this->evaluateToken(*rootToken, &ok);
    if (!ok) {
        this->inputSequence->clear();
        this->inputSequence->append(Calculation::Char::ERR);
        this->needReset = true;
        return;
    }

    this->inputSequence->clear();
    this->addInputNumber(result);
}
