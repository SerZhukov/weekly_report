#ifndef WORD_H
#define WORD_H

#include <QObject>
#include <QAxObject>

class Word : public QObject
{
    Q_OBJECT
public:
    explicit Word(QObject *parent = nullptr);
    void save(const QString& path) const;
    void add_text(const QString& text);
    void close();
    bool isNull() const;
    void create_document();
    ~Word();
private:
    QAxObject* word = nullptr;
    QAxObject* documents = nullptr;
    QAxObject *document  = nullptr;
    QAxObject* range_word  = nullptr;



signals:

};

#endif // WORD_H
