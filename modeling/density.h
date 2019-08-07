#ifndef DENSITY_H
#define DENSITY_H

#include <QObject>
#include <QVector>
#include <QString>

class density : public QObject
{
    Q_OBJECT
public:
    explicit density(QObject *parent = nullptr);
    ~density();
    const QVector<double> get_x_read();
    const QVector<double> get_x_write();
    const QVector<double> get_y_write();
    const QVector<double> get_y_read();
    void densityCalc(QVector<int>*, QVector<int>*);
    void clearDensData();

private:
    QVector<double> x_read;
    QVector<double> x_write;
    QVector<double> y_read;
    QVector<double> y_write;
public slots:
};

#endif // DENSITY_H
