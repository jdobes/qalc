#include <QTextStream>

#include "calculation.h"

Calculation::Calculation()
{
    this->input = new QVector<Calculation::Token>;
    this->needReset = false;
}

QString Calculation::getTokenString(const Calculation::Token token) const
{
    switch (token) {
        case Calculation::Token::B_0:
            return "0";
        case Calculation::Token::B_1:
            return "1";
        case Calculation::Token::B_2:
            return "2";
        case Calculation::Token::B_3:
            return "3";
        case Calculation::Token::B_4:
            return "4";
        case Calculation::Token::B_5:
            return "5";
        case Calculation::Token::B_6:
            return "6";
        case Calculation::Token::B_7:
            return "7";
        case Calculation::Token::B_8:
            return "8";
        case Calculation::Token::B_9:
            return "9";
        case Calculation::Token::B_COMMA:
            return ".";
        case Calculation::Token::B_PERCENT:
            return "%";
        case Calculation::Token::B_PLUS:
            return " + ";
        case Calculation::Token::B_MINUS:
            return " - ";
        case Calculation::Token::B_MUL:
            return " × ";
        case Calculation::Token::B_DIV:
            return " ÷ ";
        case Calculation::Token::B_LEFT_BRACKET:
            return "(";
        case Calculation::Token::B_RIGHT_BRACKET:
            return ")";
        case Calculation::Token::B_POW:
            return "²";
        case Calculation::Token::B_SQRT:
            return "√";
        case Calculation::Token::ERR:
            return "ERROR";
        default:
            return "";
    }
}

bool Calculation::isNumberToken(const Calculation::Token token, int numBuffLength) const
{
    switch (token) {
        case Calculation::Token::B_0:
        case Calculation::Token::B_1:
        case Calculation::Token::B_2:
        case Calculation::Token::B_3:
        case Calculation::Token::B_4:
        case Calculation::Token::B_5:
        case Calculation::Token::B_6:
        case Calculation::Token::B_7:
        case Calculation::Token::B_8:
        case Calculation::Token::B_9:
        case Calculation::Token::B_COMMA:
            return true;
        case Calculation::Token::B_PLUS:
        case Calculation::Token::B_MINUS:
            return (numBuffLength == 0);
        default:
            return false;
    }
}

QString Calculation::getExpressionString() const
{
    QString output = "";
    for (int i = 0; i < this->input->count(); i++) {
        output += this->getTokenString(this->input->at(i));
    }
    return output;
}

void Calculation::addToken(const Calculation::Token token)
{
    if (!this->needReset) {
        this->input->append(token);
    }
}

void Calculation::deleteLast()
{
    if (this->input->count() > 0) {
        this->input->removeLast();
    }
    if (this->input->count() == 0) {
        this->needReset = false;
    }
}

void Calculation::deleteAll()
{
    this->input->clear();
    this->needReset = false;
}

void Calculation::evaluate()
{
    // don't evaluate again until reset
    if (this->needReset) {
        return;
    }

    QTextStream out(stdout); //debug

    // add termination token
    addToken(Calculation::Token::B_RESULT);

    bool ok = true;
    QVector<QString> preProcessed;
    QString numBuff = "";
    Calculation::Token token;
    for (int i = 0; i < this->input->count(); i++) {
        token = this->input->at(i);
        if (isNumberToken(token, numBuff.length())) {
            numBuff += getTokenString(token);
        }
        else if ((token == Calculation::Token::B_RESULT) && (numBuff != "")) {
            double num = numBuff.toDouble(&ok);
            if (!ok) {
                break;
            }
            preProcessed.append(numBuff);
            numBuff = "";
        }
        else {
            if (numBuff != "") {
                double num = numBuff.toDouble(&ok);
                if (!ok) {
                    break;
                }
                preProcessed.append(numBuff);
                numBuff = "";
            }
            preProcessed.append(getTokenString(token));
        }
    }

    // debug
    for (int i = 0; i < preProcessed.count(); i++) {
        out << i << ": " << preProcessed.at(i) << endl;
    }

    this->input->clear();

    if (!ok) {
        this->input->append(Calculation::Token::ERR);
        this->needReset = true;
    }
}
