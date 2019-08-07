#ifndef SIMULATION_H
#define SIMULATION_H

#include "distribution.h"
#include <QDateTime>
#include <stdlib.h>
#include <QObject>

class simulation : public distribution
{
    Q_OBJECT
public:
    simulation(int, int);
    ~simulation();
    void simCalc(QVector<int>*,QVector<int>*);
    //void clearPreviousData();

signals:
    void sendStatus(QString msg);

private:
    int clients;
    int runtime;
    int rrand();
    int wrand();
};

#endif // SIMULATION_H
