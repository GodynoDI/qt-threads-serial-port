#ifndef WORKERSERIALPORT_H
#define WORKERSERIALPORT_H
#include <QObject>
#include <QSerialPort>

class WorkerSerialPort : public QObject {
    Q_OBJECT

public:
    explicit WorkerSerialPort(QObject *parent = nullptr);
    ~WorkerSerialPort();

signals:
    void dataReceived(QByteArray data);

public slots:
    void openPort(const QString &portName, quint32 baudRate);
    void closePort();
    void sendData(const QByteArray &data);

private slots:
    void readDataFromPort();

private:
    QSerialPort *serialPort;
};
#endif // WORKERSERIALPORT_H
