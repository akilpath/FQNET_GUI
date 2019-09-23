

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

  void setupsignalslot();
  void setupHistoPlot(QCustomPlot *customPlot);
  /*
  void setupRatePlot(QCustomPlot *customPlot);
  void setupCustomCali(QCustomPlot *customcali);
  void setupCustomScope(QCustomPlot *customcali);
  void setupPlayground(QCustomPlot *customPlot);
  */
  
  

private slots:
  //void tiemporeal(const datadqi &datach1, int even, int mues);
  /*void tiemporeal(const datadqidouble &dat);
  void histopedestal(const datadqidouble &dat, int xset, int a);
  void scopeplot(const datadqi &datach1);
*/
  //void inputdata(const vectorInt64 &datahist1);
  void plotRates(char AoB, int event, double key);
  void changeStartchan(int starchan){this->in_startChan=starchan;}

  void histoplot(const vectorDouble &dat1, const vectorDouble &dat2);

  void BegA1(int val);
  void BegA2(int val);
  void BegA3(int val);
  void EndA1(int val);
  void EndA2(int val);
  void EndA3(int val);
  void BegB1(int val);
  void BegB2(int val);
  void BegB3(int val);
  void EndB1(int val);
  void EndB2(int val);
  void EndB3(int val);
  void Chang_in_binsinplot(int val){this->in_binsinplot=val;}
  void Chang_in_histStart(int val){this->in_histStart=val;}
  void Chang_in_histEnd(int val){this->in_histEnd=val;}

  void Chang_in_adqtime(double val){this->in_adqtime=val;}

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

  void Chang_in_PlotAChn1(int val){this->in_PlotACh1=val;}
  void Chang_in_PlotAChn2(int val){this->in_PlotACh2=val;}
  void Chang_in_PlotBChn1(int val){this->in_PlotBCh1=val;}
  void Chang_in_PlotBChn2(int val){this->in_PlotBCh2=val;}

  void Chang_track1(bool val){this->P_T[0]=val;trackRateChang =true;}
  void Chang_track2(bool val){this->P_T[1]=val;trackRateChang =true;}
  void Chang_track3(bool val){this->P_T[2]=val;trackRateChang =true;}
  void Chang_track4(bool val){this->P_T[3]=val;trackRateChang =true;}
  void Chang_track5(bool val){this->P_T[4]=val;trackRateChang =true;}
  void Chang_track6(bool val){this->P_T[5]=val;trackRateChang =true;}

private:
  Ui::MainWindow *ui;
  qutagadq adq;
  qutaganl anl;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;
  int currentDemoIndex;
  double prom;
  QButtonGroup *buttonGroup1 ;
  QButtonGroup *buttonGroup2 ;
  bool trackRateChang =false;

  QVector<int> datach1;
  QVector<int> datacali;

  QCPItemStraightLine *infLine1,*infLine2,*infLine3,*infLine4,*infLine5,*infLine6,*infLine7,*infLine8,*infLine9,*infLine10,*infLine11,*infLine12;


  ////first tab//////

  ///general Configs////
  int in_binsinplot, in_startChan, in_histStart, in_histEnd;
  double in_adqtime;
  int in_PlotACh1, in_PlotACh2, in_PlotBCh1, in_PlotBCh2;
  /////first plot////
  int P_R[6];
  bool P_T[6];
  int PA_B1,PA_B2, PA_B3, PA_E1, PA_E2, PA_E3;
  //bool PA_T1, PA_T2, PA_T3;
  //int PA_R1=0, PA_R2=0, PA_R3=0;
  /////second plot////
  int PB_B1,PB_B2, PB_B3, PB_E1, PB_E2, PB_E3;
  //bool PB_T1, PB_T2, PB_T3;
  //int PB_R1=0, PB_R2=0, PB_R3=0;

  ////SECOND tab////

  int xtime;
  float adqtime_tab2;
  int plot1_1, plot1_2, plot2_1, plot2_2, plot3_1, plot3_2;
  int win1_1, win1_2, win2_1, win2_2, win3_1, win3_2;



signals:
    
};

#endif // MAINWINDOW_H
