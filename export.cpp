#include <QWidget>
#include "export.h"
#include <QAxObject>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <QProgressDialog>



Export::Export(QObject* parent) : QObject(parent)

{

    word = new Word;
    progress_bar = new QProgressDialog();
    progress_bar->close();
    progress_bar->setAutoClose(false);
    progress_bar->setAutoReset(false);
    progress_bar->setWindowModality(Qt::ApplicationModal);
    progress_bar->setFixedSize(600, 100);
    connect(this, &Export::give_prog,  progress_bar, &QProgressDialog::setValue);
    connect(this, &Export::give_msg,  progress_bar, &QProgressDialog::setLabelText);
    connect(this, &Export::show_prog,  progress_bar, &QProgressDialog::show);
}


Export::~Export()
{
    delete word;
    //delete progress_bar;
}

void Export::export_office(const QStringList& path)
    {
        //qApp->processEvents();
        //progress_bar->show();
        emit show_prog();
        //progress_bar->setLabelText("Waiting...");
        emit give_msg("Waiting...");
        if(word->isNull())
        {
            QMessageBox::information(nullptr, "weekly report", "Error opening excel.");
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
        //progress_bar->setValue(value_progress);
        emit give_prog(value_progress);
        double step_progress = 100.0/path.count();
        for (qsizetype i = 0; i < path.count(); ++i )
        {
            //progress_bar->setLabelText("Export " + path[i]);
            emit give_msg("Export " + path[i]);
            QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", path[i]);
            QAxObject* worksheets = workbook->querySubObject("Worksheets(int)", 1);
            QAxObject* range = worksheets->querySubObject("UsedRange");
            QAxObject *foundCell_1 = range->querySubObject("Find(const QString&)", "Вывод:");
            if(!foundCell_1)
            {
                //progress_bar->setLabelText("Value no find: " + path[i]);
                emit give_msg("Value no find: " + path[i]);
                workbook->dynamicCall("Close()");
                value_progress += step_progress;
                //progress_bar->setValue(value_progress);
                emit give_prog(value_progress);
                continue;
            }
            QAxObject *foundCell_2 = foundCell_1->querySubObject("Offset(int, int)", 1, 0);
            QString value = foundCell_2->dynamicCall("Value").toString();
            word->add_text(value);
           // range_word->dynamicCall("InsertAfter(const QString&)", value);
            workbook->dynamicCall("Close()");
            value_progress += step_progress;
            //progress_bar->setValue(value_progress);
            emit give_prog(value_progress);

        }
        //progress_bar->setLabelText("Completed");
        emit give_msg("Completed");
        value_progress = 100;
        //progress_bar->setValue(value_progress);
        emit give_prog(value_progress);
        QString save_path;
        save_path = QFileDialog::getSaveFileName(nullptr,
                                                 "Сохранить выводы", "C://", "Word (*.docx *doc)");
        if(save_path != "")
        {

            word->save(save_path);
        }
        else
        {
            //progress_bar->setLabelText("No selected path save");
            emit give_msg("No selected path save");
            word->close();
        }
        excel->dynamicCall("Quit()");

    }

