#include "density.h"

density::density(QObject *parent) : QObject(parent)
{

}

density::~density()
{
    clearDensData();
}

const QVector<double> density::get_x_read()
{
    return x_read;
}

const QVector<double> density::get_x_write()
{
    return x_write;
}

const QVector<double> density::get_y_write()
{
    return y_write;
}

const QVector<double> density::get_y_read()
{
    return y_read;
}

void density::densityCalc(QVector<int> *rd, QVector<int> *wd)
{
    QVector<int> readBuff = *rd;
    QVector<int> writeBuff = *wd;
    foreach( int value, readBuff ){
        if(readBuff.count(value)==0)
            continue;
        x_read.append(value);
        y_read.append((static_cast<double>(readBuff.count(value))/static_cast<double>(rd->length())));
        readBuff.removeAll(value);
    }

    foreach( int value, writeBuff ){
        if(writeBuff.count(value)==0)
            continue;
        x_write.append(value);
        y_write.append((static_cast<double>(writeBuff.count(value))/static_cast<double>(wd->length())));
        writeBuff.removeAll(value);
    }
}

void density::clearDensData()
{
    y_read.clear();
    y_write.clear();
    x_read.clear();
    x_write.clear();
}
