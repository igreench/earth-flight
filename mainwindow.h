#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "glwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    QPushButton *button;
    GLWidget glWidget;
    QComboBox *combo1;
    QComboBox *combo2;
    bool isStarted;
};

#endif // MAINWINDOW_H
