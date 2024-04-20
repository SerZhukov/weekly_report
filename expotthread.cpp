#include "expotthread.h"
#include <QProgressDialog>
#include <QFileDialog>
#include "export.h"



ExpotThread::ExpotThread()
{

//    QProgressDialog* progress_bar = new QProgressDialog;
//    progress_bar->close();
//    progress_bar->setAutoClose(false);
//    progress_bar->setAutoReset(false);
//    progress_bar->setWindowModality(Qt::ApplicationModal);
//    progress_bar->setFixedSize(600, 100);
    exp = new Export;
    thread = new QThread(this);
    exp->moveToThread(thread);
    connect(this, &ExpotThread::give_path, exp, &Export::export_office);
    connect(exp, &Export::fihish_export, thread, &QThread::quit);
    connect(this, &ExpotThread::give_save, exp, &Export::setSavePath);
    connect(this, &ExpotThread::give_this, exp, &Export::setPointerCalledThread);
    //    connect(this, &Export::give_prog,  progress_bar, &QProgressDialog::setValue);
    //    connect(this, &Export::give_msg,  progress_bar, &QProgressDialog::setLabelText);
    //    connect(this, &Export::show_prog,  progress_bar, &QProgressDialog::show);
    thread->start();


}

ExpotThread::~ExpotThread()
{
    delete exp;
    qDebug() << "Called ExpotThread::~ExpotThread()";
}

void ExpotThread::export_office(const QStringList &path)
{
    //передача указателя на класс агрегатор, для возможности последующих вызовов методов класса агрегатора
    emit give_this(this);
    //передача пути экспортируемых файлов
    emit give_path(path);
}

void ExpotThread::saveFaile()
{
    qDebug() << "Method saveFaile is" << QThread::currentThreadId() << "start";
    save_path = QFileDialog::getSaveFileName(nullptr,
                                             "Сохранить выводы", "C://", "Word (*.docx *doc)");
    emit give_save(save_path);
    //QMetaObject::invokeMethod(exp, "setSavePath", Qt::QueuedConnection , Q_ARG(QString, save_path));
    qDebug() << "Method saveFaile is" << QThread::currentThreadId() << "finish";

}
