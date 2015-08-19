#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDate>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_load_clicked()
{
    QFile file("todo.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QString line;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            line=in.readLine();
            ui->textBrowser_2->append(line);
        }
    }
    else{
    qDebug() << "Fail";
  }
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    showdate=date.toString("yyyy/MM/dd");
    ui->calendarWidget->setEnabled(0);
    ui->timeEdit->setEnabled(1);

}


void MainWindow::on_pushButton_OK_clicked()
{
    ui->textBrowser_2->append(showdate);
    ui->textBrowser_2->insertPlainText("   "+ui->timeEdit->text());
    ui->textBrowser_2->insertPlainText("   "+ui->textEdit->toPlainText());
    ui->textEdit->clear();

    ui->calendarWidget->setEnabled(1);
    ui->timeEdit->setEnabled(0);
    ui->textEdit->setEnabled(0);
    ui->pushButton_save->setEnabled(1);
}


void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
    ui->textEdit->setEnabled(1);
}

void MainWindow::on_pushButton_save_clicked()
{
    QFile file("todo.txt");
    if(file.open(QFile::WriteOnly | QFile::Truncate |QFile::Text))
    {
        QTextStream out(&file);
        out << ui->textBrowser_2->toPlainText();
    }
}
