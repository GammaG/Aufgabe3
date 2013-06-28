#include "sudokumain.h"
#include <QApplication>

/**
 * @author Marco Seidler
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuMain w;
    w.show();
    
    return a.exec();
}
