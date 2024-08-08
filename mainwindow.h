#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitPressed();
    void operationPressed();
    void unaryOperationPressed();
    void equalsPressed();
    void clearPressed();

private:
    Ui::MainWindow *ui;

    // Member variables to store operands, operator and flags
    double leftOperand;
    double rightOperand;

    QString pendingOperator;

    bool errorFlag;
    bool operationInProcess;
    bool answerAquired;
};
#endif // MAINWINDOW_H
