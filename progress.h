#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>
#include <QProgressDialog>
#include <QVBoxLayout>
#include <QLabel>

class Progress : public QWidget
{
    Q_OBJECT
public:
    Progress(QWidget* parent = nullptr);
public slots:
    void setValue(int i);
    void setText(const QString& mess);
    void setRange(int min, int max);
    void setAutoClose(bool close);
    void setAutoReset(bool reset);
public:
    int value() const;
private:
    QProgressDialog* progress = nullptr;
    QVBoxLayout* vbox = nullptr;
    QLabel* label = nullptr;

};

#endif // PROGRESS_H
