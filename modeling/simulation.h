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

signals:
    void sendStatus(QString msg);

private:
    QVector<int> *read_sim_data = new QVector<int>;
    QVector<int> *write_sim_data = new QVector<int>;
    int clients;
    int runtime;
    int rrand();
    int wrand();
};

#endif // SIMULATION_H
