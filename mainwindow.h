#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QFileDialog>
#include <QStringList>

class NewWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private:
    QVBoxLayout* vbox = nullptr;
    QPushButton* btn_window = nullptr;
    QPushButton* btn_quit = nullptr;
    QPushButton* btn_test = nullptr;
    QPushButton* btn_open_files = nullptr;
    QWidget* main_widget = nullptr;
    QLabel* label = nullptr;
    QWidget* w = nullptr;
    QStringList list_files;



private slots:
    void push();
    void my_signal(QString str);
    void test();



signals:
    void test_signal(QString str);

};
#endif // MAINWINDOW_H
