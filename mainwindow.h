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
    QPushButton* btn_quit = nullptr;
    QPushButton* btn_gen_concl = nullptr;
    QWidget* main_widget = nullptr;
private slots:

signals:

};
#endif // MAINWINDOW_H
