#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>
#include <QLineEdit>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addNumber(int value);
    void clearDisplay(bool checked);
    void performOperation(bool checked);

signals:
    void changeDisplay(QString text);

private:
    QLineEdit *display;
    double memory;
    char operation;
};

#endif // MAINWINDOW_H
