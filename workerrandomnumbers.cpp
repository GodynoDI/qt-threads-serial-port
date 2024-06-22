#include "workerrandomnumbers.h"

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <cstdlib>
#include <ctime>

WorkerRandomNumbers::WorkerRandomNumbers(QObject *parent) : QObject(parent) {
    isRunning = false;
}

WorkerRandomNumbers::~WorkerRandomNumbers() {
    stop();
}

void WorkerRandomNumbers::start() {
    isRunning = true;
    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, &QTimer::timeout, this, &WorkerRandomNumbers::generateRandomNumber);
    timer->start();
}

void WorkerRandomNumbers::stop() {
    isRunning = false;
}

void WorkerRandomNumbers::generateRandomNumber() {
    if (isRunning) {
        std::srand(std::time(0));
        int randomNumber = std::rand() % 11;
        qDebug() << "Сгенерированное число:" << randomNumber;
        int count = 0;
        for (int num : container) {
            if (num == randomNumber) {
                count++;
            }
        }
        if (count > 0) {
            qDebug() << "Число найдено в контейнере: " << count << " раз";
            emit randomNumberFound(randomNumber, count);
        } else {
            qDebug() << "Число не найдено в контейнере";
        }
    }
}
