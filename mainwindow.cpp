#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect digit buttons to digitPressed slot
    connect(ui->NumberZero, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberOne, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberTwo, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberThree, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberFour, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberFive, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberSix, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberSeven, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberEight, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->NumberNine, SIGNAL(released()), this, SLOT(digitPressed()));

    // Connect operation buttons to operationPressed slot
    connect(ui->Divide, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Plus, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Minus, SIGNAL(released()), this, SLOT(operationPressed()));

    // Connect equals button to equalsPressed slot
    connect(ui->Equals, SIGNAL(released()), this, SLOT(equalsPressed()));

    // Connect clear buttons to clearPressed slot
    connect(ui->Backspace, SIGNAL(released()), this, SLOT(clearPressed()));
    connect(ui->Reset, SIGNAL(released()), this, SLOT(clearPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitPressed()
{

    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();

    operationInProcess = true;

    if ((displayValue == "0") || (displayValue == "0.0") || (answerAquired == true))
    {
        ui->Display->setText(buttonValue);
        answerAquired = false;
    }
    else
    {
        QString newValue = displayValue + buttonValue;
        ui->Display->setText(newValue);
    }



}

void MainWindow::operationPressed()
{

    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();
    pendingOperator = buttonValue;

    if (operationInProcess == true)
    {
        leftOperand = ui->Display->text().toDouble();
        ui->Display->clear();

        operationInProcess = false;
    }


}

void MainWindow::equalsPressed()
{
    rightOperand = ui->Display->text().toDouble();
    double result = 0.0;
    errorFlag = false;
    answerAquired = true;

    if (pendingOperator == "+")
    {
        result = leftOperand + rightOperand;
    }

    else if (pendingOperator == "×")
    {
        result = leftOperand * rightOperand;
    }

    else if ((pendingOperator == "÷") && (rightOperand != 0))
    {
        result = leftOperand / rightOperand;
    }

    else if (pendingOperator == "−")
    {
        result = leftOperand - rightOperand;
    }

    else
    {
        ui->Display->setText("Math Error");
        errorFlag = true;

    }

    if (errorFlag == false)
    {
        ui->Display->setText((QString::number(result)));
    }

}

void MainWindow::clearPressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString buttonValue = button->text();

    if (buttonValue == "AC")
    {
        ui->Display->clear();
        leftOperand = 0.0;
        pendingOperator = "";
        rightOperand = 0.0;

    }

    else if ((buttonValue == "<-") && (answerAquired == false))
    {
        QString DisplayValue = ui->Display->text();
        QString newValue = DisplayValue.removeLast();
        ui->Display->setText(newValue);

    }
}
