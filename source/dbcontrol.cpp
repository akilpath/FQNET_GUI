#include "dbcontrol.h"
#include <iostream>
#include <time.h>

DBControl::DBControl(){

}

DBControl::~DBControl(){
    if(db.isOpen())db.close();
    std::cout<<"log off from DB"<<std::endl;
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
       QSqlQuery query("create table if not exists inqnet_gui_tab2gates_V2(id int not null auto_increment primary key, and1 int,and2 int, and3 int, orgate int, bsm int, and_adqtime float(7,2), delayline int, datetime datetime);",db);
       QSqlQuery query2("create table if not exists inqnet_gui_historates(id int not null auto_increment primary key, Ra1 int,Ra2 int, Ra3 int, Rb1 int,Rb2 int, Rb3 int, hist_adqtime float(7,2), datetime datetime);",db);
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

void DBControl::SaveAndValues(int and1, int and2, int and3, int orgate, int bsm, float andTime, int delayline){
    QString s= "insert into inqnet_gui_tab2gates_V2(and1,and2, and3, orgate, bsm, and_adqtime, delayline, datetime) values("+QString::number(and1)+","+QString::number(and2)+","+QString::number(and3)+","+QString::number(orgate)+","+QString::number(bsm)+","+QString::number(andTime)+","+QString::number(delayline)+","+"now());";
    std::cout<<s.toStdString()<<std::endl;
    if(connection_succesfull){QSqlQuery query(s,db);
       // std::cout<<"gud"<<std::endl;
    }

}

void DBControl::SaveRateValues( int Ra1, int Ra2, int Ra3, int Rb1, int Rb2, int Rb3,int Rc1 , int Rc2, int Rc3, float hist_adqtime){
    QString s= "insert into inqnet_gui_historates(Ra1, Ra2, Ra3, Rb1, Rb2, Rb3, Rc1, Rc2, Rc3, hist_adqtime, datetime) values("+QString::number(Ra1)+","+QString::number(Ra2)+","+QString::number(Ra3)+QString::number(Rb1)+","+QString::number(Rb2)+","+QString::number(Rb3)+","+QString::number(Rc1)+","+QString::number(Rc2)+","+QString::number(Rc3)+","+QString::number(hist_adqtime)+","+"now());";
   if(connection_succesfull){
       QSqlQuery query(s,db);

   }
}


void DBControl::disconnectFromServer()
{
    db.close();
}


