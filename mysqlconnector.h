#ifndef MYSQLCONNECTOR_H
#define MYSQLCONNECTOR_H


#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

class MySQLConnector
{
public:

    QSqlDatabase db;
    MySQLConnector();
    void connectToDatabase();
    void closeConnection();

};

#endif // MYSQLCONNECTOR_H
