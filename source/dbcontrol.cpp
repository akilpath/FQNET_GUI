#include "dbcontrol.h"
#include <iostream>
#include <time.h>

DBControl::DBControl(){

}

DBControl::~DBControl(){
    if(db.isOpen())db.close();
}

void DBControl::run(){

    this->DBConnect("localhost", 3306, "INQNET_GUI", "GUI2", "Teleport1536!");

}

void DBControl::DBConnect(QString server, int port, QString database, QString login, QString password){
    db = QSqlDatabase();
    db.removeDatabase("example-connection"); // remove old connection if exists
    db = QSqlDatabase::addDatabase("QMYSQL", "example-connection");

    connection_succesfull = connectToServerMySQL(server, port, database, login, password);
    if(connection_succesfull){
        std::cout<<"connection DB success"<<std::endl;
        QStringList tables_names = db.tables();
        for (int i = 0; i < tables_names.size(); ++i)
                 std::cout << tables_names.at(i).toLocal8Bit().constData() << std::endl;
       QSqlQuery query("create table if not exists inqnet_gui_andgates(id int not null auto_increment primary key, and1 int,and2 int, and3 int, and_adqtime float(7,2), datetime datetime);",db);
       usleep(1000);
       //SaveAndValues(1,1,1,1);
    }
    else std::cout<<"connection fail"<<std::cout;

}


bool DBControl::connectToServerMySQL(QString server, int port, QString database,
                                        QString login, QString password)
{
    db.setHostName(server);
    db.setPort(port);
    db.setDatabaseName(database);
    db.setUserName(login);
    db.setPassword(password);

    return db.open();
}

void DBControl::SaveAndValues(int and1, int and2, int and3, float andTime){
    QString s= "insert into inqnet_gui_andgates(and1,and2, and3, and_adqtime, datetime) values("+QString::number(and1)+","+QString::number(and2)+","+QString::number(and3)+","+QString::number(andTime)+","+"now());";
   if(connection_succesfull)QSqlQuery query(s,db);

}


void DBControl::disconnectFromServer()
{
    db.close();
}


