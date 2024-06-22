#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QThread>
#include "workerserialport.h"
#include "workerrandomnumbers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTextEdit();

private slots:
    void dataReceived(QByteArray data);
    void randomNumberFound(int number, int count);
    void on_pushButton_clicked();

private:
    QString text="";
    Ui::MainWindow *ui;
    WorkerSerialPort *workerSerialPort;
    WorkerRandomNumbers *workerRandomNumbers;
    QThread *threadSerialPort;
    QThread *threadRandomNumbers;
};

#endif // MAINWINDOW_H
