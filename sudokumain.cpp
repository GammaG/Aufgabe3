#include "sudokumain.h"
#include "ui_sudokumain.h"
#include "iostream"
#include "QErrorMessage"
#include "QtGui"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "iostream"
#include "QDir"
#include <cstdlib>
#include "map"



SudokuMain::SudokuMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SudokuMain)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(checkValues()));

    connect(ui->actionNeu, SIGNAL(triggered()), this, SLOT(createNewRound()));


}



SudokuMain::~SudokuMain()
{
    delete ui;
}

/** Methode loades new Values for UI and sets them
 * @brief SudokuMain::createNewRound
 */
void SudokuMain::createNewRound(){
    reset();
    connectToDatabase();
    closeConnection();
    setValues();


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



/** Methode konvertiert einen übergebenen Int wert zu einem String und gibt diesen zurück.
 * @brief convertInt
 * @param number
 * @return
 */
std::string SudokuMain::convertInt(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}



void SudokuMain::connectToDatabase(){
db = QSqlDatabase::addDatabase("QSQLITE");

db.setDatabaseName(QDir::homePath() + QDir::separator() + "sudokuData");

bool ok = db.open();

if(ok)
{

    map.clear();
    QSqlQuery query (db);


    std::string temp = "select name, value from data where collection = "+convertInt(getRandom())+";";


    query.exec(QString::fromStdString(temp));

    int i = 0;
    while (query.next())
    {

    QString name = query.value(0).toString();
    QString value = query.value(1).toString();

    Valuepair pair = {name.toStdString(),value.toInt()};

    map[i] = pair;

    i++;
    }


    std::cout << qPrintable(query.lastError().text()) << std::endl;
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

void SudokuMain::setValues(){

    for(int i = 0; i < map.size(); ++i){



        Valuepair pair = map.find(i)->second;


        setField(pair.name, pair.value);
    }



}

void SudokuMain::setField(std::string str, int val){

    if(str=="tl11"){
        ui->tl11->setValue(val);
        ui->tl11->setReadOnly(true);

    }

    else if(str=="tl12"){
        ui->tl12->setValue(val);
        ui->tl12->setReadOnly(true);
    }

    else if(str=="tl13"){
        ui->tl13->setValue(val);
        ui->tl13->setReadOnly(true);
    }


    else if(str=="tl21"){
        ui->tl21->setValue(val);
        ui->tl21->setReadOnly(true);
    }


    else if(str=="tl22"){
        ui->tl22->setValue(val);
        ui->tl22->setReadOnly(true);
    }


    else if(str=="tl23"){
        ui->tl23->setValue(val);
        ui->tl23->setReadOnly(true);
    }


    else if(str=="tl31"){
        ui->tl31->setValue(val);
        ui->tl31->setReadOnly(true);
    }


    else if(str=="tl32"){
        ui->tl32->setValue(val);
        ui->tl32->setReadOnly(true);
    }


    else if(str=="tl33"){
        ui->tl33->setValue(val);
        ui->tl33->setReadOnly(true);
    }


    else if(str=="tm11"){
        ui->tm11->setValue(val);
        ui->tm11->setReadOnly(true);
    }


    else if(str=="tm12"){
        ui->tm12->setValue(val);
        ui->tm12->setReadOnly(true);
    }


    else if(str=="tm13"){
        ui->tm13->setValue(val);
        ui->tm13->setReadOnly(true);
    }


    else if(str=="tm21"){
        ui->tm21->setValue(val);
        ui->tm21->setReadOnly(true);
    }


    else if(str=="tm22"){
        ui->tm22->setValue(val);
        ui->tm22->setReadOnly(true);
    }


    else if(str=="tm23"){
        ui->tm23->setValue(val);
        ui->tm23->setReadOnly(true);
    }


    else if(str=="tm31"){
        ui->tm31->setValue(val);
        ui->tm31->setReadOnly(true);
    }


    else if(str=="tm32"){
        ui->tm32->setValue(val);
        ui->tm32->setReadOnly(true);
    }


    else if(str=="tm33"){
        ui->tm33->setValue(val);
        ui->tm33->setReadOnly(true);
    }

    else if(str=="tr11"){
        ui->tr11->setValue(val);
        ui->tr11->setReadOnly(true);
    }


    else if(str=="tr12"){
        ui->tr12->setValue(val);
        ui->tr12->setReadOnly(true);
    }


    else if(str=="tr13"){
        ui->tr13->setValue(val);
        ui->tr13->setReadOnly(true);
    }


    else if(str=="tr21"){
        ui->tr21->setValue(val);
        ui->tr21->setReadOnly(true);
    }


    else if(str=="tr22"){
        ui->tr22->setValue(val);
        ui->tr22->setReadOnly(true);
    }


    else if(str=="tr23"){
        ui->tr23->setValue(val);
        ui->tr23->setReadOnly(true);
    }


    else if(str=="tr31"){
        ui->tr31->setValue(val);
        ui->tr31->setReadOnly(true);
    }


    else if(str=="tr32"){
        ui->tr32->setValue(val);
        ui->tr32->setReadOnly(true);
    }


    else if(str=="tr33"){
        ui->tr33->setValue(val);
        ui->tr33->setReadOnly(true);
    }


    else if(str=="ml11"){
        ui->ml11->setValue(val);
        ui->ml11->setReadOnly(true);
    }


    else if(str=="ml12"){
        ui->ml12->setValue(val);
        ui->ml12->setReadOnly(true);
    }


    else if(str=="ml13"){
        ui->ml13->setValue(val);
        ui->ml13->setReadOnly(true);
    }


    else if(str=="ml21"){
        ui->ml21->setValue(val);
        ui->ml21->setReadOnly(true);
    }


    else if(str=="ml22"){
        ui->ml22->setValue(val);
        ui->ml22->setReadOnly(true);
    }


    else if(str=="ml23"){
        ui->ml23->setValue(val);
        ui->ml23->setReadOnly(true);
    }


    else if(str=="ml31"){
        ui->ml31->setValue(val);
        ui->ml31->setReadOnly(true);
    }


    else if(str=="ml32"){
        ui->ml32->setValue(val);
        ui->ml32->setReadOnly(true);
    }


    else if(str=="ml33"){
        ui->ml33->setValue(val);
        ui->ml33->setReadOnly(true);
    }


    else if(str=="mm11"){
        ui->mm11->setValue(val);
        ui->mm11->setReadOnly(true);
    }


    else if(str=="mm12"){
        ui->mm12->setValue(val);
        ui->mm12->setReadOnly(true);
    }


    else if(str=="mm13"){
        ui->mm13->setValue(val);
        ui->mm13->setReadOnly(true);
    }


    else if(str=="mm21"){
        ui->mm21->setValue(val);
        ui->mm21->setReadOnly(true);
    }


    else if(str=="mm22"){
        ui->mm22->setValue(val);
        ui->mm22->setReadOnly(true);
    }


    else if(str=="mm23"){
        ui->mm23->setValue(val);
        ui->mm23->setReadOnly(true);
    }


    else if(str=="mm31"){
        ui->mm31->setValue(val);
        ui->mm31->setReadOnly(true);
    }


    else if(str=="mm32"){
        ui->mm32->setValue(val);
        ui->mm32->setReadOnly(true);
    }


    else if(str=="mm33"){
        ui->mm33->setValue(val);
        ui->mm33->setReadOnly(true);
    }


    else if(str=="mr11"){
        ui->mr11->setValue(val);
        ui->mr11->setReadOnly(true);
    }


    else if(str=="mr12"){
        ui->mr12->setValue(val);
        ui->mr12->setReadOnly(true);
    }


    else if(str=="mr13"){
        ui->mr13->setValue(val);
        ui->mr13->setReadOnly(true);
    }


    else if(str=="mr21"){
        ui->mr21->setValue(val);
        ui->mr21->setReadOnly(true);
    }


    else if(str=="mr22"){
        ui->mr22->setValue(val);
        ui->mr22->setReadOnly(true);
    }


    else if(str=="mr23"){
        ui->mr23->setValue(val);
        ui->mr23->setReadOnly(true);
    }


    else if(str=="mr31"){
        ui->mr31->setValue(val);
        ui->mr31->setReadOnly(true);
    }


    else if(str=="mr32"){
        ui->mr32->setValue(val);
        ui->mr32->setReadOnly(true);
    }


    else if(str=="mr33"){
        ui->mr33->setValue(val);
        ui->mr33->setReadOnly(true);
    }


    else if(str=="dl11"){
        ui->dl11->setValue(val);
        ui->dl11->setReadOnly(true);
    }


    else if(str=="dl12"){
        ui->dl12->setValue(val);
        ui->dl12->setReadOnly(true);
    }


    else if(str=="dl13"){
        ui->dl13->setValue(val);
        ui->dl13->setReadOnly(true);
    }


    else if(str=="dl21"){
        ui->dl21->setValue(val);
        ui->dl21->setReadOnly(true);
    }


    else if(str=="dl22"){
        ui->dl22->setValue(val);
        ui->dl22->setReadOnly(true);
    }


    else if(str=="dl23"){
        ui->dl23->setValue(val);
        ui->dl23->setReadOnly(true);
    }


    else if(str=="dl31"){
        ui->dl31->setValue(val);
        ui->dl31->setReadOnly(true);
    }


    else if(str=="dl32"){
        ui->dl32->setValue(val);
        ui->dl32->setReadOnly(true);
    }


    else if(str=="dl33"){
        ui->dl33->setValue(val);
        ui->dl33->setReadOnly(true);
    }


    else if(str=="dm11"){
        ui->dm11->setValue(val);
        ui->dm11->setReadOnly(true);
    }


    else if(str=="dm12"){
        ui->dm12->setValue(val);
        ui->dm12->setReadOnly(true);
    }


    else if(str=="dm13"){
        ui->dm13->setValue(val);
        ui->dm13->setReadOnly(true);
    }


    else if(str=="dm21"){
        ui->dm21->setValue(val);
        ui->dm21->setReadOnly(true);
    }


    else if(str=="dm22"){
        ui->dm22->setValue(val);
        ui->dm22->setReadOnly(true);
    }


    else if(str=="dm23"){
        ui->dm23->setValue(val);
        ui->dm23->setReadOnly(true);
    }


    else if(str=="dm31"){
        ui->dm31->setValue(val);
        ui->dm31->setReadOnly(true);
    }


    else if(str=="dm32"){
        ui->dm32->setValue(val);
        ui->dm32->setReadOnly(true);
    }


    else if(str=="dm33"){
        ui->dm33->setValue(val);
        ui->dm33->setReadOnly(true);
    }


    else if(str=="dr11"){
        ui->dr11->setValue(val);
        ui->dr11->setReadOnly(true);
    }


    else if(str=="dr12"){
        ui->dr12->setValue(val);
        ui->dr12->setReadOnly(true);
    }


    else if(str=="dr13"){
        ui->dr13->setValue(val);
        ui->dr13->setReadOnly(true);
    }


    else if(str=="dr21"){
        ui->dr21->setValue(val);
        ui->dr21->setReadOnly(true);
    }


    else if(str=="dr22"){
        ui->dr22->setValue(val);
        ui->dr22->setReadOnly(true);
    }


    else if(str=="dr23"){
        ui->dr23->setValue(val);
        ui->dr23->setReadOnly(true);
    }


    else if(str=="dr31"){
        ui->dr31->setValue(val);
        ui->dr31->setReadOnly(true);
    }


    else if(str=="dr32"){
        ui->dr32->setValue(val);
        ui->dr32->setReadOnly(true);
    }


    else if(str=="dr33"){
        ui->dr33->setValue(val);
        ui->dr33->setReadOnly(true);
    }
}


/** Methode resets actually values and sets all field to writeable
 * @brief SudokuMain::reset
 */
void SudokuMain::reset(){



    //first Box top left
    ui->tl11->setReadOnly(false);
    ui->tl12->setReadOnly(false);
    ui->tl13->setReadOnly(false);
    ui->tl21->setReadOnly(false);
    ui->tl22->setReadOnly(false);
    ui->tl23->setReadOnly(false);
    ui->tl31->setReadOnly(false);
    ui->tl32->setReadOnly(false);
    ui->tl33->setReadOnly(false);

    //first Box top left
    ui->tl11->setValue(0);
    ui->tl12->setValue(0);
    ui->tl13->setValue(0);
    ui->tl21->setValue(0);
    ui->tl22->setValue(0);
    ui->tl23->setValue(0);
    ui->tl31->setValue(0);
    ui->tl32->setValue(0);
    ui->tl33->setValue(0);


    //second Box top middle
    ui->tm11->setReadOnly(false);
    ui->tm12->setReadOnly(false);
    ui->tm13->setReadOnly(false);
    ui->tm21->setReadOnly(false);
    ui->tm22->setReadOnly(false);
    ui->tm23->setReadOnly(false);
    ui->tm31->setReadOnly(false);
    ui->tm32->setReadOnly(false);
    ui->tm33->setReadOnly(false);


    //second Box top middle
    ui->tm11->setValue(0);
    ui->tm12->setValue(0);
    ui->tm13->setValue(0);
    ui->tm21->setValue(0);
    ui->tm22->setValue(0);
    ui->tm23->setValue(0);
    ui->tm31->setValue(0);
    ui->tm32->setValue(0);
    ui->tm33->setValue(0);


    //third Box top right
    ui->tr11->setReadOnly(false);
    ui->tr12->setReadOnly(false);
    ui->tr13->setReadOnly(false);
    ui->tr21->setReadOnly(false);
    ui->tr22->setReadOnly(false);
    ui->tr23->setReadOnly(false);
    ui->tr31->setReadOnly(false);
    ui->tr32->setReadOnly(false);
    ui->tr33->setReadOnly(false);

    //third Box top right
    ui->tr11->setValue(0);
    ui->tr12->setValue(0);
    ui->tr13->setValue(0);
    ui->tr21->setValue(0);
    ui->tr22->setValue(0);
    ui->tr23->setValue(0);
    ui->tr31->setValue(0);
    ui->tr32->setValue(0);
    ui->tr33->setValue(0);

    //first Box middle left
    ui->ml11->setReadOnly(false);
    ui->ml12->setReadOnly(false);
    ui->ml13->setReadOnly(false);
    ui->ml21->setReadOnly(false);
    ui->ml22->setReadOnly(false);
    ui->ml23->setReadOnly(false);
    ui->ml31->setReadOnly(false);
    ui->ml32->setReadOnly(false);
    ui->ml33->setReadOnly(false);


    //first Box middle left
    ui->ml11->setValue(0);
    ui->ml12->setValue(0);
    ui->ml13->setValue(0);
    ui->ml21->setValue(0);
    ui->ml22->setValue(0);
    ui->ml23->setValue(0);
    ui->ml31->setValue(0);
    ui->ml32->setValue(0);
    ui->ml33->setValue(0);

    //second Box middle middle
    ui->mm11->setReadOnly(false);
    ui->mm12->setReadOnly(false);
    ui->mm13->setReadOnly(false);
    ui->mm21->setReadOnly(false);
    ui->mm22->setReadOnly(false);
    ui->mm23->setReadOnly(false);
    ui->mm31->setReadOnly(false);
    ui->mm32->setReadOnly(false);
    ui->mm33->setReadOnly(false);


    //second Box middle middle
    ui->mm11->setValue(0);
    ui->mm12->setValue(0);
    ui->mm13->setValue(0);
    ui->mm21->setValue(0);
    ui->mm22->setValue(0);
    ui->mm23->setValue(0);
    ui->mm31->setValue(0);
    ui->mm32->setValue(0);
    ui->mm33->setValue(0);

    //third Box middle right
    ui->mr11->setReadOnly(false);
    ui->mr12->setReadOnly(false);
    ui->mr13->setReadOnly(false);
    ui->mr21->setReadOnly(false);
    ui->mr22->setReadOnly(false);
    ui->mr23->setReadOnly(false);
    ui->mr31->setReadOnly(false);
    ui->mr32->setReadOnly(false);
    ui->mr33->setReadOnly(false);

    //third Box middle right
    ui->mr11->setValue(0);
    ui->mr12->setValue(0);
    ui->mr13->setValue(0);
    ui->mr21->setValue(0);
    ui->mr22->setValue(0);
    ui->mr23->setValue(0);
    ui->mr31->setValue(0);
    ui->mr32->setValue(0);
    ui->mr33->setValue(0);

    //first Box down left
    ui->dl11->setReadOnly(false);
    ui->dl12->setReadOnly(false);
    ui->dl13->setReadOnly(false);
    ui->dl21->setReadOnly(false);
    ui->dl22->setReadOnly(false);
    ui->dl23->setReadOnly(false);
    ui->dl31->setReadOnly(false);
    ui->dl32->setReadOnly(false);
    ui->dl33->setReadOnly(false);


    //first Box down left
    ui->dl11->setValue(0);
    ui->dl12->setValue(0);
    ui->dl13->setValue(0);
    ui->dl21->setValue(0);
    ui->dl22->setValue(0);
    ui->dl23->setValue(0);
    ui->dl31->setValue(0);
    ui->dl32->setValue(0);
    ui->dl33->setValue(0);

    //second Box down middle
    ui->dm11->setReadOnly(false);
    ui->dm12->setReadOnly(false);
    ui->dm13->setReadOnly(false);
    ui->dm21->setReadOnly(false);
    ui->dm22->setReadOnly(false);
    ui->dm23->setReadOnly(false);
    ui->dm31->setReadOnly(false);
    ui->dm32->setReadOnly(false);
    ui->dm33->setReadOnly(false);


    //second Box down middle
    ui->dm11->setValue(0);
    ui->dm12->setValue(0);
    ui->dm13->setValue(0);
    ui->dm21->setValue(0);
    ui->dm22->setValue(0);
    ui->dm23->setValue(0);
    ui->dm31->setValue(0);
    ui->dm32->setValue(0);
    ui->dm33->setValue(0);


    //first Box down left
    ui->dr11->setReadOnly(false);
    ui->dr12->setReadOnly(false);
    ui->dr13->setReadOnly(false);
    ui->dr21->setReadOnly(false);
    ui->dr22->setReadOnly(false);
    ui->dr23->setReadOnly(false);
    ui->dr31->setReadOnly(false);
    ui->dr32->setReadOnly(false);
    ui->dr33->setReadOnly(false);


    //first Box down left
    ui->dr11->setValue(0);
    ui->dr12->setValue(0);
    ui->dr13->setValue(0);
    ui->dr21->setValue(0);
    ui->dr22->setValue(0);
    ui->dr23->setValue(0);
    ui->dr31->setValue(0);
    ui->dr32->setValue(0);
    ui->dr33->setValue(0);

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

