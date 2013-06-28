#ifndef SUDOKUMAIN_H
#define SUDOKUMAIN_H

#include <QMainWindow>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <map>

/**
 * @author Marco Seidler
 * Header-Class for SudokuMain
 */
namespace Ui {
class SudokuMain;
}

class SudokuMain : public QMainWindow
{
    Q_OBJECT
    
public:

    //is used for temporary save values of the Database
    struct Valuepair{
        std::string name;
        int value;
    };


    std::map<int, Valuepair> map;
    QSqlDatabase db;

    int getRandom();
    void connectToDatabase();
    void closeConnection();


    //Boxes, are used for the collection of 3x3 int values
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
    bool checkHorizontal(int box1[], int box2[], int box3[]);
    std::string convertInt(int number);
    bool checkVertical(int box1[], int box2[], int box3[]);
    bool checkBox(int box[]);
    void showDialog(const QString &message);
    void reset();
    void setValues();
    void setField(std::string str, int val);

public slots:

    void checkValues();
    void createNewRound();


private:
    Ui::SudokuMain *ui;

};

#endif // SUDOKUMAIN_H
