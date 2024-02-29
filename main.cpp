#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    const QMetaObject* pmo = w.metaObject();
//    for (qptrdiff i = 0; i < pmo->propertyCount(); ++i )
//    {
//        const QMetaProperty mp = pmo->property(i);
//        qDebug() << "Property";
//        qDebug() << "Type: " << mp.typeName();
//        qDebug() << "Name: " << mp.name();
//        qDebug() << "Value: " << w.property(mp.name());

//    }



    return a.exec();
}
