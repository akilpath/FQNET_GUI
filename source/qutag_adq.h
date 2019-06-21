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

typedef QVector<Int64> timetagsPP;
typedef QVector<int8_t> channelsTDCPP;

#define TIMESTAMP_COUNT   100000
#define EXP_TIME    1


class qutagadq : public QThread
{
    Q_OBJECT
  

public:


void run();




    explicit qutagadq();
    ~qutagadq();


	


public slots:
    
  void adqui();
  void clockchange(int);


signals:
    void dataready(const timetagsPP &TTdata, const channelsTDCPP &CHdata, int nevent);
	

private:
    void checkRc( const char * fctname, int rc );
    //int foo(int A);
    float rate(int ch_rate);
    int get_max_collection_time( float rate );

    QVector<int64_t> timetags;
    QVector<int8_t> channelsTDC;
	bool _stop, _pause;
    int ret;
    Int32 rc, count, tooSmall, tooBig, tsValid, eventsA, eventsB, i, j, it, ch;
    Int64 expTime, lastTimestamp = 0;
    Int64 timestamps[TIMESTAMP_COUNT];
    Int8  channels[TIMESTAMP_COUNT];
    int   coincCnt[TDC_COINC_CHANNELS];
    double bin2ns = 0, timeBase = 0.;
    double simPara[2] = { 1000., 1000. };
    float TOTAL_RATE;
    int COLLECT_TIME;

};

#endif // ADQUICLASS_H
