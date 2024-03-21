#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>
#include "progress.h"

class Export : public QWidget
{
    Q_OBJECT
public:
     Export(QWidget *parent = nullptr);
    ~Export();
public slots:
    void export_office(const QStringList& path);

signals:
    void give_progress(int i);
    void start_progress();
private:
    Progress* progress_bar = nullptr;

};

#endif // EXPORT_H
