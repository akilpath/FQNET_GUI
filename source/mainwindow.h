#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h" 
#include <QtCore>
#include <ctime>
#include <stdio.h>
#include "qutag_adq.h"
#include "qutag_anl.h"
#include "dbcontrol.h"
#include "socket_com.h"

namespace Ui {
class MainWindow;
}





class MainWindow : public QMainWindow
{
  Q_OBJECT

public:


  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void closeEvent(QCloseEvent *event);

  void setupPlotA(QCustomPlot *customPlot);
  void setupratePlot(QCustomPlot *customPlot);
  void setupratePlot_tab2(QCustomPlot *customPlot);

  void setupsignalslot();
  void setupHistoPlot(QCustomPlot *customPlot);

  void setup_histolines_Teleport();
  
  void setupDefaultRanges();
  

private slots:
  
  void plotRates(char AoB, int event, double key);
  void plotRates_tab2(int eventA, int eventB, int eventC,int eventD, int eventE, int eventf, double key);
  void changeStartchan(int starchan){this->in_startChan=starchan;}

  void histoplot(const vectorDouble &dat1, const vectorDouble &dat2, const vectorDouble &dat3);

  void LinePlot();

  void BegA1(int val){Plot_Win_BoE[0][0][0]=val;LinePlot();}
  void BegA2(int val){Plot_Win_BoE[0][1][0]=val;LinePlot();}
  void BegA3(int val){Plot_Win_BoE[0][2][0]=val;LinePlot();}
  void EndA1(int val){Plot_Win_BoE[0][0][1]=val;LinePlot();}
  void EndA2(int val){Plot_Win_BoE[0][1][1]=val;LinePlot();}
  void EndA3(int val){Plot_Win_BoE[0][2][1]=val;LinePlot();}

  void BegB1(int val){Plot_Win_BoE[1][0][0]=val;LinePlot();}
  void BegB2(int val){Plot_Win_BoE[1][1][0]=val;LinePlot();}
  void BegB3(int val){Plot_Win_BoE[1][2][0]=val;LinePlot();}
  void EndB1(int val){Plot_Win_BoE[1][0][1]=val;LinePlot();}
  void EndB2(int val){Plot_Win_BoE[1][1][1]=val;LinePlot();}
  void EndB3(int val){Plot_Win_BoE[1][2][1]=val;LinePlot();}

  void BegC1(int val){Plot_Win_BoE[2][0][0]=val;LinePlot();}
  void BegC2(int val){Plot_Win_BoE[2][1][0]=val;LinePlot();}
  void BegC3(int val){Plot_Win_BoE[2][2][0]=val;LinePlot();}
  void EndC1(int val){Plot_Win_BoE[2][0][1]=val;LinePlot();}
  void EndC2(int val){Plot_Win_BoE[2][1][1]=val;LinePlot();}
  void EndC3(int val){Plot_Win_BoE[2][2][1]=val;LinePlot();}

  void Chang_in_binsinplot(int val){this->in_binsinplot=val;}
  void Chang_in_histStart(int val){this->in_histStart=val;}
  void Chang_in_histEnd(int val){this->in_histEnd=val;}

  void Chang_in_adqtime(double val){this->in_adqtime=val;}

  void Chang_plot1_1(int val){this->tab2_plot[0][0]=val;}
  void Chang_plot1_2(int val){this->tab2_plot[0][1]=val;}
  void Chang_plot2_1(int val){this->tab2_plot[1][0]=val;}
  void Chang_plot2_2(int val){this->tab2_plot[1][1]=val;}
  void Chang_plot3_1(int val){this->tab2_plot[2][0]=val;}
  void Chang_plot3_2(int val){this->tab2_plot[2][1]=val;}
  void Chang_plot4_1(int val){this->tab2_plot[3][0]=val;}
  void Chang_plot4_2(int val){this->tab2_plot[3][1]=val;}
  void Chang_plot5_1(int val){this->tab2_plot[4][0]=val;}
  void Chang_plot5_2(int val){this->tab2_plot[4][1]=val;}

  void Chang_win1_1(int val){this->tab2_win[0][0]=val;}
  void Chang_win1_2(int val){this->tab2_win[0][1]=val;}
  void Chang_win2_1(int val){this->tab2_win[1][0]=val;}
  void Chang_win2_2(int val){this->tab2_win[1][1]=val;}
  void Chang_win3_1(int val){this->tab2_win[2][0]=val;}
  void Chang_win3_2(int val){this->tab2_win[2][1]=val;}
  void Chang_win4_2(int val){this->tab2_win[3][1]=val;}

  void Chang_in_PlotAChn1(int val){this->in_PlotACh1=val;}
  void Chang_in_PlotAChn2(int val){this->in_PlotACh2=val;}
  void Chang_in_PlotBChn1(int val){this->in_PlotBCh1=val;}
  void Chang_in_PlotBChn2(int val){this->in_PlotBCh2=val;}
  void Chang_in_PlotCChn1(int val){this->in_PlotCCh1=val;}
  void Chang_in_PlotCChn2(int val){this->in_PlotCCh2=val;}

  void Chang_track1(bool val){this->P_T[0]=val;trackRateChang =true;}
  void Chang_track2(bool val){this->P_T[1]=val;trackRateChang =true;}
  void Chang_track3(bool val){this->P_T[2]=val;trackRateChang =true;}
  void Chang_track4(bool val){this->P_T[3]=val;trackRateChang =true;}
  void Chang_track5(bool val){this->P_T[4]=val;trackRateChang =true;}
  void Chang_track6(bool val){this->P_T[5]=val;trackRateChang =true;}
  void Chang_track7(bool val){this->P_T[6]=val;trackRateChang =true;}
  void Chang_track8(bool val){this->P_T[7]=val;trackRateChang =true;}
  void Chang_track9(bool val){this->P_T[8]=val;trackRateChang =true;}

  void CombinationChange(bool val){CombiChang =val;}

  void Chang_adqtime_2(double val){in_adqtime_2=val;}

  void turnONDB(int val);

  void SaveState(bool a);
  void LoadState(bool a);

  void tab2_plot1_activate(bool val){in_tab2_plot1=val;}
  void tab2_plot2_activate(bool val){in_tab2_plot2=val;}
  void tab2_plot3_activate(bool val){in_tab2_plot3=val;}
  void tab2_plot4_activate(bool val){in_tab2_plot4=val;}
  void tab2_plot5_activate(bool val){in_tab2_plot5=val;}
  void tab2_plot6_activate(bool val){in_tab2_plot6=val;}

  void setBSMmeas();
  void setHOMmeas();
  void clean_tab2();

  void Chang_delayline(int val){in_delayline=val;}

  void Chang_homscan_time(int val){in_homscan_time=val;}
  void Chang_homscan(int val);

  void chang_tab2range(int val){xrange=val;}


  void resetdelay(){in_delayline=0;prev_homscan=0;}
  void chang_in_max_del(int val){in_Max_delay=val;}

  void chang_in_stepduration(int val){in_stepduration=val;}

  void createQKDLinesA1();
  void createQKDLinesA2();
  void createQKDLinesA3();
  void createQKDLinesB1();
  void createQKDLinesB2();
  void createQKDLinesB3();
  void createQKDLinesC1();
  void createQKDLinesC2();
  void createQKDLinesC3();


private:
  Ui::MainWindow *ui;
  qutagadq adq;
  qutaganl anl;
  DBControl dbc;
  socket_com udpcom;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;
  bool Teleport0_or_QKD1=1
  int currentDemoIndex;
  double prom;
  QButtonGroup *buttonGroup1 ;
  QButtonGroup *buttonGroup2 ;
  bool trackRateChang =false, CombiChang =false;
  float in_adqtime_2;
  QVector<int> datach1;
  QVector<int> datacali;
  bool dbrunning=false;

  QCPItemStraightLine *infLine[18];

  double lastPointKey_tab1;
  double lastPointKey_tab2;

  ////first tab//////
  QMap<QString, int>windows;

  ///general Configs////
  int in_binsinplot, in_startChan, in_histStart, in_histEnd;
  double in_adqtime;
  int in_PlotACh1, in_PlotACh2, in_PlotBCh1, in_PlotBCh2,in_PlotCCh1,in_PlotCCh2;
  /////first plot////
  int P_R[9]={0};
  bool P_T[9]={0};
  int Plot_Win_BoE[3][3][2]={{{0}}};

  ////SECOND tab////


  float adqtime_tab2;
  int tab2_plot[6][2]={{0}};
  int tab2_win[4][2]={{0}};

  bool in_tab2_plot1=false;
  bool in_tab2_plot2=false;
  bool in_tab2_plot3=false;
  bool in_tab2_plot4=false;
  bool in_tab2_plot5=false;
  bool in_tab2_plot6=false;

  int in_delayline=0;

  bool in_homscan=false;
  int in_homscan_time;
  int prev_homscan=0;
  int xrange = 120;
  int in_Max_delay=500;
  bool firstscan=false;
  int in_stepduration;
  double del_key, del_previouskey;

//////QKD///////////////

  QVector<QCPItemStraightLine> LinesPlotA1;
  QVector<QCPItemStraightLine> LinesPlotA2;
  QVector<QCPItemStraightLine> LinesPlotA3;

  QVector<QCPItemStraightLine> LinesPlotB1;
  QVector<QCPItemStraightLine> LinesPlotB2;
  QVector<QCPItemStraightLine> LinesPlotB3;

  QVector<QCPItemStraightLine> LinesPlotC1;
  QVector<QCPItemStraightLine> LinesPlotC2;
  QVector<QCPItemStraightLine> LinesPlotC3;

  int QubitTime, Phasetime, NoQubits, PeaksQubit;

signals:
    void main_SaveAndValues(int and1, int and2, int and3, int orgate, int bsm1, int bsm2, float andTime, int delayline);
    void main_SaveRateValues( int Ra1, int Ra2, int Ra3, int Rb1, int Rb2, int Rb3, int Rc1, int Rc2, int Rc3, float hist_adqtime);

};

#endif // MAINWINDOW_H
