
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt
#include <vector>//min_element//max_exelement//HD
#include <QApplication>
#include <QtCore>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow){

  ui->setupUi(this);
  setGeometry(200, 200, 1500, 500);


//setupPlotA(ui->PlotA);

//dbc.DBConnect("localhost", 3306, "INQNET_GUI", "GUI", "Teleport1536!");

 setupsignalslot();

setWindowTitle(QString("INQNET TDC"));


setupHistoPlot(ui->PlotB);
setupHistoPlot(ui->PlotA);
setupratePlot(ui->PlotTrack);
setupratePlot_tab2(ui->PlotTab2);

for (int i=0;i<12;i++) {
    if(i<6)infLine[i] = new QCPItemStraightLine(ui->PlotA);
    else infLine[i] = new QCPItemStraightLine(ui->PlotB);
}

ui->thch1->setValue(0.5);
ui->thch2->setValue(-0.08);
ui->thch3->setValue(-0.08);
ui->cw->setValue(50000);

for (int i=0;i<6;i++)P_R[i]=0;
for (int i=0;i<6;i++)P_T[i]=false;

ui->plot1_1->setValue(0);
ui->plot1_2->setValue(0);
ui->win1_1->setValue(0);
ui->win1_2->setValue(0);

ui->histStart->setValue(69000);
ui->histEnd->setValue(77500);
/*ui->histStart->setValue(1000);
ui->histEnd->setValue(10000);*/

ui->binsinplot->setValue(1000);
ui->adqtime->setValue(10);//update rate Adq time


ui->BegA1->setValue(70500);
ui->BegA2->setValue(72700);
ui->BegA3->setValue(74600);
ui->EndA1->setValue(72100);
//ui->EndA1->setValue(39800);
ui->EndA2->setValue(73900);
ui->EndA3->setValue(75900);

ui->BegB1->setValue(71600);
ui->BegB2->setValue(73600);
ui->BegB3->setValue(75600);
ui->EndB1->setValue(72800);
ui->EndB2->setValue(74800);
ui->EndB3->setValue(76800);



ui->PlotAChn1->setValue(1);
ui->PlotAChn2->setValue(3);
ui->PlotBChn1->setValue(1);
ui->PlotBChn2->setValue(2);
ui->startChan->setValue(1);


ui->plot1_1->setValue(0);
ui->plot1_2->setValue(1);
ui->plot2_1->setValue(0);
ui->plot2_2->setValue(1);
ui->plot3_1->setValue(0);
ui->plot3_2->setValue(1);

ui->win1_1->setValue(0);
ui->win1_2->setValue(0);
ui->win2_1->setValue(1);
ui->win2_2->setValue(1);
ui->win3_1->setValue(2);
ui->win3_2->setValue(2);

//QThread::msleep(100);

ui->adqtime_2->setValue(10);


lastPointKey_tab1 = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
lastPointKey_tab2 = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;


dbc.start();
adq.start();
anl.start();



adq.initdone = 1;
}




void MainWindow::setupratePlot(QCustomPlot *scope){


scope->plotLayout()->clear();

QCPAxisRect *wideAxisRect = new QCPAxisRect(scope);


  wideAxisRect->setupFullAxesBox(true);
  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  //wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);

  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabelColor(Qt::white);
  //wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabelColor(Qt::white);

  wideAxisRect->axis(QCPAxis::atRight, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setBasePen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickPen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atRight, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setSubTickPen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setSubGridVisible(true);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setSubGridVisible(true);
  //wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setVisible(false);//
  //wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setVisible(false);//
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setZeroLinePen(Qt::NoPen);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setZeroLinePen(Qt::NoPen);
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);

  //wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabel("Counts");
  //wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabel("Time");

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);

  wideAxisRect->setRangeZoom(Qt::Vertical);


 //scope->plotLayout()->addElement(0, 0, title1);
 scope->plotLayout()->addElement(0, 0, wideAxisRect);

  QCPGraph *graph1 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),4));
  graph1->setPen(QPen(QColor(200, 0, 0), 2));

  QCPGraph *graph2 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),4));
  graph2->setPen(QPen(QColor(0, 200, 0), 2));



  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  scope->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  scope->axisRect()->setBackground(axisRectGradient);


  //scope->yAxis->setRange(0, 2);

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  scope->xAxis->setTicker(timeTicker);
scope->rescaleAxes();
  scope->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::setupratePlot_tab2(QCustomPlot *scope){


scope->plotLayout()->clear();

QCPAxisRect *wideAxisRect = new QCPAxisRect(scope);


  wideAxisRect->setupFullAxesBox(true);
  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  //wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);

  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabelColor(Qt::white);
  //wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabelColor(Qt::white);

  wideAxisRect->axis(QCPAxis::atRight, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setBasePen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickPen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atRight, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setSubTickPen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setSubGridVisible(true);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setSubGridVisible(true);
  //wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setVisible(false);//
  //wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setVisible(false);//
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setZeroLinePen(Qt::NoPen);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setZeroLinePen(Qt::NoPen);
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);

  //wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabel("Counts");
  //wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabel("Time");

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);

  wideAxisRect->setRangeZoom(Qt::Vertical);


 //scope->plotLayout()->addElement(0, 0, title1);
 scope->plotLayout()->addElement(0, 0, wideAxisRect);

  QCPGraph *graph1 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),4));
  graph1->setPen(QPen(QColor(200, 0, 0), 2));

  QCPGraph *graph2 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),4));
  graph2->setPen(QPen(QColor(0, 200, 0), 2));

  QCPGraph *graph3 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),4));
  graph3->setPen(QPen(QColor(200, 200, 0), 2));



  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  scope->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  scope->axisRect()->setBackground(axisRectGradient);

  scope->rescaleAxes();
  //scope->yAxis->setRange(0, 2);

  scope->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}



void MainWindow::setupHistoPlot(QCustomPlot *histograma){

  histograma->plotLayout()->clear();

  QCPAxisRect *wideAxisRect = new QCPAxisRect(histograma);


  wideAxisRect->setupFullAxesBox(true);
  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabels(true);

  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atTop, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickLabelColor(Qt::white);

  wideAxisRect->axis(QCPAxis::atRight, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setBasePen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setBasePen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setTickPen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atRight, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atTop, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setSubTickPen(QPen(Qt::white, 1));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setSubTickPen(QPen(Qt::white, 1));

  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setSubGridVisible(true);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setSubGridVisible(true);
  //wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setVisible(false);//
  //wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setVisible(false);//
  wideAxisRect->axis(QCPAxis::atLeft, 0)->grid()->setZeroLinePen(Qt::NoPen);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->grid()->setZeroLinePen(Qt::NoPen);
  wideAxisRect->axis(QCPAxis::atLeft, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);

  //wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabel("Cuentas");
  //wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabel("Energia");

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);

  wideAxisRect->setRangeZoom(Qt::Horizontal);



  
/*QCPPlotTitle *title1 = new QCPPlotTitle(histograma);
title1->setText("histo");
title1->setFont(QFont("sans", 12, QFont::Bold));
title1->setTextColor(Qt::white);

*/


  //histograma->plotLayout()->addElement(0, 0, title1);
  histograma->plotLayout()->addElement(0, 0, wideAxisRect);


  QCPGraph *graph1 = histograma->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  //QCPGraph *graph2 = histograma->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));

  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),4));
  graph1->setPen(QPen(QColor(100, 100, 100), 2));
  graph1->setLineStyle((QCPGraph::LineStyle)4);

  histograma->xAxis->setRange(0, 10000);

  //histograma->addGraph();
  //histograma->graph(0)->setPen(QPen(Qt::red));

  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  histograma->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  histograma->axisRect()->setBackground(axisRectGradient);



 // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  histograma->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


}


void MainWindow::setupsignalslot(){

    qRegisterMetaType<vectorInt64>("vectorInt64");
    qRegisterMetaType<vectorInt32>("vectorInt32");
    qRegisterMetaType<vectorInt8>("vectorInt8");
    qRegisterMetaType<vectorDouble>("vectorDouble");


    QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_startChan(int)));
    QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_startChan(int)));
    QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), this, SLOT(changeStartchan(int)));

    QObject::connect(ui->adqtime, SIGNAL(valueChanged(double)), this, SLOT(Chang_in_adqtime(double)));
    QObject::connect(ui->adqtime, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_adqtime(double)));



    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_histStart(int)));
    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_histStart(int)));
    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_histStart(int)));


    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_histEnd(int)));
    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_histEnd(int)));
    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_histEnd(int)));

    QObject::connect(ui->binsinplot, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_binsinplot(int)));
    QObject::connect(ui->binsinplot, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_binsinplot(int)));
    QObject::connect(ui->binsinplot, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_binsinplot(int)));

    QObject::connect(ui->PlotAChn1, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_PlotAChn1(int)));
    QObject::connect(ui->PlotAChn2, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_PlotAChn2(int)));
    QObject::connect(ui->PlotBChn1, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_PlotBChn1(int)));
    QObject::connect(ui->PlotBChn2, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_PlotBChn2(int)));

    QObject::connect(ui->PlotAChn1, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotAChn1(int)));
    QObject::connect(ui->PlotAChn2, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotAChn2(int)));
    QObject::connect(ui->PlotBChn1, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotBChn1(int)));
    QObject::connect(ui->PlotBChn2, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotBChn2(int)));

    QObject::connect(ui->PlotAChn1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotAChn1(int)));
    QObject::connect(ui->PlotAChn2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotAChn2(int)));
    QObject::connect(ui->PlotBChn1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotBChn1(int)));
    QObject::connect(ui->PlotBChn2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotBChn2(int)));




    QObject::connect(ui->BegA1, SIGNAL(valueChanged(int)), this, SLOT(BegA1(int)));
    QObject::connect(ui->BegA2, SIGNAL(valueChanged(int)), this, SLOT(BegA2(int)));
    QObject::connect(ui->BegA3, SIGNAL(valueChanged(int)), this, SLOT(BegA3(int)));

    QObject::connect(ui->EndA1, SIGNAL(valueChanged(int)), this, SLOT(EndA1(int)));
    QObject::connect(ui->EndA2, SIGNAL(valueChanged(int)), this, SLOT(EndA2(int)));
    QObject::connect(ui->EndA3, SIGNAL(valueChanged(int)), this, SLOT(EndA3(int)));

    QObject::connect(ui->BegB1, SIGNAL(valueChanged(int)), this, SLOT(BegB1(int)));
    QObject::connect(ui->BegB2, SIGNAL(valueChanged(int)), this, SLOT(BegB2(int)));
    QObject::connect(ui->BegB3, SIGNAL(valueChanged(int)), this, SLOT(BegB3(int)));

    QObject::connect(ui->EndB1, SIGNAL(valueChanged(int)), this, SLOT(EndB1(int)));
    QObject::connect(ui->EndB2, SIGNAL(valueChanged(int)), this, SLOT(EndB2(int)));
    QObject::connect(ui->EndB3, SIGNAL(valueChanged(int)), this, SLOT(EndB3(int)));

    QObject::connect(ui->BegA1, SIGNAL(valueChanged(int)), &anl, SLOT(BegA1(int)));
    QObject::connect(ui->BegA2, SIGNAL(valueChanged(int)), &anl, SLOT(BegA2(int)));
    QObject::connect(ui->BegA3, SIGNAL(valueChanged(int)), &anl, SLOT(BegA3(int)));

    QObject::connect(ui->EndA1, SIGNAL(valueChanged(int)), &anl, SLOT(EndA1(int)));
    QObject::connect(ui->EndA2, SIGNAL(valueChanged(int)), &anl, SLOT(EndA2(int)));
    QObject::connect(ui->EndA3, SIGNAL(valueChanged(int)), &anl, SLOT(EndA3(int)));

    QObject::connect(ui->BegB1, SIGNAL(valueChanged(int)), &anl, SLOT(BegB1(int)));
    QObject::connect(ui->BegB2, SIGNAL(valueChanged(int)), &anl, SLOT(BegB2(int)));
    QObject::connect(ui->BegB3, SIGNAL(valueChanged(int)), &anl, SLOT(BegB3(int)));

    QObject::connect(ui->EndB1, SIGNAL(valueChanged(int)), &anl, SLOT(EndB1(int)));
    QObject::connect(ui->EndB2, SIGNAL(valueChanged(int)), &anl, SLOT(EndB2(int)));
    QObject::connect(ui->EndB3, SIGNAL(valueChanged(int)), &anl, SLOT(EndB3(int)));

    QObject::connect(ui->trackA1, SIGNAL(toggled(bool)), this, SLOT(Chang_track1(bool)));
    QObject::connect(ui->trackA2, SIGNAL(toggled(bool)), this, SLOT(Chang_track2(bool)));
    QObject::connect(ui->trackA3, SIGNAL(toggled(bool)), this, SLOT(Chang_track3(bool)));
    QObject::connect(ui->trackB1, SIGNAL(toggled(bool)), this, SLOT(Chang_track4(bool)));
    QObject::connect(ui->trackB2, SIGNAL(toggled(bool)), this, SLOT(Chang_track5(bool)));
    QObject::connect(ui->trackB3, SIGNAL(toggled(bool)), this, SLOT(Chang_track6(bool)));

    QObject::connect(ui->plot1_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot1_1(int)));
    QObject::connect(ui->plot1_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot1_2(int)));
    QObject::connect(ui->plot2_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot2_1(int)));
    QObject::connect(ui->plot2_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot2_2(int)));
    QObject::connect(ui->plot3_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot3_1(int)));
    QObject::connect(ui->plot3_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot3_2(int)));

    QObject::connect(ui->win1_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win1_1(int)));
    QObject::connect(ui->win1_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win1_2(int)));
    QObject::connect(ui->win2_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win2_1(int)));
    QObject::connect(ui->win2_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win2_2(int)));
    QObject::connect(ui->win3_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win3_1(int)));
    QObject::connect(ui->win3_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win3_2(int)));

    QObject::connect(ui->adqtime_2, SIGNAL(valueChanged(double)), &anl, SLOT(Chang_adqtime_2(double)));
    QObject::connect(ui->adqtime_2, SIGNAL(valueChanged(double)), this, SLOT(Chang_adqtime_2(double)));

    QObject::connect(&anl, SIGNAL(Chang_anlAvilable(bool)), &adq, SLOT(Chang_anlAvilable(bool)));

    QObject::connect(&anl, SIGNAL(CombinationChange(bool)), this, SLOT(CombinationChange(bool)));
   // QObject::connect(&anl, SIGNAL(CombinationChange(bool)), this, SLOT(CombinationChange(bool)));

    QObject::connect(&adq, SIGNAL(dataready(vectorInt64, vectorInt8, int)), &anl, SLOT(timestampANL(vectorInt64, vectorInt8, int)),Qt::QueuedConnection);


    QObject::connect(&anl, SIGNAL(anlongoing(bool)), &adq, SLOT(adqpausechange(bool)));

    QObject::connect(&adq, SIGNAL(qutaghist(vectorDouble, vectorDouble)), this, SLOT(histoplot(vectorDouble, vectorDouble)),Qt::QueuedConnection);
    //QObject::connect(&adq, SIGNAL(qutaghist(vectorDouble, vectorDouble)), this, SLOT(histoplot(vectorDouble, vectorDouble)), Qt::BlockingQueuedConnection);

    QObject::connect(&anl, SIGNAL(rates_tab2(int, int, int, double)), this, SLOT(plotRates_tab2(int, int, int, double)));

    QObject::connect(ui->thch1, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch1(double)));
    QObject::connect(ui->thch2, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch2(double)));
    QObject::connect(ui->thch3, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch3(double)));
    QObject::connect(ui->cw, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_cw(int)));
}



//////////////////////////////////////////////////////////
///////////////////rateplot///////////////////////////
///////////////////////////////////////////////////////////

void MainWindow::plotRates(char AoB, int event, double key){





    double value1 = event; 
  // std::cout<<value1<<std::endl;
   if(AoB=='A'){

        ui->PlotTrack->graph(0)->addData(key-lastPointKey_tab1, value1);
    // remove data of lines that's outside visible range:key, value1
    //ui->PlotTrack->graph(0)->removeDataBefore(key-55);
    // rescale value (vertical) axis to fit the current data:
        ui->PlotTrack->graph(0)->rescaleValueAxis(true);
      //  lastPointKey_tab1 = key;
 // make key axis range scroll with the data (at a constant range size of 8):
       // ui->PlotTrack->graph(0)->keyAxis()->setRange(key+0.25, 50, Qt::AlignRight);
        //ui->PlotTrack->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->PlotTrack->replot();
    }
   if(AoB=='B'){


        ui->PlotTrack->graph(1)->addData(key-lastPointKey_tab1, value1);
    // remove data of lines that's outside visible range:key, value1
    //ui->PlotTrack->graph(0)->removeDataBefore(key-55);
    // rescale value (vertical) axis to fit the current data:
        ui->PlotTrack->graph(1)->rescaleValueAxis(true);

 // make key axis range scroll with the data (at a constant range size of 8):
      //  ui->PlotTrack->graph(1)->keyAxis()->setRange(key+0.25, 50, Qt::AlignRight);

    }
   ui->PlotTrack->xAxis->setRange(key-lastPointKey_tab1, 40, Qt::AlignRight);
   //ui->PlotTrack->yAxis->rescale();
    ui->PlotTrack->replot();

    if(trackRateChang && AoB=='A'){
        ui->PlotTrack->graph(0)->data()->clear();
        trackRateChang=false;
    }
    if(trackRateChang && AoB=='B'){
        ui->PlotTrack->graph(1)->data()->clear();
        trackRateChang=false;
    }
   //prom=0;
   //promedio.prepend(event);
   //for(int i=0; i<promedio.size(); i++)prom=prom+promedio[i];
   //prom=prom/promedio.size();
   //ui->mediamovil->display(prom);
   //if(promedio.size()>50)promedio.resize(50);
    //lastPointKey_tab1 = key;

}

void MainWindow::plotRates_tab2(int eventA, int eventB, int eventC, double key){


   double value1 = eventA;
   double value2 = eventB;
   double value3 = eventC;
   //std::cout<<value1<<std::endl;

        ui->PlotTab2->graph(0)->addData(key-lastPointKey_tab2, value1);
        //ui->PlotTab2->graph(0)->rescaleValueAxis(true);



        ui->PlotTab2->graph(1)->addData(key-lastPointKey_tab2, value2);
        //ui->PlotTab2->graph(1)->rescaleValueAxis(true);



        ui->PlotTab2->graph(2)->addData(key-lastPointKey_tab2, value3);
        //ui->PlotTab2->graph(2)->rescaleValueAxis(true);

    dbc.SaveAndValues(int(value1), int(value2), int(value3), in_adqtime_2);

   ui->PlotTab2->xAxis->setRange(key-lastPointKey_tab2, 120, Qt::AlignRight);
  //ui->PlotTab2->yAxis->rescale();
   ui->PlotTab2->replot();

    if(CombiChang ){
        ui->PlotTab2->graph(0)->data()->clear();
        CombiChang=false;
    }
    if(CombiChang){
        ui->PlotTab2->graph(1)->data()->clear();
        CombiChang=false;
    }
    if(CombiChang){
        ui->PlotTab2->graph(2)->data()->clear();
        CombiChang=false;
    }
//lastPointKey_tab2 = key;



}

//////////////////////////////////////////////////////////
///////////////////histograms///////////////////////////
///////////////////////////////////////////////////////////


void MainWindow::histoplot(const vectorDouble &datA, const vectorDouble &datB){
    //std::cout<<"que pasaaaaaaaaaaaaaaaaaaaaaa histo"<<std::endl;
    double binwidth=((in_histEnd-in_histStart)/in_binsinplot);
   // std::cout<<"histogram size   "<<datA.size()<<std::endl;

    QVector<double> x(datA.size());
//for (int i=in_histStart; i<in_histEnd; i++){
    for (int i=0; i<datA.size(); ++i){
        x[i] = binwidth*i+in_histStart;

    }


  ui->PlotA->graph(0)->data()->clear();
  // pass data points to graphs:
  ui->PlotA->graph(0)->setData(x, datA);
  //let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  ui->PlotA->graph(0)->rescaleAxes();
  ui->PlotA->replot();

  ui->PlotB->graph(0)->data()->clear();
  // pass data points to graphs:
  ui->PlotB->graph(0)->setData(x, datB);
  //let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  ui->PlotB->graph(0)->rescaleAxes();
  ui->PlotB->replot();


  for (int D=0; D<datA.size(); D++) {
      for (int i=0; i<6; i++) {
          if(i<3){if(x[D]>Plot_Win_BoE[0][i][0] && x[D]<Plot_Win_BoE[0][i][1])P_R[i]+=datA[D];}
            else {if(x[D]>Plot_Win_BoE[1][i-3][0] && x[D]<Plot_Win_BoE[1][i-3][1])P_R[i]+=datB[D];}
      }

    }

  ui->countA1->display(P_R[0]);
  ui->countA2->display(P_R[1]);
  ui->countA3->display(P_R[2]);
  ui->countB1->display(P_R[3]);
  ui->countB2->display(P_R[4]);
  ui->countB3->display(P_R[5]);


  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
  for (int i=0;i<6;i++){
      char AoB;
      if(P_T[i]){
          if(i<3)AoB='A';
          else AoB='B';
          plotRates(AoB, P_R[i], key);
      }
  }

  for (int i=0;i<6;i++)P_R[i]=0;
  x.clear();

	
}


void MainWindow::LinePlot(){

   ////int Plot_Win_BoE[2][3][2];

   for (int i=0; i<12; i++) {

        if(i==0 || i==3 || i==6 || i==9)infLine[i]->setPen(QPen(Qt::red));
        if(i==1 || i==4 || i==7 || i==10)infLine[i]->setPen(QPen(Qt::green));
        if(i==2 || i==5 || i==8 || i==11)infLine[i]->setPen(QPen(Qt::yellow));



        if(i<6){

            if(i<3)infLine[i]->point1->setCoords(Plot_Win_BoE[0][i][0], 0);
                else infLine[i]->point1->setCoords(Plot_Win_BoE[0][i-3][1], 0);
            if(i<3)infLine[i]->point2->setCoords(Plot_Win_BoE[0][i][0], 1);
                else infLine[i]->point2->setCoords(Plot_Win_BoE[0][i-3][1], 1);


            ui->PlotA->replot();

        }
        else{
            if(i<9)infLine[i]->point1->setCoords(Plot_Win_BoE[1][i-6][0], 0);
                else infLine[i]->point1->setCoords(Plot_Win_BoE[1][i-6-3][1], 0);
            if(i<9)infLine[i]->point2->setCoords(Plot_Win_BoE[1][i-6][0], 1);
                else infLine[i]->point2->setCoords(Plot_Win_BoE[1][i-6-3][1], 1);

            ui->PlotB->replot();


        }
    }
//std::cout<<"que pasaaaaaaaaaaaaaaaaaaaaaa  line"<<std::endl;

}


MainWindow::~MainWindow()
{
  delete ui;
}

//////////////////////////////////////
////////////popup error///////////////
/////////////////////////////////////
/*void MainWindow::error1(){
	QMessageBox msgBox;
	msgBox.setText("reinicialice/encienda el conversor.");
	msgBox.exec();
}
*/

void MainWindow::closeEvent (QCloseEvent *event)
{
        std::cout<<"going out"<<std::endl;
       adq.Break();
       usleep(100);
       //adq.~qutagadq();
       usleep(100e3);
       std::cout<<"destroy"<<std::endl;
       //adq.quit();
       //anl.quit();


	
       while(adq.isRunning() || anl.isRunning()|| dbc.isRunning())usleep(100);
       usleep(1000);
       event->accept();


    //else event->ignore();

    
}
/*
void MainWindow::Ceventosalarma(int eventosalarma){

_eventosalarma=eventosalarma;

}
*/
