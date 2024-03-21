#ifndef EXPORT_TO_OFFICE_H
#define EXPORT_TO_OFFICE_H
#include <QWidget>
#include "export.h"
#include <QAxObject>
#include <QFileDialog>
#include <QApplication>

Export::Export(QWidget *parent)
    : QWidget(parent)
{
    progress_bar = new Progress(this);
    progress_bar->setWindowFlags(Qt::Window);
    progress_bar->setRange(0, 100);
    progress_bar->setAutoClose(false);
    progress_bar->setAutoReset(false);
    progress_bar->setWindowModality(Qt::ApplicationModal);
    connect(this, &Export::give_progress, progress_bar, &Progress::setValue);
    connect(this, &Export::start_progress, this, [this] ()
            {progress_bar->show();});
}

Export::~Export()
{
    delete progress_bar;
}

void Export::export_office(const QStringList& path)
    {
        emit start_progress();
        qApp->processEvents();
        progress_bar->setText("Create word document");
        qDebug() << "Create word document";
        QAxObject* word =  new QAxObject( "Word.Application", nullptr);
        QAxObject* documents = word->querySubObject("Documents");
        QAxObject *document = documents->querySubObject("Add()");
        QAxObject* range_word = document->querySubObject("Range()");

        int value_progress = 5;
        emit give_progress(value_progress);

        progress_bar->setText("Create excel document");
        qDebug() << "Create excel document";
        QAxObject* excel = new QAxObject( "Excel.Application");
        QAxObject* workbooks = excel->querySubObject("Workbooks");
        value_progress += 5;
        emit give_progress(value_progress);

        qDebug() << "Start export";

        int step_progress = 90/path.count();

        for (qptrdiff i = 0; i < path.count(); ++i )
        {
            qDebug() << "Export:" << path[i];
            progress_bar->setText("Start export " + path[i]);
            QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", path[i]);
            QAxObject* worksheets = workbook->querySubObject("Worksheets(int)", 1);
            QAxObject* range = worksheets->querySubObject("UsedRange");
            QAxObject *foundCell_1 = range->querySubObject("Find(const QString&)", "Вывод:");
            if(!foundCell_1)
            {
                qDebug() << "Value no find";
                progress_bar->setText("Value no find: " + path[i]);
                workbook->dynamicCall("Close()");
                value_progress += step_progress;
                emit give_progress(value_progress);
                continue;
            }
            QAxObject *foundCell_2 = foundCell_1->querySubObject("Offset(int, int)", 1, 0);
            QString value = foundCell_2->dynamicCall("Value").toString();
            range_word->dynamicCall("InsertAfter(const QString&)", value);
            workbook->dynamicCall("Close()");
            qDebug() << "Comleted export:" << path[i];
            value_progress += step_progress;
            emit give_progress(value_progress);
            progress_bar->setText("Completed export " + path[i]);
        }
        QString save_path;
        save_path = QFileDialog::getSaveFileName(nullptr,
                                                 "Сохранить выводы", "C://", "Word (*.docx *doc)");
        if(save_path != "")
        {
            document->dynamicCall("SaveAs(const QString&)", save_path);
        }
        else
        {
            qDebug() << "No save path selected";
            document->dynamicCall("Close(wdDoNotSaveChanges)");

        }
        qDebug() << "Start exit excel";
        excel->dynamicCall("Quit()");
        qDebug() << "Finish exit excel";
        qDebug() << "Start exit word";

        word->dynamicCall("Quit()");
        qDebug() << "Finish exit word";
        progress_bar->setText("Completed");
        value_progress = 100;
        emit give_progress(value_progress);

        qDebug() << "Finish";
    }
#endif // EXPORT_TO_OFFICE_H
