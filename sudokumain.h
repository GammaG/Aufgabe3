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

    int tlBox[9];
    int tmBox[9];
    int trBox[9];

    int mlBox[9];
    int mmBox[9];
    int mrBox[9];

    int dlBox[9];
    int dmBox[9];
    int drBox[9];

    explicit SudokuMain(QWidget *parent = 0);
    ~SudokuMain();
    void getBoxValues();
    bool checkValues();
    bool checkHorizontal(int box1[], int box2[], int box3[]);

    
private:
    Ui::SudokuMain *ui;
};

#endif // SUDOKUMAIN_H
