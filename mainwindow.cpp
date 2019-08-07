#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "modeling/density.h"
#include "modeling/distribution.h"
#include "modeling/simulation.h"
#include <QtConcurrent>
#include "about.h"

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(2)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->runtime_edit->setValidator(new QIntValidator(0, 10000000, this) );
    ui->userCount_edit->setValidator(new QIntValidator(0, 10000000, this) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSimStatus(QString msg)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage(msg);
}

void MainWindow::on_pushButton_clicked()
{
    if(read_Data.length() == 0 || write_Data.length() == 0){
        QMessageBox msgBox;
        msgBox.setText("Нет исходных данных, выберите файл!");
        msgBox.exec();

        on_selectFile_clicked();

    }

    if(ui->tabWidget->currentIndex()==0){
        density *dens = new density();

        QFuture<void> future = QtConcurrent::run([=](){
            dens->densityCalc(&read_Data, &write_Data);
        });

        QFutureWatcher<void> watcher;
        QEventLoop loop;

        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()),  Qt::QueuedConnection);
        watcher.setFuture(future);
        loop.exec();

        printDensGraph(dens);

    }else if(ui->tabWidget->currentIndex()==1){
        distribution *dist = new distribution();

        QFuture<void> future = QtConcurrent::run([=](){
            dist->distCalc(&read_Data, &write_Data);
        });

        QFutureWatcher<void> watcher;
        QEventLoop loop;

        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()),  Qt::QueuedConnection);
        watcher.setFuture(future);
        loop.exec();

        printDistGraph(dist);
    }else if(ui->tabWidget->currentIndex()==2){

        simulation *sim = new simulation(ui->userCount_edit->text().toInt(), ui->runtime_edit->text().toInt());

        connect(sim, SIGNAL(sendStatus(QString)), this, SLOT(getSimStatus(QString)));
        QFuture<void> future = QtConcurrent::run([=](){
            sim->simCalc(&read_Data, &write_Data);
        });

        QFutureWatcher<void> watcher;
        QEventLoop loop;

        connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()),  Qt::QueuedConnection);
        watcher.setFuture(future);
        loop.exec();

        printSimGraph(sim);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->tabWidget->currentIndex()==0){
        ui->tab->clearGraphs();
        ui->tab->clearItems();
        ui->tab->replot();
        ui->statusBar->showMessage("Очистка графика плотности вероятности", 1000);
    }else if(ui->tabWidget->currentIndex()==1){
        ui->tab_2->clearGraphs();
        ui->tab_2->clearItems();
        ui->tab_2->replot();
        ui->statusBar->showMessage("Очистка графика распределения вероятностей", 1000);
    }else if(ui->tabWidget->currentIndex()==2){
        ui->tab_3->clearGraphs();
        ui->tab_3->clearItems();
        ui->tab_3->replot();
        ui->statusBar->showMessage("Очистка графика симуляции", 1000);
    }else if(ui->tabWidget->currentIndex()==3){
        ui->tab_4->clearGraphs();
        ui->tab_4->clearItems();
        ui->tab_4->replot();
        ui->statusBar->showMessage("Очистка графика распределения вероятностей симуляции", 1000);
    }
}

void MainWindow::on_selectFile_clicked()
{
    read_Data.clear();
    write_Data.clear();
    QString dataFile = QFileDialog::getOpenFileName(nullptr,"Select a file","");
    ui->filePath->setText(dataFile);
    readFile(dataFile);
}

void MainWindow::readFile(QString filename)
{
    QFile file(filename);

    /*Считываем исходный файл в контейнер*/
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        while(!file.atEnd())
        {
            QString data = file.readLine();
            read_Data.append(data.section(' ', 0, 0).toInt());
            write_Data.append(data.section(' ', 1, 1).toInt());
        }
        file.close();
    }

    //Сортируем данные по возрастанию
    std::sort(read_Data.begin(),read_Data.end(), std::less<int>());
    std::sort(write_Data.begin(),write_Data.end(), std::less<int>());
}

void MainWindow::printDensGraph(density* dens)
{
    ui->tab->clearGraphs();
    ui->tab->clearItems();
    ui->tab->replot();
    ui->statusBar->showMessage("Очистка графика плотности вероятности", 500);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->tab);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("Плотность вероятности операций ввода вывода");
    textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger

    ui->tab->addGraph();
    ui->tab->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->tab->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->tab->graph(0)->setName("Read");
    ui->tab->addGraph();
    ui->tab->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->tab->graph(1)->setName("Write");


    ui->tab->xAxis->setLabel("IO/s");
    ui->tab->yAxis->setLabel("Вероятность");
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->tab->xAxis2->setVisible(true);
    ui->tab->xAxis2->setTickLabels(false);
    ui->tab->yAxis2->setVisible(true);
    ui->tab->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->tab->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->tab->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->tab->graph(0)->setData(dens->get_x_read(),dens->get_y_read());
    ui->tab->graph(1)->setData(dens->get_x_write(),dens->get_y_write());
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->tab->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->tab->graph(1)->rescaleAxes(true);
    // Note: we could have also just called ui->tab->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->tab->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectItems);

    ui->tab->legend->setVisible(true);
    ui->tab->replot();

    delete dens;

}

void MainWindow::printDistGraph(distribution* dist)
{
    ui->tab_2->clearGraphs();
    ui->tab_2->clearItems();
    ui->tab_2->replot();
    ui->statusBar->showMessage("Очистка графика распределения вероятностей", 500);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->tab_2);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("Распределение вероятностей операций ввода вывода");
    textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger

    ui->tab_2->addGraph();
    ui->tab_2->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->tab_2->graph(0)->setName("Read");
    ui->tab_2->addGraph();
    ui->tab_2->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->tab_2->graph(1)->setName("Write");


    ui->tab_2->xAxis->setLabel("IO/s");
    ui->tab_2->yAxis->setLabel("Вероятность");
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->tab_2->xAxis2->setVisible(true);
    ui->tab_2->xAxis2->setTickLabels(false);
    ui->tab_2->yAxis2->setVisible(true);
    ui->tab_2->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->tab_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->tab_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab_2->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->tab_2->graph(0)->setData(dist->get_x_read(),dist->get_y_read_dist());
    ui->tab_2->graph(1)->setData(dist->get_x_write(),dist->get_y_write_dist());
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->tab_2->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->tab_2->graph(1)->rescaleAxes(true);
    // Note: we could have also just called ui->tab->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->tab_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->tab_2->legend->setVisible(true);
    ui->tab_2->replot();

    delete dist;
}

void MainWindow::printSimGraph(simulation* sim)
{
    ui->tab_3->clearGraphs();
    ui->tab_3->clearItems();
    ui->tab_3->replot();
    ui->statusBar->showMessage("Очистка графика симуляции", 500);
    ui->tab_4->clearGraphs();
    ui->tab_4->clearItems();
    ui->tab_4->replot();
    ui->statusBar->showMessage("Очистка графика распределения вероятностей симуляции", 500);

    // Добавление текста:
    QCPItemText *textLabel = new QCPItemText(ui->tab_3);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // позиция
    textLabel->setText("Плотность вероятности операций ввода вывода для " + ui->userCount_edit->text() + " польз.");
    textLabel->setFont(QFont(font().family(), 12)); // Размер шрифта

    QCPItemText *textLabel2 = new QCPItemText(ui->tab_4);
    textLabel2->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel2->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel2->position->setCoords(0.5, 0); // позиция
    textLabel2->setText("Распределение вероятностей операций ввода вывода для " + ui->userCount_edit->text() + " польз.");
    textLabel2->setFont(QFont(font().family(), 12)); // Размер шрифта

    ui->tab_3->addGraph();
    ui->tab_3->graph(0)->setPen(QPen(Qt::blue)); // Синяя линия, первый график
    ui->tab_3->graph(0)->setName("Чтение");
    ui->tab_3->addGraph();
    ui->tab_3->graph(1)->setPen(QPen(Qt::red)); // Красная линия, второй график
    ui->tab_3->graph(1)->setName("Запись");

    ui->tab_4->addGraph();
    ui->tab_4->graph(0)->setPen(QPen(Qt::blue)); // Синяя линия, первый график
    ui->tab_4->graph(0)->setName("Чтение");
    ui->tab_4->addGraph();
    ui->tab_4->graph(1)->setPen(QPen(Qt::red)); // Красная линия, второй график
    ui->tab_4->graph(1)->setName("Запись");



    ui->tab_3->xAxis->setLabel("IO/s");
    ui->tab_3->yAxis->setLabel("Вероятность");

    ui->tab_4->xAxis->setLabel("IO/s");
    ui->tab_4->yAxis->setLabel("Вероятность");

    // Настройка осей:
    ui->tab_3->xAxis2->setVisible(true);
    ui->tab_3->xAxis2->setTickLabels(false);
    ui->tab_3->yAxis2->setVisible(true);
    ui->tab_3->yAxis2->setTickLabels(false);

    ui->tab_4->xAxis2->setVisible(true);
    ui->tab_4->xAxis2->setTickLabels(false);
    ui->tab_4->yAxis2->setVisible(true);
    ui->tab_4->yAxis2->setTickLabels(false);
    // Автоматическое изменение размера графика в зависимости от протяженностиs:
    connect(ui->tab_3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab_3->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->tab_3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab_3->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->tab_4->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab_4->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->tab_4->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->tab_4->yAxis2, SLOT(setRange(QCPRange)));
    // Данные для орисовки:
    ui->tab_3->graph(0)->setData(sim->get_x_read(),sim->get_y_read());
    ui->tab_3->graph(1)->setData(sim->get_x_write(),sim->get_y_write());


    ui->tab_4->graph(0)->setData(sim->get_x_read(),sim->get_y_read_dist());
    ui->tab_4->graph(1)->setData(sim->get_x_write(),sim->get_y_write_dist());
    // Рескеил:
    ui->tab_3->graph(0)->rescaleAxes();
    ui->tab_4->graph(0)->rescaleAxes();

    ui->tab_3->graph(1)->rescaleAxes(true);
    ui->tab_4->graph(1)->rescaleAxes(true);

    ui->tab_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->tab_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->tab_3->legend->setVisible(true);
    ui->tab_4->legend->setVisible(true);

    ui->tab_3->replot();
    ui->tab_4->replot();

    delete sim;
}

void MainWindow::on_screenShot_button_clicked()
{
    QString outputFile = QFileDialog::getSaveFileName(nullptr,"Сохранить изображение графика","./graph.png", "Images (*.png)");
    QFile file(outputFile);
    if (!file.open(QIODevice::WriteOnly|QFile::WriteOnly)){
        QMessageBox::warning(nullptr,"Не удаётся создать скриншот",
        QObject::tr( "\n Не удаётся сохранить созданный график на диск!"));
    }

    ui->tab->saveJpg( outputFile,  0, 0, 1.0, -1  );


    if(ui->tabWidget->currentIndex()==0){
        ui->tab->savePng(outputFile,0,0,1.0,-1);
        ui->statusBar->showMessage("Сохранение изображения "+outputFile,2000 );
    }else if(ui->tabWidget->currentIndex()==1){
        ui->tab_2->savePng(outputFile,0,0,1.0,-1);
        ui->statusBar->showMessage("Сохранение изображения "+outputFile,2000 );
    }else if(ui->tabWidget->currentIndex()==2){
        ui->tab_3->savePng( outputFile,0,0,1.0,-1);
        ui->statusBar->showMessage("Сохранение изображения "+outputFile,2000 );
    }else if(ui->tabWidget->currentIndex()==3){
        ui->tab_4->savePng( outputFile,0,0,1.0,-1);
        ui->statusBar->showMessage("Сохранение изображения "+outputFile,2000 );
    }
}

void MainWindow::on_menu_open_file_triggered()
{
   on_selectFile_clicked();
}

void MainWindow::on_menu_about_triggered()
{
    About *aboutWin = new About();
    aboutWin->show();
}

void MainWindow::on_menu_exit_triggered()
{
    QApplication::quit();
}
