#ifndef EXPORT_H
#define EXPORT_H

#include <QProgressDialog>
#include <QObject>
#include <QEventLoop>
#include <QMutex>
#include <QWaitCondition>

#include "expotthread.h"



class Export : public QObject
{
    Q_OBJECT

public:
     Export(QObject* parent = nullptr);
    ~Export();
public slots:
    void export_office(const QStringList& path);
    void setPointerCalledThread(ExpotThread* ptr);
    void setSavePath(const QString& str);
    //const QString& getSavePath();
signals:
    void give_prog(int);
    void give_msg(const QString& msg);
    void show_prog();
    void fihish_export();


private:
    QString save_path;
    ExpotThread* called_thread;
    QEventLoop loop;
    QMutex mutex;
    QWaitCondition waitCondition;





};

#endif // EXPORT_H
