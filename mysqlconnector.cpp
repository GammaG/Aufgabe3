#include "mysqlconnector.h"
#include "QtGui"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "iostream"

MySQLConnector::MySQLConnector(){

}


void MySQLConnector::connectToDatabase()
{

QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setHostName("localhost:8080");
db.setDatabaseName("sudokuData");
db.setUserName("root");
db.setPassword("toor");
bool ok = db.open();

if(ok)
{

    QSqlQuery query ( "SELECT `value` FROM `values` WHERE 1");
    while (query.next())
    {

    QString temp = query.value(0).toString();
    std::cout << temp.toStdString() << std::endl;

    }
}


}

