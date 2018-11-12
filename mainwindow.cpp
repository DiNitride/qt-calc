#include "mainwindow.h"
#include <cmath>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QButtonGroup>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    this->memory = 0;
    this->operation = 0;
    QGridLayout *central = new QGridLayout();

    this->display = new QLineEdit();
    this->display->setReadOnly(true);
    this->display->setAlignment(Qt::AlignRight);
    this->display->setMaxLength(15);

    QButtonGroup *nums = new QButtonGroup();

    central->addWidget(this->display, 0, 1, 1, 4);

    int row = 1;
    int col = 0;
    for(int i(0); i < 10; i++){

        nums->addButton(new QPushButton(QString::number(i)), i);
        if( !i ){

            central->addWidget(nums->button(i), 4, 2, 1, 1);

        } else {

            central->addWidget(nums->button(i), row, ++col);
            if( !(i % 3) ){

                row++;
                col = 0;

            }

        }

    }

    QPushButton *add = new QPushButton("+");
    QPushButton *sub = new QPushButton("-");
    QPushButton *eq = new QPushButton("=");
    QPushButton *clear = new QPushButton("CLR");

    add->setObjectName("+");
    sub->setObjectName("-");
    eq->setObjectName("=");
    clear->setObjectName("><");

    central->addWidget(add, 1, 4, 1, 1);
    central->addWidget(sub, 2, 4, 1, 1);
    central->addWidget(eq, 3, 4, 1, 1);
    central->addWidget(clear, 4, 4, 1, 1);

    connect(nums, SIGNAL(buttonClicked(int)), this, SLOT(addNumber(int)));
    connect(this, SIGNAL(changeDisplay(QString)), this->display, SLOT(setText(QString)));
    connect(add, SIGNAL(clicked(bool)), this, SLOT(performOperation(bool)));
    connect(sub, SIGNAL(clicked(bool)), this, SLOT(performOperation(bool)));
    connect(eq, SIGNAL(clicked(bool)), this, SLOT(performOperation(bool)));
    connect(clear, SIGNAL(clicked(bool)), this, SLOT(clearDisplay(bool)));

    this->setLayout(central);


}

MainWindow::~MainWindow()
{

}

void MainWindow::addNumber(int value){

    emit this->changeDisplay(this->display->text() + QString::number(value));

}

void MainWindow::clearDisplay(bool checked){

    this->memory = 0;
    this->operation = 0;
    emit this->changeDisplay("");

}

void MainWindow::performOperation(bool checked){

    QObject *origin = sender();

    if( origin->objectName() == "+" ){

        this->memory = this->display->text().toDouble();
        this->operation = '+';
        emit this->changeDisplay("");

    } else if( origin->objectName() == "-" ){

        this->memory = this->display->text().toDouble();
        this->operation = '-';
        emit this->changeDisplay("");

    } else if( origin->objectName() == "=" ){

        if( this->memory && this->operation ){

            switch( this->operation ){

                case '+':
                    emit this->changeDisplay(QString::number(int(this->memory + this->display->text().toDouble())));
                    this->memory = 0;
                    this->operation = 0;
                    break;
                case '-':
                    emit this->changeDisplay(QString::number(int(this->memory - this->display->text().toDouble())));
                    this->memory = 0;
                    this->operation = 0;
                    break;

            }

        }

    }

}
