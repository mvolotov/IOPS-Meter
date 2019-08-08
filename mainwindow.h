#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "modeling/simulation.h"
#include <QTranslator>
#include <QLocale>
#include <QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getSimStatus(QString);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_selectFile_clicked();
    void on_screenShot_button_clicked();

    void on_menu_open_file_triggered();

    void on_menu_about_triggered();

    void on_menu_exit_triggered();

    void on_languageEn_triggered();

    void on_languageRu_triggered();

private:
    Ui::MainWindow *ui;
    void readFile(QString);

    QVector<int> read_Data;
    QVector<int> write_Data;

    void printDensGraph(density*);
    void printDistGraph(distribution*);
    void printSimGraph(simulation*);

    QTranslator *qtLanguageTranslator;
    void changeTranslator(QString);
    void changeEvent(QEvent*);
};

#endif // MAINWINDOW_H
