#include "mainwindow.h"
#include "GenerateConclusions.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    vbox = new QVBoxLayout();
    btn_quit = new QPushButton("Exit");
    btn_gen_concl = new QPushButton("Generate conclusions");
    main_widget = new QWidget();
    vbox->addWidget(btn_gen_concl);
    vbox->addWidget(btn_quit);
    main_widget->setLayout(vbox);
    setCentralWidget(main_widget);
    this->resize(400, 400);
    connect(btn_quit, &QPushButton::clicked, qApp->quit);
    connect(btn_gen_concl, &QPushButton::clicked, this, [](){
        GenerateConclusions* w = new GenerateConclusions();
        w->select_files();
        delete w;
    });

}


MainWindow::~MainWindow()
{

}
