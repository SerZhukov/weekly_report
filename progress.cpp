#include "progress.h"

Progress::Progress(QWidget* parent) : QWidget(parent),
    progress(new QProgressDialog()), vbox(new QVBoxLayout()),
    label(new QLabel("Waiting"))
{

    label->setFrameStyle(2);
    vbox->addWidget(label);
    vbox->addWidget(progress);
    setLayout(vbox);
    resize(500, 200);

}

void Progress::setValue(int i)
{
    progress->setValue(i);
}

void Progress::setText(const QString &mess)
{
    label->setText(mess);
}

void Progress::setRange(int min, int max)
{
    progress->setRange(min, max);
}

void Progress::setAutoClose(bool close)
{
    progress->setAutoClose(close);
}

void Progress::setAutoReset(bool reset)
{
    progress->setAutoReset(reset);
}

int Progress::value() const
{
    return progress->value();
}
