#include "distribution.h"

distribution::distribution()
{

}

distribution::~distribution()
{
    clearDensData();
    clearDistData();
}

void distribution::distCalc(QVector<int> *rd, QVector<int> *wd)
{
    densityCalc(rd,wd);

    double rDist = 0.0, wDist = 0.0;

    for(int i = 0; i < get_x_read().length(); i++){
        rDist+=get_y_read().at(i);
        y_read_dist.push_back(rDist);
    }

    for(int i = 0; i < get_x_write().length(); i++){
        wDist+=get_y_write().at(i);
        y_write_dist.push_back(wDist);
    }

}

const QVector<double> distribution::get_y_read_dist()
{
    return y_read_dist;
}

const QVector<double> distribution::get_y_write_dist()
{
    return y_write_dist;
}

void distribution::clearDistData()
{
    y_read_dist.clear();
    y_write_dist.clear();
}


