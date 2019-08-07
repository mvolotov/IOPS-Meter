#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "density.h"

class distribution : public density
{
public:
    distribution();
    ~distribution();
    void distCalc(QVector<int>*,QVector<int>*);
    const QVector<double> get_y_read_dist();
    const QVector<double> get_y_write_dist();
    void clearDistData();

private:
    QVector<double> y_read_dist;
    QVector<double> y_write_dist;
};

#endif // DISTRIBUTION_H
