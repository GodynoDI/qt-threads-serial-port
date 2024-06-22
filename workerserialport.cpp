#include "workerserialport.h"
#include <QDebug>

WorkerSerialPort::WorkerSerialPort(QObject *parent) : QObject(parent) {
    serialPort = new QSerialPort(this);
}

WorkerSerialPort::~WorkerSerialPort() {
    serialPort->close();
}

void WorkerSerialPort::openPort(const QString &portName, quint32 baudRate) {
    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);

    if (serialPort->open(QIODevice::ReadWrite)) {
        connect(serialPort, &QSerialPort::readyRead, this, &WorkerSerialPort::readDataFromPort);
        qDebug() << "Порт открыт";
    } else {
        qDebug() << "Ошибка при открытии порта: " << serialPort->errorString();
    }
}

void WorkerSerialPort::closePort() {
    serialPort->close();
    qDebug() << "Порт закрыт";
}

void WorkerSerialPort::sendData(const QByteArray &data) {
    if (serialPort->isOpen()) {
        serialPort->write(data);
    } else {
        qDebug() << "Ошибка при отправке данных. Порт закрыт";
    }
}

void WorkerSerialPort::readDataFromPort() {
    QByteArray data = serialPort->readAll();
    emit dataReceived(data);
}

