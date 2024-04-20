#ifndef GENERATECONCLUSIONS_H
#define GENERATECONCLUSIONS_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "expotthread.h"



class GenerateConclusions : public QWidget
{
    Q_OBJECT
public:
    GenerateConclusions(QWidget* parent = nullptr);
    ~GenerateConclusions();
private:
     QVBoxLayout* vbox = nullptr;
     QPushButton* btn_gen_concl  = nullptr;
     QFileDialog* choose_files = nullptr;
     QStringList list_files;
     ExpotThread* exp = nullptr;

 public slots:
    void select_files();
 signals:
     void give_path(const QStringList&);

};

#endif // GENERATECONCLUSIONS_H
