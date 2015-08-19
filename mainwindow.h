#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString showdate;
    ~MainWindow();

private slots:
    void on_pushButton_load_clicked();


    void on_calendarWidget_clicked(const QDate &date);


    void on_pushButton_OK_clicked();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
