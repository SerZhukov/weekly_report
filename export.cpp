#include "export.h"
#include <QAxObject>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QThread>
#include "word.h"

Export::Export(QObject* parent) : QObject(parent)

{


}

Export::~Export()
{

}

void Export::export_office(const QStringList& path)
    {
        qDebug() << "Method export_office is" << QThread::currentThreadId();
        Word* word = new Word;
        emit show_prog();
        emit give_msg("Waiting...");
        if(word->isNull())
        {
            QMessageBox::information(nullptr, "weekly report", "Error opening word.");
            return;
        }
        else
        {
            word->create_document();
        }

        QAxObject* excel = new QAxObject( "Excel.Application");
        if(excel->isNull())
        {
            qDebug() << "Error opening excel";
            return;
        }
        QAxObject* workbooks = excel->querySubObject("Workbooks");
        double value_progress = 0;
        emit give_prog(value_progress);
        double step_progress = 100.0/path.count();
        for (qsizetype i = 0; i < path.count(); ++i )
        {
            emit give_msg("Export " + path[i]);
            QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", path[i]);
            QAxObject* worksheets = workbook->querySubObject("Worksheets(int)", 1);
            QAxObject* range = worksheets->querySubObject("UsedRange");
            QAxObject* foundCell_1 = range->querySubObject("Find(const QString&)", "Вывод:");
            if(!foundCell_1)
            {
                emit give_msg("Value no find: " + path[i]);
                workbook->dynamicCall("Close()");
                value_progress += step_progress;
                emit give_prog(value_progress);
            }
            else
            {
                QAxObject *foundCell_2 = foundCell_1->querySubObject("Offset(int, int)", 1, 0);
                QString value = foundCell_2->dynamicCall("Value").toString();
                word->add_text(value);
                workbook->dynamicCall("Close()");
                value_progress += step_progress;
                emit give_prog(value_progress);
            }
        }
        emit give_msg("Completed");
        value_progress = 100;
        emit give_prog(value_progress);

        QMetaObject::invokeMethod(called_thread, "saveFaile", Qt::BlockingQueuedConnection);
        loop.exec();
        //QMutexLocker locker(&mutex);
        //waitCondition.wait(&mutex);
        //QCoreApplication::processEvents();


        if(save_path != "")
        {
            qDebug() << save_path;
            word->save(save_path);
        }
        else
        {
            emit give_msg("No selected path save");
            qDebug() << "Word close start";
            word->close();
            qDebug() << "Word close finish";
        }
        excel->dynamicCall("Quit()");
        delete word;
        qDebug() << "Finish export";
       emit fihish_export();
       loop.quit();
    }

    void Export::setPointerCalledThread(ExpotThread *ptr)
    {
        called_thread = ptr;
    }

    void Export::setSavePath(const QString &str)
    {
        qDebug() << "Called setSavePath ";
        save_path = str;
        loop.quit();
        //waitCondition.wakeAll();
    }







