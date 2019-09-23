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
       int debug = DEBUG;
       int debug2 = DEBUG2;

       int Hist1Bin, Hist2Bin, Hist1Ch, Hist2Ch;
       ////new
       int Hist1start, Hist2start, Hist1end, Hist2end;
       Int64 sampleclocks[AVGLENGTH];
       Int64 sampletimediffs[AVGLENGTH - 1];
       int arrindex = 0;
       int clockchannel;
       Int64 sum1 = 0;
       Int64 sum2 = 0;
       int i = 0;
       int evt= 0;
       int ch = 0;
       int tg = 0;
       int avgtimediff = 0;
       int anlclock = 0;
       int eventsum = 0;
       Int64 begin = 0;
       Int64 end = 0;
       Int64 prevclock = -1;
       Int64 init_prevclock = -1;
       int newevent = 0;
       int goodevent = 0;
       int clocksum = 0;
       std::array<int, 4> myarray;
       int runcounter = 0;
       int clocknotfound = 0;
       int starttag = 0;
       char clock1[15];
       char clock2[15];
       char clock3[15];
       char clock4[15];
       int totalevents;
       int lengthtoprint;
       Int64 delta;



       std::array<std::array<int,4>,4> my2darray{}; //for testing

       std::vector<std::array<std::array<Int64, TAGPCLOCK>,4 >> events;    //vector(events) of array(channels) of array(tags for each channel)   **basically a 3D datastructure of variable length**


       std::vector< std::pair <Int64,int> > deltavector;

    void run();


    void clear_events();
    void print_event(int EVT, int CLOCK);
    void generate_deltavector(int CHAN, int CLOCK, int TOTALEVENTS);
    void print_deltavector(std::vector< std::pair <Int64,int> > VECTOR, int LENGTHTOPRINT);

    explicit qutaganl();
    ~qutaganl();

    /////histogram Windows////
    int PA_B1,PA_B2, PA_B3, PA_E1, PA_E2, PA_E3;
    int PB_B1,PB_B2, PB_B3, PB_E1, PB_E2, PB_E3;

   //////tab 2 param/////////
    int xtime;
    float adqtime_tab2;
    int plot1_1, plot1_2, plot2_1, plot2_2, plot3_1, plot3_2;
    int win1_1, win1_2, win2_1, win2_2, win3_1, win3_2;

public slots:
    
  void inputdata(const vectorInt64 &TTdata, const channelsTDCPP &CHdata, int nevent);   //receives from dataready() TTdata and CHdata are not initialized in this thread?

  void Hist1BinChang(int val){Hist1Bin = val;}  //Hist1Bin is initialized in mainwindow class
  void Hist2BinChang(int val){Hist2Bin=val;}

  void Hist1ChChange(int val){Hist1Ch=val;}
  void Hist2ChChange(int val){Hist2Ch=val;}


  void Hist1startChang(int val){Hist1start=val;}
  void Hist2startChang(int val){Hist2start=val;}
  void Hist1endChang(int val){Hist1end=val;}
  void Hist2endChang(int val){Hist2end=val;}



  void clockchange(int clockchannel){anlclock = clockchannel;}

  void BegA1(int val){PA_B1=val;}
  void BegA2(int val){PA_B2=val;}
  void BegA3(int val){PA_B3=val;}
  void EndA1(int val){PA_E1=val;}
  void EndA2(int val){PA_E2=val;}
  void EndA3(int val){PA_E3=val;}
  void BegB1(int val){PB_B1=val;}
  void BegB2(int val){PB_B2=val;}
  void BegB3(int val){PB_B3=val;}
  void EndB1(int val){PB_E1=val;}
  void EndB2(int val){PB_E2=val;}
  void EndB3(int val){PB_E3=val;}

  void Chang_plot1_1(int val){this->plot1_1=val;}
  void Chang_plot1_2(int val){this->plot1_2=val;}
  void Chang_plot2_1(int val){this->plot2_1=val;}
  void Chang_plot2_2(int val){this->plot2_2=val;}
  void Chang_plot3_1(int val){this->plot3_1=val;}
  void Chang_plot3_2(int val){this->plot3_2=val;}

  void Chang_win1_1(int val){this->win1_1=val;}
  void Chang_win1_2(int val){this->win1_2=val;}
  void Chang_win2_1(int val){this->win2_1=val;}
  void Chang_win2_2(int val){this->win2_2=val;}
  void Chang_win3_1(int val){this->win3_1=val;}
  void Chang_win3_2(int val){this->win3_2=val;}

signals:

    void histo1signal(const vectorDouble &TTdata);      //histogram 1 data ready
    void anlongoing(bool ong);                          //analysis program still working
private:

  QVector<double> histo1data;

};

#endif
