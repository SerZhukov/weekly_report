#include "GenerateConclusions.h"


GenerateConclusions::GenerateConclusions(QWidget *parent) : QWidget(parent)
{
    vbox = new QVBoxLayout();
    btn_gen_concl = new QPushButton("Generate conclusions");
    vbox->addWidget(btn_gen_concl);
    setLayout(vbox);
    resize(300, 300);
    connect(btn_gen_concl, &QPushButton::clicked, this, &GenerateConclusions::select_files);

}

void GenerateConclusions::select_files()
{
    choose_files = new QFileDialog(this, "Select files",
                                   "C:\\", "Excel files (*.xlsx *.xls)");
    choose_files->setFileMode(QFileDialog::ExistingFiles);
    choose_files->setLabelText(QFileDialog::Accept, "Выбрать файлы");
    if(choose_files->exec())
    {
        list_files = choose_files->selectedFiles();
        exp = new Export(this);
        connect(this, &GenerateConclusions::give_path, exp, &Export::export_office);
        emit give_path(list_files);
    }
    else
    {
         qDebug() << "No files selected";
    }


}

