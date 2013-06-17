#include "sudokumain.h"
#include "ui_sudokumain.h"

SudokuMain::SudokuMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SudokuMain)
{
    ui->setupUi(this);
}

SudokuMain::~SudokuMain()
{
    delete ui;
}
