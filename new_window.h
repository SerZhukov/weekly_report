#ifndef NEW_WINDOW_H
#define NEW_WINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class NewWindow : public QWidget
{
public:
    NewWindow(QWidget* parent = nullptr);
private:
    QVBoxLayout* vbox = nullptr;
    QLabel* label = nullptr;
};

#endif // NEW_WINDOW_H
