#include "mainwindow.h"
#include "new_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    vbox = new QVBoxLayout(main_widget);
    btn_quit = new QPushButton("Exit", main_widget);
    btn_window = new QPushButton("New window", main_widget);
    btn_test = new QPushButton("Test", main_widget);
    btn_open_files = new QPushButton("Open files", main_widget);
    label = new QLabel("Hello, World!", main_widget);
    label->setAlignment(Qt::AlignCenter);
    main_widget = new QWidget(this);
    vbox->addWidget(label);
    vbox->addWidget(btn_window);
    vbox->addWidget(btn_test);
    vbox->addWidget(btn_open_files);
    vbox->addWidget(btn_quit);
    main_widget->setLayout(vbox);
    setCentralWidget(main_widget);
    this->resize(400, 400);
    //connect(btn_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    //connect(btn_quit, &QPushButton::clicked, [] () {qApp->quit();});
    connect(btn_quit, &QPushButton::clicked, qApp->quit);
//    connect(btn_test, &QPushButton::clicked, [this]()
//            {
//        this->push();
//    });
    connect(btn_window, &QPushButton::clicked, this, &MainWindow::push);
    //connect(btn_window, SIGNAL(clicked()), SLOT(push()));
    connect(this, SIGNAL(test_signal(QString)), SLOT(my_signal(QString)));
    connect(btn_test, &QPushButton::clicked, this,  &MainWindow::test);
    connect(btn_open_files, &QPushButton::clicked, this, [this](){
        this->list_files = QFileDialog::getOpenFileNames(this, "Test");
    });
}

MainWindow::~MainWindow()
{

}

void MainWindow::push()
{
    w = new NewWindow();
    w->resize(200, 200);
    w->show();
    emit test_signal("Hello, World");
}

void MainWindow::my_signal(QString str)
{
    qDebug() << str << Qt::endl;
}

void MainWindow::test()
{
    foreach (const QString &str, list_files) {

        qDebug() << str << Qt::endl;

    }
}
