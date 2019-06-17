#ifndef ADQCLASS_H
#define ADQCLASS_H 

#include <iostream>
#include <QObject>
#include <QtCore>
#include <unistd.h>
//#include <sys/time.h>
//#include <QMessageBox>


typedef QVector<int> datadqi;
typedef QVector<double> datadqidouble;


class adquiclass : public QThread
{
    Q_OBJECT
  

public:


void run()
    {	
	std::cout<<_tipoadq<<std::endl;
       if(_tipoadq==1)adquisichon();
	
    }

	explicit adquiclass();
	~adquiclass();	
	
	





public slots:
    



signals:
    	void finadqhist(const datadqi &data, int event, int nmuest);
	

private:
	
        QVector<int> data;
	QVector<int> datascope;
	bool _stop, _pause;

};

#endif // ADQUICLASS_H
