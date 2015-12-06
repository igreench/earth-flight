#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

MainWindow::MainWindow() {
    QWidget *centralWidget = new QWidget(this);

    isStarted = false;

    button = new QPushButton("Start");
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QHBoxLayout *hlayout3 = new QHBoxLayout();

    combo1 = new QComboBox();
    combo2 = new QComboBox();
    combo1->addItem("New York");
    combo1->setCurrentIndex(-1);
    combo2->addItem("Moscow");
    combo2->setCurrentIndex(-1);

    QLabel *label1 = new QLabel("From");
    label1->setGeometry(0, 0, 200, 40);
    QLabel *label2 = new QLabel("To");
    label2->setGeometry(0, 0, 200, 40);

    centralWidget->setLayout(vlayout);

    //vlayout->addLayout(hlayout1);
    //vlayout->addLayout(hlayout2);
    vlayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    vlayout->addLayout(hlayout3);
    hlayout1->addWidget(label1);
    hlayout1->addWidget(combo1);
    hlayout1->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout2->addWidget(label2);
    hlayout2->addWidget(combo2);
    hlayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    hlayout3->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout3->addWidget(button);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_clicked()));

    setCentralWidget(centralWidget);
    resize(300, 300);
}

MainWindow::~MainWindow() {
}

void MainWindow::on_pushButton_clicked() {
    //if (combo1->currentIndex() != -1 && combo2->currentIndex() != -1) {
        glWidget.show();
        glWidget.resize(300, 300);
        if (!isStarted) {
            isStarted = true;
            glWidget.start();
        }
    //}
}
