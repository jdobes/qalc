#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calculation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_zeroButton_clicked();

    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_commaButton_clicked();

    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_mulButton_clicked();

    void on_divButon_clicked();

    void on_delButton_clicked();

    void on_clearButton_clicked();

    void on_leftBracketButton_clicked();

    void on_rightBracketButton_clicked();

    void on_powButton_clicked();

    void on_sqrtButton_clicked();

    void on_resultButton_clicked();

    void on_modButton_clicked();

private:
    void buttonClicked(const Calculation::Char c);
    Ui::MainWindow *ui;
    Calculation calculation;
};
#endif // MAINWINDOW_H
