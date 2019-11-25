#ifndef DBCONTROL_H
#define DBCONTROL_H

#include <QString>
#include <QtSql>

class DBControl
{
public:
    DBControl();
    ~DBControl();
    void disconnectFromServer();
    void DBConnect(QString server, int port, QString database, QString login, QString password);
    void SaveAndValues(int and1, int and2, int and3, float andTime);
private:
    QSqlDatabase db;
    bool connection_succesfull;
    bool connectToServerMySQL(QString server, int port, QString database, QString login, QString password);

};
#endif // DBCONTROL_H
