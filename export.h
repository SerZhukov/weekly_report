#ifndef EXPORT_H
#define EXPORT_H

#include <QProgressDialog>
#include <QObject>
#include "word.h"


class Export : public QObject
{
    Q_OBJECT

public:
     Export(QObject* parent = nullptr);
    ~Export();
public slots:
    void export_office(const QStringList& path);
signals:
    void give_prog(int);
    void give_msg(const QString& msg);
    void show_prog();


private:

    Word* word = nullptr;
    QProgressDialog* progress_bar = nullptr;
};

#endif // EXPORT_H
