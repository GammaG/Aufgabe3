#ifndef SUDOKUMAIN_H
#define SUDOKUMAIN_H

#include <QMainWindow>

namespace Ui {
class SudokuMain;
}

class SudokuMain : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SudokuMain(QWidget *parent = 0);
    ~SudokuMain();
    
private:
    Ui::SudokuMain *ui;
};

#endif // SUDOKUMAIN_H
