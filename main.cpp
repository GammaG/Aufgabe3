#include "sudokumain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuMain w;
    w.show();
    
    return a.exec();
}
