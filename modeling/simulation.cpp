#include "simulation.h"
#include <QDebug>
#include <QElapsedTimer>

simulation::simulation(int client, int rt)
{
    clients = client;
    runtime = rt;

    qsrand(QDateTime::currentDateTime().toTime_t());
}

simulation::~simulation()
{
    clearDensData();
    clearDistData();
}

void simulation::simCalc(QVector<int>* rd, QVector<int>* wd)
{
    QElapsedTimer timer;
    timer.start();
    densityCalc(rd,wd);

    int r, w;

    for (int i = 0; i < runtime; i++) {
        if(i % (runtime/100) == 0)
            emit sendStatus(tr("Прогресс моделирования ") + QString::number((i/(runtime/100))) + "/" + QString::number((runtime/(runtime/100)))+"%");

            r = w = 0;
            for (int j = 0; j < clients; j++) {
                r += rrand();
                w += wrand();
            }

            read_sim_data->push_back(r);
            write_sim_data->push_back(w);
    }

    std::sort(read_sim_data->begin(),read_sim_data->end(), std::less<int>());
    std::sort(write_sim_data->begin(),write_sim_data->end(), std::less<int>());

    emit sendStatus(tr("Очистка данных"));
    clearDensData();
    clearDistData();

    emit sendStatus(tr("Расчёт распределения плотности вероятности"));
    distCalc(read_sim_data, write_sim_data);

    delete read_sim_data;
    delete write_sim_data;

    qDebug() << tr("Bench Time = ") << timer.elapsed();
}

int simulation::rrand()
{
    double r, r1 = 0.0;
    r = static_cast<double>(qrand())/ RAND_MAX;

    for (int i = 0; i < get_y_read().length(); i++) {
        r1 += get_y_read().at(i);
        if (r < r1){
            return static_cast<int>(get_x_read().at(i));
        }
    }
    return 0;
}

int simulation::wrand()
{
    double r, r1 = 0.0;
    r = static_cast<double>(qrand())/ RAND_MAX;

    for (int i = 0; i < get_y_write().length(); i++) {
            r1 += get_y_write().at(i);
            if (r < r1){
                return static_cast<int>(get_x_write().at(i));
            }
    }
    return 0;
}
