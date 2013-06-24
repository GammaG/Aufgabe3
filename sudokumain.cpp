#include "sudokumain.h"
#include "ui_sudokumain.h"
#include "iostream"
#include "QErrorMessage"
#include "sqlconnector.h"
#include "QtGui"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "iostream"
#include "QDir"
#include <cstdlib>



SudokuMain::SudokuMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SudokuMain)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(checkValues()));

    connect(ui->actionNeu, SIGNAL(triggered()), this, SLOT(createNewRound()));

    connectToDatabase();
    closeConnection();
}



SudokuMain::~SudokuMain()
{
    delete ui;
}

/** Methode loades new Values for UI and sets them
 * @brief SudokuMain::createNewRound
 */
void SudokuMain::createNewRound(){
    std::cout << "gehe rein tue nix" << std::endl;


}


/** Methode reads actually values and adds them to Arrays
 * @brief SudokuMain::getBoxValues
 */
void SudokuMain::getBoxValues(){



    //first Box top left
    tlBox[0] = ui->tl11->value();
    tlBox[1] = ui->tl12->value();
    tlBox[2] = ui->tl13->value();
    tlBox[3] = ui->tl21->value();
    tlBox[4] = ui->tl22->value();
    tlBox[5] = ui->tl23->value();
    tlBox[6] = ui->tl31->value();
    tlBox[7] = ui->tl32->value();
    tlBox[8] = ui->tl33->value();



    //second Box top middle
    tmBox[0] = ui->tm11->value();
    tmBox[1] = ui->tm12->value();
    tmBox[2] = ui->tm13->value();
    tmBox[3] = ui->tm21->value();
    tmBox[4] = ui->tm22->value();
    tmBox[5] = ui->tm23->value();
    tmBox[6] = ui->tm31->value();
    tmBox[7] = ui->tm32->value();
    tmBox[8] = ui->tm33->value();



    //third Box top right
    trBox[0] = ui->tr11->value();
    trBox[1] = ui->tr12->value();
    trBox[2] = ui->tr13->value();
    trBox[3] = ui->tr21->value();
    trBox[4] = ui->tr22->value();
    trBox[5] = ui->tr23->value();
    trBox[6] = ui->tr31->value();
    trBox[7] = ui->tr32->value();
    trBox[8] = ui->tr33->value();


    //first Box middle left
    mlBox[0] = ui->ml11->value();
    mlBox[1] = ui->ml12->value();
    mlBox[2] = ui->ml13->value();
    mlBox[3] = ui->ml21->value();
    mlBox[4] = ui->ml22->value();
    mlBox[5] = ui->ml23->value();
    mlBox[6] = ui->ml31->value();
    mlBox[7] = ui->ml32->value();
    mlBox[8] = ui->ml33->value();



    //second Box middle middle
    mmBox[0] = ui->mm11->value();
    mmBox[1] = ui->mm12->value();
    mmBox[2] = ui->mm13->value();
    mmBox[3] = ui->mm21->value();
    mmBox[4] = ui->mm22->value();
    mmBox[5] = ui->mm23->value();
    mmBox[6] = ui->mm31->value();
    mmBox[7] = ui->mm32->value();
    mmBox[8] = ui->mm33->value();



    //third Box middle right
    mrBox[0] = ui->mr11->value();
    mrBox[1] = ui->mr12->value();
    mrBox[2] = ui->mr13->value();
    mrBox[3] = ui->mr21->value();
    mrBox[4] = ui->mr22->value();
    mrBox[5] = ui->mr23->value();
    mrBox[6] = ui->mr31->value();
    mrBox[7] = ui->mr32->value();
    mrBox[8] = ui->mr33->value();


    //first Box down left
    dlBox[0] = ui->dl11->value();
    dlBox[1] = ui->dl12->value();
    dlBox[2] = ui->dl13->value();
    dlBox[3] = ui->dl21->value();
    dlBox[4] = ui->dl22->value();
    dlBox[5] = ui->dl23->value();
    dlBox[6] = ui->dl31->value();
    dlBox[7] = ui->dl32->value();
    dlBox[8] = ui->dl33->value();



    //second Box down middle
    dmBox[0] = ui->dm11->value();
    dmBox[1] = ui->dm12->value();
    dmBox[2] = ui->dm13->value();
    dmBox[3] = ui->dm21->value();
    dmBox[4] = ui->dm22->value();
    dmBox[5] = ui->dm23->value();
    dmBox[6] = ui->dm31->value();
    dmBox[7] = ui->dm32->value();
    dmBox[8] = ui->dm33->value();



    //first Box down left
    drBox[0] = ui->dr11->value();
    drBox[1] = ui->dr12->value();
    drBox[2] = ui->dr13->value();
    drBox[3] = ui->dr21->value();
    drBox[4] = ui->dr22->value();
    drBox[5] = ui->dr23->value();
    drBox[6] = ui->dr31->value();
    drBox[7] = ui->dr32->value();
    drBox[8] = ui->dr33->value();

}

/** Methode checks values and returns true if all rules are completed else false.
 * @brief SudokuMain::checkValues
 * @return
 */
void SudokuMain::checkValues()
{



    getBoxValues();
    //Horizontal check
    if(    !checkHorizontal(tlBox, tmBox, trBox)
        || !checkHorizontal(mlBox, mmBox, mrBox)
        || !checkHorizontal(dlBox, dmBox, drBox)){

        showDialog("Wrong, Check Horizontal Lines! ");

        return;
    }
    if(   !checkVertical(tlBox,mlBox,dlBox)
       || !checkVertical(tmBox,mmBox,dmBox)
       || !checkVertical(trBox,mrBox,drBox) ){

        showDialog("Wrong, Check Vertical Lines! ");

        return;
   }

    if(   !checkBox(tlBox) || !checkBox(tmBox) || !checkBox(trBox)
       || !checkBox(mlBox) || !checkBox(mmBox) || !checkBox(mrBox)
       || !checkBox(dlBox) || !checkBox(dmBox) || !checkBox(drBox))
    {

        showDialog("Wrong, Check the Boxes! ");
        return;
    }

        showDialog("Gratulation, You win ! ");

return;

}



void SudokuMain::showDialog(const QString &message){

    QErrorMessage* error = new QErrorMessage();

    error->showMessage(message);

}

/** Methode checks every Horizontal line that numbers 1-9 are unique
 * @brief SudokuMain::checkHorizontal
 * @param box1
 * @param box2
 * @param box3
 * @return
 */
bool SudokuMain::checkHorizontal(int box1[], int box2[], int box3[]){

    int x = 0;
    int y = 0;
    int counter = 0;

    for(int c = 1; c < 4; ++c){


    switch(c)
    {
    case 1: { x = 0; y = 3; } break;
    case 2: { x = 3; y = 6; } break;
    case 3: { x = 6; y = 9; } break;

    }

    int tempArray[9];

    for(int i = 0; i < 3; ++i){


        for(int j = x; j < y; ++j) {

            switch(i){
            case 0 : tempArray[counter] = box1[j]; break;
            case 1 : tempArray[counter] = box2[j]; break;
            case 2 : tempArray[counter] = box3[j]; break;
            }
            ++counter;

        }
    }



    for(int i = 0; i < 9; ++i){
        int temp = tempArray[i];
        for(int j = i; j < 9; ++j){
            if(temp == tempArray[j] || tempArray[j] == 0){
                return false;
            }
        }


    }
}
return true;

}

/** Methode checks every Vertical line that numbers 1-9 are unique
 * @brief SudokuMain::checkVertical
 * @param box1
 * @param box2
 * @param box3
 * @return
 */
bool SudokuMain::checkVertical(int box1[], int box2[], int box3[]){

    int x = 0;
    int y = 0;

    int counter = 0;

    for(int c = 1; c < 4; ++c){


    switch(c)
    {
    case 1: { x = 0; y = 7;} break;
    case 2: { x = 1; y = 8;} break;
    case 3: { x = 2; y = 9;} break;

    }

    int tempArray[9];

    for(int i = 0; i < 3; ++i){


        for(int j = x; j < y; j+=3) {

            switch(i){
            case 0 : tempArray[counter] = box1[j]; break;
            case 1 : tempArray[counter] = box2[j]; break;
            case 2 : tempArray[counter] = box3[j]; break;
            }
            ++counter;

        }
    }



    for(int i = 0; i < 9; ++i){
        int temp = tempArray[i];
        for(int j = i; j < 9; ++j){
            if(temp == tempArray[j] || tempArray[j] == 0){
                return false;
            }
        }


    }
}
return true;

}

/** Methode checks every Box that numbers 1-9 are unique
 * @brief SudokuMain::checkBox
 * @param box
 * @return
 */
bool SudokuMain::checkBox(int box[]){
    for(int i = 0; i < 9; ++i){
        int temp = box[i];
        for(int j = i; j < 9; ++j){
            if(temp == box[j] || box[j] == 0){
                return false;
            }
        }

}
return true;
}


void SudokuMain::connectToDatabase(){
db = QSqlDatabase::addDatabase("QSQLITE");

db.setDatabaseName(QDir::homePath() + QDir::separator() + "sudokuData");

bool ok = db.open();

if(ok)
{

    map.clear();
    QSqlQuery query (db);

    query.exec("select * from `data`");

    int i = 0;
    while (query.next())
    {

    QString name = query.value(0).toString();
    QString value = query.value(2).toString();

    Valuepair pair = {name.toStdString(),value.toInt()};

    map[i] = pair;

    std::cout << name.toStdString() << std::endl;
    std::cout << getRandom() << std::endl;

    }

 //   std::cout << "last error: " << qPrintable(query.lastError().text()) << std::endl;
    }

}

int SudokuMain::getRandom(){
int  r;

srand(time(0));

r = rand()%10;


return ++r;

}

void SudokuMain::closeConnection(){
    db.commit();
    db.close();
}

