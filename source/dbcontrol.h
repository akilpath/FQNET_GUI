#ifndef DBCONTROL_H
#define DBCONTROL_H

#include <QString>
#include <QtSql>
#include <QObject>
#include <QtCore>

class DBControl : public QThread
{
    Q_OBJECT

public:
    void run();
    explicit DBControl();
    ~DBControl();
    void disconnectFromServer();
    void DBConnect(QString server, int port, QString database, QString login, QString password);
    void SaveAndValues(int and1, int and2, int and3, float andTime);
    void SaveRateValues( int Ra1, int Ra2, int Ra3, int Rb1, int Rb2, int Rb3, int Rc1, int Rc2, int Rc3, float hist_adqtime);
private:
    QSqlDatabase db;
    bool connection_succesfull;
    bool connectToServerMySQL(QString server, int port, QString database, QString login, QString password);

signals:

public slots:

};
#endif // DBCONTROL_H
