#include <QTextStream>

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
        case Calculation::Char::B_PERCENT:
            return "%";
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

bool Calculation::isCharNumberRelated(const Calculation::Char c, int numBuffLength) const
{
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
            return (numBuffLength == 0);
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

void Calculation::addChar(const Calculation::Char c)
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

void Calculation::preProcessChars(QVector<QString> *preProcessed, bool *ok)
{
    QString numBuff = "";
    Calculation::Char c;
    for (int i = 0; i < this->inputSequence->count(); i++) {
        c = this->inputSequence->at(i);
        if (isCharNumberRelated(c, numBuff.length())) {
            numBuff += getCharString(c);
        }
        else {
            if (numBuff != "") {
                double num = numBuff.toDouble(ok);
                if (!*ok) {
                    return;
                }
                preProcessed->append(numBuff);
                numBuff = "";
            }
            // ignore termination character
            if (c != Calculation::Char::B_RESULT) {
                preProcessed->append(getCharString(c));
            }
        }
    }
}

void Calculation::evaluate()
{
    // don't evaluate again until reset
    if (this->needReset) {
        return;
    }

    QTextStream out(stdout); //debug

    // add termination character
    addChar(Calculation::Char::B_RESULT);

    bool ok = true;
    QVector<QString> preProcessed;

    // covert button presses to numbers and operations
    this->preProcessChars(&preProcessed, &ok);

    // debug
    for (int i = 0; i < preProcessed.count(); i++) {
        out << i << ": " << preProcessed.at(i) << endl;
    }

    this->inputSequence->clear();

    if (!ok) {
        this->inputSequence->append(Calculation::Char::ERR);
        this->needReset = true;
    }
}
