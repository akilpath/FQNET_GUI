#ifndef ANLCLASS_H
#define ANLCLASS_H

#include <iostream>
#include <QObject>
#include <QtCore>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>              /* for exit() */
#include <math.h>
#include <qutag_adq.h>

class qutaganl : public QThread
{
    Q_OBJECT
  

public:


void run();




    explicit qutaganl();
    ~qutaganl();


	


public slots:
    
  void inputdata(const timetagsPP &TTdata, const channelsTDCPP &CHdata, int nevent);

signals:

	

private:


};

#endif
