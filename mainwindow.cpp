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
            QStringList strList = line.split(",");
            //qDebug() << strList[0] <<strList[1] <<strList[2];
            QDate date;
            date = QDate::fromString(strList[0],"yyyy/MM/dd");
            //qDebug() << date;
            QTime time;
            time = QTime::fromString(strList[1],"HH:mm");
            QDate nowdate;
            nowdate=nowdate.currentDate();
            QTime nowtime;
            nowtime=nowtime.currentTime();
            ui->textBrowser_2->append(line);
            if(date==nowdate&&time.addSecs(-30*60)<nowtime&&time>nowtime)
            {
                //ui->textBrowser_2->clear();
                ui->textBrowser_2->setTextColor(2000);
                ui->textBrowser_2->append("It's time to "+  strList[2]);
                qDebug() << "It's time to " << strList[2];
                ui->textBrowser_2->setTextColor(1);


        }
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
    ui->textBrowser_2->insertPlainText(","+ui->timeEdit->text());
    ui->textBrowser_2->insertPlainText(","+ui->textEdit->toPlainText());
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
//QString str = "2013-10-15,14:00,sleep";

//    QStringList strList = str.split(",");

//    qDebug() << strList[0] <<strList[1]<<strList[2];

//    QDate date;
//    date = QDate::fromString(strList[0],"yyyy/MM/dd");
//    qDebug() << date;

//    QTime time;
//    time = QTime::fromString(strList[1],"HH:mm");
//    qDebug() << time;
//







void MainWindow::on_textEdit_cursorPositionChanged()
{
    ui->pushButton_OK->setEnabled(1);
}
