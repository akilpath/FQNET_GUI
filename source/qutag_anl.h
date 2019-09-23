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
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt



class qutaganl : public QThread
{
    Q_OBJECT
  

public:
       int debug = DEBUG;
       int debug2 = DEBUG2;
       bool anlAvilable = false;
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
    void updateConditions();
    ~qutaganl();

    /////histogram Windows////
    int Plot_Win_BoE[2][3][2]= {{{0}}};

    ////first plot////
    int in_binsinplot, in_startChan, in_histStart, in_histEnd;
    double in_adqtime;
    int in_PlotACh1, in_PlotACh2, in_PlotBCh1, in_PlotBCh2;





   //////tab 2 param/////////
    int xtime;
    float adqtime_tab2;
    int tab2_plot[3][2]={{0}};
    int tab2_win[3][2]= {{0}};

    int counterplot1=0, counterplot2=0, counterplot3=0;
    int tab2_ranges[3][2][2] = {{{0}}};

public slots:
    
  void timestampANL(const vectorInt64 &vectorTimetags, const vectorInt8 &vectorChannels, int tsvalid);


  void Chang_in_startChan(int starchan){this->in_startChan=starchan;updateConditions();}
  void Chang_in_PlotAChn1(int val){this->in_PlotACh1=val;updateConditions();}
  void Chang_in_PlotAChn2(int val){this->in_PlotACh2=val;updateConditions();}
  void Chang_in_PlotBChn1(int val){this->in_PlotBCh1=val;updateConditions();}
  void Chang_in_PlotBChn2(int val){this->in_PlotBCh2=val;updateConditions();}

  void Chang_in_binsinplot(int val){this->in_binsinplot=val;updateConditions();}
  void Chang_in_histStart(int val){this->in_histStart=val;updateConditions();}
  void Chang_in_histEnd(int val){this->in_histEnd=val;updateConditions();}

  //void clockchange(int clockchannel){anlclock = clockchannel;}

  void BegA1(int val){Plot_Win_BoE[0][0][0]=val;updateConditions();}
  void BegA2(int val){Plot_Win_BoE[0][1][0]=val;updateConditions();}
  void BegA3(int val){Plot_Win_BoE[0][2][0]=val;updateConditions();}
  void EndA1(int val){Plot_Win_BoE[0][0][1]=val;updateConditions();}
  void EndA2(int val){Plot_Win_BoE[0][1][1]=val;updateConditions();}
  void EndA3(int val){Plot_Win_BoE[0][2][1]=val;updateConditions();}

  void BegB1(int val){Plot_Win_BoE[1][0][0]=val;updateConditions();}
  void BegB2(int val){Plot_Win_BoE[1][1][0]=val;updateConditions();}
  void BegB3(int val){Plot_Win_BoE[1][2][0]=val;updateConditions();}
  void EndB1(int val){Plot_Win_BoE[1][0][1]=val;updateConditions();}
  void EndB2(int val){Plot_Win_BoE[1][1][1]=val;updateConditions();}
  void EndB3(int val){Plot_Win_BoE[1][2][1]=val;updateConditions();}


  void Chang_plot1_1(int val){this->tab2_plot[0][0]=val;updateConditions();}
  void Chang_plot1_2(int val){this->tab2_plot[0][1]=val;updateConditions();}
  void Chang_plot2_1(int val){this->tab2_plot[1][0]=val;updateConditions();}
  void Chang_plot2_2(int val){this->tab2_plot[1][1]=val;updateConditions();}
  void Chang_plot3_1(int val){this->tab2_plot[2][0]=val;updateConditions();}
  void Chang_plot3_2(int val){this->tab2_plot[2][1]=val;updateConditions();}

  void Chang_win1_1(int val){this->tab2_win[0][0]=val;updateConditions();}
  void Chang_win1_2(int val){this->tab2_win[0][1]=val;updateConditions();}
  void Chang_win2_1(int val){this->tab2_win[1][0]=val;updateConditions();}
  void Chang_win2_2(int val){this->tab2_win[1][1]=val;updateConditions();}
  void Chang_win3_1(int val){this->tab2_win[2][0]=val;updateConditions();}
  void Chang_win3_2(int val){this->tab2_win[2][1]=val;updateConditions();}

  void Chang_adqtime_2(float val){this->adqtime_2=val;updateConditions();}

signals:

    void histo1signal(const vectorDouble &TTdata);      //histogram 1 data ready
    void anlongoing(bool ong);                          //analysis program still working
    void Chang_anlAvilable(bool val);
private:

  QVector<double> histo1data;
  std::ofstream file;
  double diffh;
  int ChannelIndex=0, j, StopIndex=0, counterplot[3]={0,0,0}, flag[2]= {0,0};
  float adqtime_2=0;

};

#endif
