#include "word.h"
#include <QApplication>
#include <QThread>

Word::Word(QObject *parent)
    : QObject{parent}
{
    word = new QAxObject( "Word.Application");
    qDebug() << "Called Word";
    qDebug() << "Thread Word is " << QThread::currentThreadId();
    qDebug() << " Word is " << word->isNull();

}

void Word::save(const QString& path) const
{
    document->dynamicCall("SaveAs(const QString&)", path);
}


void Word::add_text(const QString& text)
{
    range_word->dynamicCall("InsertAfter(const QString&)", text);
}

void Word::close()
{
    document->dynamicCall("Close(wdDoNotSaveChanges)");
}

bool Word::isNull() const
{
    return word->isNull();
}

void Word::create_document()
{
    documents = word->querySubObject("Documents");
    document = documents->querySubObject("Add()");
    range_word = document->querySubObject("Range()");
}

Word::~Word()
{

    word->dynamicCall("Quit()");
    delete word;
}
