#include "calculation.h"

Calculation::Calculation()
{
    this->input = new QVector<Calculation::Token>;
}

QString Calculation::getExpressionString() const
{
    QString output = "";
    for (int i = 0; i < this->input->count(); i++) {
        switch (this->input->at(i)) {
            case Calculation::Token::B_0:
                output += "0";
                break;
            case Calculation::Token::B_1:
                output += "1";
                break;
            case Calculation::Token::B_2:
                output += "2";
                break;
            case Calculation::Token::B_3:
                output += "3";
                break;
            case Calculation::Token::B_4:
                output += "4";
                break;
            case Calculation::Token::B_5:
                output += "5";
                break;
            case Calculation::Token::B_6:
                output += "6";
                break;
            case Calculation::Token::B_7:
                output += "7";
                break;
            case Calculation::Token::B_8:
                output += "8";
                break;
            case Calculation::Token::B_9:
                output += "9";
                break;
            case Calculation::Token::B_COMMA:
                output += ",";
                break;
            case Calculation::Token::B_PERCENT:
                output += "%";
                break;
            case Calculation::Token::B_PLUS:
                output += " + ";
                break;
            case Calculation::Token::B_MINUS:
                output += " - ";
                break;
            case Calculation::Token::B_MUL:
                output += " × ";
                break;
            case Calculation::Token::B_DIV:
                output += " ÷ ";
                break;
            case Calculation::Token::B_LEFT_BRACKET:
                output += "(";
                break;
            case Calculation::Token::B_RIGHT_BRACKET:
                output += ")";
                break;
            case Calculation::Token::B_POW:
                output += "²";
                break;
            case Calculation::Token::B_SQRT:
                output += "√";
                break;
            default:
                break;
        }
    }
    return output;
}

void Calculation::addToken(const Calculation::Token token)
{
    this->input->append(token);
}

void Calculation::deleteLast()
{
    this->input->removeLast();
}

void Calculation::deleteAll()
{
    this->input->clear();
}
