#ifndef EXPOTTHREAD_H
#define EXPOTTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

class Export;

class ExpotThread : public QObject
{
    Q_OBJECT
    QThread* thread;
    Export* exp;
    QString save_path;



public:
    ExpotThread();
    ~ExpotThread();

public slots:
    void export_office(const QStringList& path);
    void saveFaile();
signals:
    void give_path(const QStringList&);
    void give_save(const QString&);
    void give_this(ExpotThread* ptr);


};

#endif // EXPOTTHREAD_H
