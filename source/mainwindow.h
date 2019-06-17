

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
  /*void setupHistoPlot(QCustomPlot *customPlot);
  void setupRatePlot(QCustomPlot *customPlot);
  void setupCustomCali(QCustomPlot *customcali);
  void setupCustomScope(QCustomPlot *customcali);
  void setupPlayground(QCustomPlot *customPlot);
  void setupsignalslot();*/
  
  

private slots:
  //void tiemporeal(const datadqi &datach1, int even, int mues);
  /*void tiemporeal(const datadqidouble &dat);
  void histopedestal(const datadqidouble &dat, int xset, int a);
  void scopeplot(const datadqi &datach1);
  void tiemporeal2(int event, double key);
  void screenShot();
  void tfoto();
  void error1();
  void getImg(QImage*);
  void Ceventosalarma(int eventosalarma);*/


private:
  Ui::MainWindow *ui;
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
signals:
    
};

#endif // MAINWINDOW_H
