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






      /* std::array<std::array<int,4>,4> my2darray{}; //for testing

       std::vector<std::array<std::array<Int64, TAGPCLOCK>,4 >> events;    //vector(events) of array(channels) of array(tags for each channel)   **basically a 3D datastructure of variable length**


       std::vector< std::pair <Int64,int> > deltavector;*/

    void run();


    void clear_events();
    //void print_event(int EVT, int CLOCK);
    //void generate_deltavector(int CHAN, int CLOCK, int TOTALEVENTS);
    //void print_deltavector(std::vector< std::pair <Int64,int> > VECTOR, int LENGTHTOPRINT);

    explicit qutaganl();
    void updateConditions();
    ~qutaganl();

    /////histogram Windows////
    int Plot_Win_BoE[3][3][2]= {{{0}}};

    ////first plot////
    int in_binsinplot, in_startChan, in_histStart, in_histEnd;
    double in_adqtime;
    int in_PlotACh1, in_PlotACh2, in_PlotBCh1, in_PlotBCh2, in_PlotCCh1, in_PlotCCh2;





   //////tab 2 param/////////
    int xtime;
    float adqtime_tab2;
    int tab2_plot[6][2]={{0}};
    int tab2_win[6][2]= {{0}};

   // int counterplot1=0, counterplot2=0, counterplot3=0;
    int tab2_ranges[6][2][2] = {{{0}}};

public slots:
    
  void timestampANL(const vectorInt64 &vectorTimetags, const vectorInt8 &vectorChannels, int tsvalid);


  void Chang_in_startChan(int starchan){this->in_startChan=starchan;updateConditions();}
  void Chang_in_PlotAChn1(int val){this->in_PlotACh1=val;updateConditions();}
  void Chang_in_PlotAChn2(int val){this->in_PlotACh2=val;updateConditions();}
  void Chang_in_PlotBChn1(int val){this->in_PlotBCh1=val;updateConditions();}
  void Chang_in_PlotBChn2(int val){this->in_PlotBCh2=val;updateConditions();}
  void Chang_in_PlotCChn1(int val){this->in_PlotCCh1=val;updateConditions();}
  void Chang_in_PlotCChn2(int val){this->in_PlotCCh2=val;updateConditions();}

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

  void BegC1(int val){Plot_Win_BoE[2][0][0]=val;updateConditions();}
  void BegC2(int val){Plot_Win_BoE[2][1][0]=val;updateConditions();}
  void BegC3(int val){Plot_Win_BoE[2][2][0]=val;updateConditions();}
  void EndC1(int val){Plot_Win_BoE[2][0][1]=val;updateConditions();}
  void EndC2(int val){Plot_Win_BoE[2][1][1]=val;updateConditions();}
  void EndC3(int val){Plot_Win_BoE[2][2][1]=val;updateConditions();}


  void Chang_plot1_1(int val){this->tab2_plot[0][0]=val;updateConditions();}
  void Chang_plot1_2(int val){this->tab2_plot[0][1]=val;updateConditions();}
  void Chang_plot2_1(int val){this->tab2_plot[1][0]=val;updateConditions();}
  void Chang_plot2_2(int val){this->tab2_plot[1][1]=val;updateConditions();}
  void Chang_plot3_1(int val){this->tab2_plot[2][0]=val;updateConditions();}
  void Chang_plot3_2(int val){this->tab2_plot[2][1]=val;updateConditions();}
  void Chang_plot4_1(int val){this->tab2_plot[3][0]=val;updateConditions();}
  void Chang_plot4_2(int val){this->tab2_plot[3][1]=val;updateConditions();}
  void Chang_plot5_2(int val){this->tab2_plot[4][1]=val;updateConditions();}
  void Chang_plot6_2(int val){this->tab2_plot[5][1]=val;updateConditions();}

  void Chang_win1_1(int val){this->tab2_win[0][0]=val;updateConditions();}
  void Chang_win1_2(int val){this->tab2_win[0][1]=val;updateConditions();}
  void Chang_win2_1(int val){this->tab2_win[1][0]=val;updateConditions();}
  void Chang_win2_2(int val){this->tab2_win[1][1]=val;updateConditions();}
  void Chang_win3_1(int val){this->tab2_win[2][0]=val;updateConditions();}
  void Chang_win3_2(int val){this->tab2_win[2][1]=val;updateConditions();}
  void Chang_win5_2(int val){this->tab2_win[4][1]=val;updateConditions();}
  void Chang_win6_2(int val){this->tab2_win[5][1]=val;updateConditions();}

  void Chang_adqtime_2(double val){this->adqtime_2=val;updateConditions();}

signals:

    void histo1signal(const vectorDouble &TTdata);      //histogram 1 data ready
    void anlongoing(bool ong);                          //analysis program still working
    void Chang_anlAvilable(bool val);
    void CombinationChange(bool val);
    void rates_tab2(int, int, int, int, int ,int ,double);

private:

  QVector<double> histo1data;
  std::ofstream file;
  double diffh;
  int ChannelIndex=0, StopIndex=0, counterplot[6]={0};
  int flag[6][2]= {{0}};
  double adqtime_2=0;
  double previouskey;
  double key;
  bool anlbusy =false;
  bool borrame =false;double firstkey;

};

#endif
