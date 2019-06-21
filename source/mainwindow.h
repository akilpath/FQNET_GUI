

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h" 
#include <QtCore>
//#include "qutagADQ.h"
//#include "autagAN.h"
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

  void setupsignalslot();
  /*void setupHistoPlot(QCustomPlot *customPlot);
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
  /*void changeBinres(int binres);

  void changeBinsInPlot(int binsinplot);
  void changeUpdateRate(int updaterate);
  void changePlotCoincidenceA(int ch1,int ch2);
  */
  void plotRates(int event, double key);
  void changeStartchan(int starchan){startChan=starchan;}


private:
  Ui::MainWindow *ui;
  qutagadq adq;
  qutaganl anl;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;
  int currentDemoIndex;
  double prom;

  bool fotodisponible;
  QVector<int> datach1;
  QVector<int> datacali;
  QVector<double> promedio;
  int _xpedestal, _xcristal, _eventosalarma;

  ////first tab//////

  ///general Configs////
  int binres, startChan, binsinplot;
  float updaterate;
  int plotAch1, plotAch2, plotBch1, plotBch2;
  /////first plot////
  int PA_B1,PA_B2, PA_B3, PA_E1, PA_E2, PA_E3;
  bool PA_T1, PA_T2, PA_T3;
  int PA_R1, PA_R2, PA_R3;
  /////second plot////
  int PB_B1,PB_B2, PB_B3, PB_E1, PB_E2, PB_E3;
  bool PB_T1, PB_T2, PB_T3;
  int PB_R1, PB_R2, PB_R3;

  ////SECOND tab////

  int xtime;
  float adqtime_tab2;
  int plot1A, plot1B, plot2A, plot2B, plot3A, plot3B;
  int win1A, win1B, win2A, win2B, win3A, win3B;



signals:
    
};

#endif // MAINWINDOW_H
