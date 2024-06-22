#ifndef WORKERRANDOMNUMBERS_H
#define WORKERRANDOMNUMBERS_H

#include <QObject>

class WorkerRandomNumbers : public QObject {
    Q_OBJECT

public:
    QList<int> container;
    explicit WorkerRandomNumbers(QObject *parent = nullptr);
    ~WorkerRandomNumbers();

signals:
    void randomNumberFound(int number, int count);

public slots:
    void start();
    void stop();

private slots:
    void generateRandomNumber();

private:
    bool isRunning;
};

#endif // WORKERRANDOMNUMBERS_H
