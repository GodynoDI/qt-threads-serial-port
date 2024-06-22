#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    workerSerialPort = new WorkerSerialPort();
    workerRandomNumbers = new WorkerRandomNumbers();

    threadSerialPort = new QThread();
    threadRandomNumbers = new QThread();

    workerSerialPort->moveToThread(threadSerialPort);
    workerRandomNumbers->moveToThread(threadRandomNumbers);

    connect(workerSerialPort, &WorkerSerialPort::dataReceived, this, &MainWindow::dataReceived);
    connect(workerRandomNumbers, &WorkerRandomNumbers::randomNumberFound, this, &MainWindow::randomNumberFound);

    connect(threadSerialPort, &QThread::started, [=]() {
        workerSerialPort->openPort("COM1", 9600);
    });
    connect(threadSerialPort, &QThread::finished, workerSerialPort, &WorkerSerialPort::deleteLater);
    connect(this, &QObject::destroyed, threadSerialPort, &QThread::quit);
    connect(this, &QObject::destroyed, threadSerialPort, &QThread::deleteLater);
    connect(threadRandomNumbers, &QThread::started, workerRandomNumbers, &WorkerRandomNumbers::start);
    connect(threadRandomNumbers, &QThread::finished, workerRandomNumbers, &WorkerRandomNumbers::deleteLater);
    connect(this, &QObject::destroyed, threadRandomNumbers, &QThread::quit);
    connect(this, &QObject::destroyed, threadRandomNumbers, &QThread::deleteLater);
    threadSerialPort->start();
    threadRandomNumbers->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::dataReceived(QByteArray data) {
    qDebug() << "Полученное значение:" << data;
    bool ok;
    int value = data.toInt(&ok);
    if (ok) {
        workerRandomNumbers->container.push_back(value);
        updateTextEdit();
    } else {
        qDebug() << "Полученно некорректное значение";
    }
}

void MainWindow::randomNumberFound(int number, int count) {
    QMessageBox::information(this, "Рандомное число", "Число " + QString::number(number) + " найдено в контейнере " + QString::number(count) + " раз");
    QByteArray data;
    data.append(QString::number(number).toUtf8());
    data.append(" ");
    data.append(QString::number(count).toUtf8());
    data.append(" ");
    workerSerialPort->sendData(data);
}

void MainWindow::on_pushButton_clicked()
{
    workerRandomNumbers->container.push_back(ui->lineEdit->text().toInt());
    updateTextEdit();
}

void MainWindow::updateTextEdit(){
    text = text + " " + QString::number(workerRandomNumbers->container.last());
    ui->textEdit->setText(text);
};

