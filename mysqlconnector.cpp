#include "mysqlconnector.h"
#include "QtGui"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "iostream"

MySQLConnector::MySQLConnector(){

}


void MySQLConnector::connectToDatabase()
{

db = QSqlDatabase::addDatabase("QSQLITE");
db.setHostName("localhost");
db.setPort(3306);
db.setDatabaseName("sudokuData");
db.setUserName("root");
db.setPassword("toor");
bool ok = db.open();

if(ok)
{

    QSqlQuery query ( "select * from `values`");


    while (query.next())
    {

    QString temp = query.value(0).toString();
    std::cout << temp.toStdString() << std::endl;

    }

    std::cout << "last error: " << qPrintable(query.lastError().text()) << std::endl;
    std::cout <<"Connection failed" << qPrintable(db.lastError().text()) << std::endl;
}


}


void MySQLConnector::closeConnection(){
    db.commit();
    db.close();
}
