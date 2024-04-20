#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QFileDialog>
#include <QWidget>

class FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    FileDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Dialog);
public slots:
};

#endif // FILEDIALOG_H
