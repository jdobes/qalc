#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "calculation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked(const Calculation::Char c)
{
    switch (c) {
        case Calculation::Char::B_DEL:
            this->calculation.deleteLast();
            break;
        case Calculation::Char::B_CLEAR:
            this->calculation.deleteAll();
            break;
        case Calculation::Char::B_RESULT:
            this->calculation.evaluate();
            break;
        default:
            this->calculation.addChar(c);
            break;
    }
    this->ui->lineEdit->setText(this->calculation.getExpressionString());
}

void MainWindow::on_zeroButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_0);
}

void MainWindow::on_oneButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_1);
}

void MainWindow::on_twoButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_2);
}

void MainWindow::on_threeButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_3);
}

void MainWindow::on_fourButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_4);
}

void MainWindow::on_fiveButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_5);
}

void MainWindow::on_sixButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_6);
}

void MainWindow::on_sevenButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_7);
}

void MainWindow::on_eightButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_8);
}

void MainWindow::on_nineButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_9);
}

void MainWindow::on_commaButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_COMMA);
}

void MainWindow::on_percentButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_PERCENT);
}

void MainWindow::on_plusButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_PLUS);
}

void MainWindow::on_minusButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_MINUS);
}

void MainWindow::on_mulButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_MUL);
}

void MainWindow::on_divButon_clicked()
{
    this->buttonClicked(Calculation::Char::B_DIV);
}

void MainWindow::on_delButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_DEL);
}

void MainWindow::on_clearButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_CLEAR);
}

void MainWindow::on_leftBracketButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_LEFT_BRACKET);
}

void MainWindow::on_rightBracketButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_RIGHT_BRACKET);
}

void MainWindow::on_powButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_POW);
}

void MainWindow::on_sqrtButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_SQRT);
}

void MainWindow::on_resultButton_clicked()
{
    this->buttonClicked(Calculation::Char::B_RESULT);
}
