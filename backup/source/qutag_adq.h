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
#include <algorithm>

typedef QVector<Int64> vectorInt64;
typedef QVector<int8_t> channelsTDCPP;
typedef QVector<double> vectorDouble;
typedef QVector<Int32> vectorInt32;

#define TIMESTAMP_COUNT   10000
#define EXP_TIME    1000
#define AVGLENGTH   10
#define DEBUG 0
#define DEBUG2 1
#define DEBUG3 1
#define TAGPCLOCK   5

//#define HIST_BINCOUNT        5000  /* Histogram size */
//#define HIST_BINWIDTH    20  /* Histogram bin width .5us */
#define TIMESTAMP_COUNT   10000  /* Timestamp buffer size */
#define COLLECT_TIME         1000  /* Time [ms] for data acquisition per round */
#define COLLECT_ROUNDS      100


class qutagadq : public QThread
{
    Q_OBJECT
  

public:

void run();

    explicit qutagadq();
    ~qutagadq();
    //void Break();

public slots:
    
  void adqui();
  void setHistograms();

//  void clockchange(int);
  void adqpausechange(bool chang){adqpause_=chang;}
  void Break(){break_= true;}
  //void filterconfigure(int clockchannel);
  int filterset();

  void Chang_in_binsinplot(int val){this->in_binsinplot=val;paramschange=true;}

  void Chang_in_histStart(int val){this->in_histStart=val;paramschange=true;}
  void Chang_in_histEnd(int val){this->in_histEnd=val;paramschange=true;}
  void Chang_in_startChan(int val){this->in_startChan=val;paramschange=true;}

  void Chang_in_adqtime(double val){this->in_adqtime=val;}
  void Chang_in_PlotAChn1(int val){this->in_PlotACh1=val;paramschange=true;}
  void Chang_in_PlotAChn2(int val){this->in_PlotACh2=val;paramschange=true;}
  void Chang_in_PlotBChn1(int val){this->in_PlotBCh1=val;paramschange=true;}
  void Chang_in_PlotBChn2(int val){this->in_PlotBCh2=val;paramschange=true;}




signals:
    void dataready(const vectorInt64 &TTdata, const channelsTDCPP &CHdata, int nevent); // sends to inputdata()
    void qutaghist(const vectorDouble &TTdata1, const vectorDouble &TTdata2);
    //void qutaghist2(const vectorDouble &TTdata);

private:
    bool paramschange = false;
    bool adqpause_;
    bool break_;
    void checkRc( const char * fctname, int rc );
    void getHisto();
    float rate(int ch_rate);
    int get_max_collection_time( float rate );
    int count1, count2;
    int firstChanHist, secondChanHist;
    int ActHist[4][4];
    //QVector<int> ch1[4];QVector<int> ch2[4];QVector<int> ch3[4];QVector<int> ch4[4];

    QVector<int64_t> timetags;
    QVector<int8_t> channelsTDC;
    QVector<int32_t> histo1vector, histo2vector;

    int debug = DEBUG;
    bool _stop;
    int ret;
    Int32 rc, count, tooSmall, tooBig, tsValid, eventsA, eventsB, i, j, it, ch;
    Int64 expTime, lastTimestamp = 0;
    Int64 timestamps[TIMESTAMP_COUNT];
    Int8  channels[TIMESTAMP_COUNT];
    int   coincCnt[TDC_COINC_CHANNELS];
    double bin2ns = 0, timeBase = 0.;
    double simPara[2] = { 1000., 1000. };
    float TOTAL_RATE;
    //int COLLECT_TIME;
    int adqclock;
    int notfirstrun = 0;
    int sleeptime = 10;
    int debug3 = DEBUG3;
    int a = 0;

    int microsec = 10000; // length of time to sleep, in microseconds
    struct timespec req = {0};


    void andrewrun();
    void lautrun();
    int HIST_BINWIDTH;
    int HIST_BINCOUNT;
    int HIST_BINWIDTH_out, HIST_BINCOUNT_out;
    Int32 hist1[5000], hist2[5000];

    Int32 *histodataA;
    Int32 *histodataB;

    int delays[5] = {0,0,0,0,0};
    /////////////////tab 1 variables///////////////
    int in_binsinplot, in_startChan, in_histStart, in_histEnd;
    double in_adqtime;
    int in_PlotACh1, in_PlotACh2, in_PlotBCh1, in_PlotBCh2;


public:
    clock_t begin, end;
    double cpu_time_used;
    bool initdone = 0;

private:

    //nanosleep(&req, (struct timespec *)NULL);
    //static int32 TSValid;

};

#endif // ADQUICLASS_H