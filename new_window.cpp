#include "new_window.h"

NewWindow::NewWindow(QWidget *parent) : QWidget(parent)
{
    vbox = new QVBoxLayout(this);
    label = new QLabel("Hello, World", this);
    label->setAlignment(Qt::AlignHCenter);
    vbox->addWidget(label);
    setLayout(vbox);

}
