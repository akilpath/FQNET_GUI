#ifndef ADQCLASS_H
#define ADQCLASS_H 

#include <iostream>
#include <QObject>
#include <QtCore>
#include <unistd.h>
//#include <sys/time.h>
//#include <QMessageBox>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>              /* for exit() */
#include <math.h>
#include "tdcbase.h"
#include "tdcstartstop.h"

typedef QVector<int> datadqi;
typedef QVector<double> datadqidouble;


class qutagadq : public QThread
{
    Q_OBJECT
  

public:


void run();

    //std::cout<<_tipoadq<<std::endl;
      // if(_tipoadq==1)adquisichon();


    explicit qutagadq();
    ~qutagadq();
	


public slots:
    
  void adqui();


signals:
    	void finadqhist(const datadqi &data, int event, int nmuest);
	

private:
    void checkRc( const char * fctname, int rc );
        QVector<int> data;
	QVector<int> datascope;
	bool _stop, _pause;
    int ret, rc;

};

#endif // ADQUICLASS_H
