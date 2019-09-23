
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
  setGeometry(200, 200, 1500, 1000);


//setupPlotA(ui->PlotA);



  setupsignalslot();

setWindowTitle(QString("INQNET TDC"));


setupHistoPlot(ui->PlotB);
setupHistoPlot(ui->PlotA);
setupratePlot(ui->PlotTrack);


infLine1 = new QCPItemStraightLine(ui->PlotA);
infLine2 = new QCPItemStraightLine(ui->PlotA);
infLine3 = new QCPItemStraightLine(ui->PlotA);
infLine4 = new QCPItemStraightLine(ui->PlotA);
infLine5 = new QCPItemStraightLine(ui->PlotA);
infLine6 = new QCPItemStraightLine(ui->PlotA);
infLine7 = new QCPItemStraightLine(ui->PlotB);
infLine8 = new QCPItemStraightLine(ui->PlotB);
infLine9 = new QCPItemStraightLine(ui->PlotB);
infLine10 = new QCPItemStraightLine(ui->PlotB);
infLine11 = new QCPItemStraightLine(ui->PlotB);
infLine12 = new QCPItemStraightLine(ui->PlotB);
/*
buttonGroup1 = new QButtonGroup;
buttonGroup1->addButton(ui->trackA1);
buttonGroup1->addButton(ui->trackA2);
buttonGroup1->addButton(ui->trackA3);
buttonGroup1->setExclusive(true);

buttonGroup2 = new QButtonGroup;

*/

for (int i=0;i<6;i++)P_R[i]=0;
for (int i=0;i<6;i++)P_T[i]=false;


ui->histStart->setValue(1);
ui->histEnd->setValue(9000);

ui->binsinplot->setValue(500);
ui->adqtime->setValue(2);

ui->BegA1->setValue(1100);
ui->BegA2->setValue(3100);
ui->BegA3->setValue(5100);
ui->EndA1->setValue(2900);
ui->EndA2->setValue(4900);
ui->EndA3->setValue(6900);

ui->BegB1->setValue(1100);
ui->BegB2->setValue(3100);
ui->BegB3->setValue(5100);
ui->EndB1->setValue(2900);
ui->EndB2->setValue(4900);
ui->EndB3->setValue(6900);

ui->PlotAChn1->setValue(1);
ui->PlotAChn2->setValue(3);
ui->PlotBChn1->setValue(1);
ui->PlotBChn2->setValue(2);
ui->startChan->setValue(1);

//QThread::msleep(100);

adq.start();
anl.start();

adq.initdone = 1;
}


/*
void MainWindow::getImg(QImage* img)   //This code will update the image
 {
 ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
 delete img;
 }*/


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
  graph1->setPen(QPen(QColor(100, 0, 0), 2));

  QCPGraph *graph2 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),4));
  graph2->setPen(QPen(QColor(0, 100, 0), 2));



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
/*
/////////////////////////////////////////////////////////

void MainWindow::setupRatePlot(QCustomPlot *rate){


  rate->plotLayout()->clear();
 
  QCPAxisRect *subLayout = new QCPAxisRect(rate);
  
 
  subLayout->setupFullAxesBox(true);
  subLayout->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  subLayout->axis(QCPAxis::atTop, 0)->setTickLabels(true);

  subLayout->axis(QCPAxis::atRight, 0)->setTickLabelColor(Qt::white);
  subLayout->axis(QCPAxis::atTop, 0)->setTickLabelColor(Qt::white);
  subLayout->axis(QCPAxis::atLeft, 0)->setTickLabelColor(Qt::white);
  subLayout->axis(QCPAxis::atBottom, 0)->setTickLabelColor(Qt::white);

  subLayout->axis(QCPAxis::atRight, 0)->setBasePen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atTop, 0)->setBasePen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atLeft, 0)->setBasePen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atBottom, 0)->setBasePen(QPen(Qt::white, 1));

  subLayout->axis(QCPAxis::atRight, 0)->setTickPen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atTop, 0)->setTickPen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atLeft, 0)->setTickPen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atBottom, 0)->setTickPen(QPen(Qt::white, 1));

  subLayout->axis(QCPAxis::atRight, 0)->setSubTickPen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atTop, 0)->setSubTickPen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atLeft, 0)->setSubTickPen(QPen(Qt::white, 1));
  subLayout->axis(QCPAxis::atBottom, 0)->setSubTickPen(QPen(Qt::white, 1));

  subLayout->axis(QCPAxis::atLeft, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  subLayout->axis(QCPAxis::atBottom, 0)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  subLayout->axis(QCPAxis::atLeft, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  subLayout->axis(QCPAxis::atBottom, 0)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  subLayout->axis(QCPAxis::atLeft, 0)->grid()->setSubGridVisible(true);
  subLayout->axis(QCPAxis::atBottom, 0)->grid()->setSubGridVisible(true);
  subLayout->axis(QCPAxis::atLeft, 0)->grid()->setZeroLinePen(Qt::NoPen);
  subLayout->axis(QCPAxis::atBottom, 0)->grid()->setZeroLinePen(Qt::NoPen);
  subLayout->axis(QCPAxis::atLeft, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);
  subLayout->axis(QCPAxis::atBottom, 0)->setUpperEnding(QCPLineEnding::esSpikeArrow);


  subLayout->axis(QCPAxis::atLeft, 0)->setLabel("Eventos");
  subLayout->axis(QCPAxis::atBottom, 0)->setLabel("Tiempo");


  subLayout->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  subLayout->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);


  subLayout->setRangeZoom(Qt::Vertical);
  
  QCPPlotTitle *title1 = new QCPPlotTitle(rate);
  title1->setText("Nivel de Radiación");
  title1->setFont(QFont("sans", 12, QFont::Bold));
  title1->setTextColor(Qt::white);


  rate->plotLayout()->addElement(0, 0, title1);
  rate->plotLayout()->addElement(1, 0, subLayout); 

  QCPGraph *graph2 = rate->addGraph(subLayout->axis(QCPAxis::atBottom), subLayout->axis(QCPAxis::atLeft));

  graph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),8));
  graph2->setPen(QPen(QColor(100, 100, 100), 2));


  subLayout->axis(QCPAxis::atBottom, 0)->setTickLabelType(QCPAxis::ltDateTime);
  subLayout->axis(QCPAxis::atBottom, 0)->setDateTimeFormat("hh:mm:ss");
  subLayout->axis(QCPAxis::atBottom, 0)->setAutoTickStep(false);
  subLayout->axis(QCPAxis::atBottom, 0)->setTickStep(12);
  subLayout->axis(QCPAxis::atTop, 0)->setTickLabelType(QCPAxis::ltDateTime);
  subLayout->axis(QCPAxis::atTop, 0)->setDateTimeFormat("hh:mm:ss");
  subLayout->axis(QCPAxis::atTop, 0)->setAutoTickStep(false);
  subLayout->axis(QCPAxis::atTop, 0)->setTickStep(12);

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(subLayout->axis(QCPAxis::atBottom, 0), SIGNAL(rangeChanged(QCPRange)), subLayout->axis(QCPAxis::atTop, 0), SLOT(setRange(QCPRange)));
  connect(subLayout->axis(QCPAxis::atLeft, 0), SIGNAL(rangeChanged(QCPRange)), subLayout->axis(QCPAxis::atRight, 0), SLOT(setRange(QCPRange)));
  
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible


  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  rate->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  rate->axisRect()->setBackground(axisRectGradient);



 // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  rate->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


}
////////////////////////////////////////
//////////////////////////////////////////
*/



void MainWindow::setupsignalslot(){

    qRegisterMetaType<vectorInt64>("vectorInt64");
    qRegisterMetaType<vectorInt32>("vectorInt32");
    qRegisterMetaType<channelsTDCPP>("channelsTDCPP");
    qRegisterMetaType<vectorDouble>("vectorDouble");


    QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_startChan(int)));
    QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), &anl, SLOT(clockchange(int)));
    QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), this, SLOT(changeStartchan(int)));

    QObject::connect(ui->adqtime, SIGNAL(valueChanged(double)), this, SLOT(Chang_in_adqtime(double)));
    QObject::connect(ui->adqtime, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_adqtime(double)));
    //deactivated until we unlock the filter feature
    //QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), &adq, SLOT(filterconfigure(int)));

    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), &anl, SLOT(Hist1startChang(int)));
    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), &anl, SLOT(Hist2startChang(int)));
    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_histStart(int)));
    QObject::connect(ui->histStart, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_histStart(int)));

    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), &anl, SLOT(Hist1endChang(int)));
    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), &anl, SLOT(Hist2endChang(int)));
    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_histEnd(int)));
    QObject::connect(ui->histEnd, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_histEnd(int)));

    QObject::connect(ui->binsinplot, SIGNAL(valueChanged(int)), &anl, SLOT(Hist1BinChang(int)));
    QObject::connect(ui->binsinplot, SIGNAL(valueChanged(int)), &anl, SLOT(Hist2BinChang(int)));
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


    QObject::connect(&adq, SIGNAL(dataready(vectorInt64, channelsTDCPP, int)), &anl, SLOT(inputdata(vectorInt64, channelsTDCPP, int)),Qt::QueuedConnection);

//QObject::connect(&anl, SIGNAL(histo1signal(vectorDouble)), this, SLOT(histo1plot(vectorDouble)),Qt::QueuedConnection);

    QObject::connect(&anl, SIGNAL(anlongoing(bool)), &adq, SLOT(adqpausechange(bool)));

    //QObject::connect(&adq, SIGNAL(qutaghist1(vectorInt32)), this, SLOT(histo1plot(vectorInt32)),Qt::QueuedConnection);

    QObject::connect(&adq, SIGNAL(qutaghist(vectorDouble, vectorDouble)), this, SLOT(histoplot(vectorDouble, vectorDouble)),Qt::QueuedConnection);



}


/*
void MainWindow::setupsignalslot(){


qRegisterMetaType<datadqi>("datadqi");
qRegisterMetaType<datadqidouble>("datadqidouble");

_xpedestal=0;
_xcristal=0;

QObject::connect(&adq, SIGNAL(finadqhist(datadqi, int, int)), &anl, SLOT(histoanalisis(datadqi, int, int)),Qt::QueuedConnection);
QObject::connect(&anl, SIGNAL(analisiscompletado(datadqidouble)), this, SLOT(tiemporeal(datadqidouble)),Qt::QueuedConnection);
QObject::connect(&adq, SIGNAL(finpedestal(datadqi, int, int)), &anl, SLOT(anlpedestal(datadqi, int, int)),Qt::QueuedConnection);////cambiar nombre
QObject::connect(&anl, SIGNAL(anlpedestalcompletado(datadqidouble, int, int)), this, SLOT(histopedestal(datadqidouble, int, int)),Qt::QueuedConnection);
QObject::connect(&adq, SIGNAL(fincalibracristal(datadqi, int, int)), &anl, SLOT(anlcalibracristal(datadqi, int, int)),Qt::QueuedConnection);
QObject::connect(&anl, SIGNAL(finanlcristal(datadqidouble, int, int)), this, SLOT(histopedestal(datadqidouble, int, int)),Qt::QueuedConnection);

QObject::connect(&adq, SIGNAL(scope(datadqi)), this, SLOT(scopeplot(datadqi)),Qt::QueuedConnection);
QObject::connect(&adq, SIGNAL(finadqeven(int, double)), this, SLOT(tiemporeal2(int, double)));
QObject::connect(&adq, SIGNAL(error1()), this, SLOT(error1()));

QObject::connect(ui->actionComenzar, SIGNAL(triggered()), &adq, SLOT(tipoadq1()));
QObject::connect(ui->actionPausar, SIGNAL(triggered()), &adq, SLOT(detener()));
QObject::connect(ui->actionContinuar, SIGNAL(triggered()), &adq, SLOT(continuar()));
QObject::connect(ui->actionDetener, SIGNAL(triggered()), &adq, SLOT(stopadq()));
QObject::connect(ui->actionReset, SIGNAL(triggered()), &adq, SLOT(reset()));
QObject::connect(ui->calicali, SIGNAL(pressed()), &adq, SLOT(tipoadq2()));


fotodisponible=true;
QObject::connect(&adq, SIGNAL(adquifoto()), this, SLOT(tfoto()));
QObject::connect(ui->actionFoto, SIGNAL(triggered()), this, SLOT(tfoto()));

QObject::connect(ui->actionPantallazo, SIGNAL(triggered()), this, SLOT(screenShot()));


QObject::connect(&f, SIGNAL(newImgAvailable(QImage*)),this, SLOT(getImg(QImage*)));

ui->eventoscali->setSingleStep(1000);
ui->eventoscali->setMinimum(0);
ui->eventoscali->setMaximum(100000);
ui->eventoscali->setValue(10000);
QObject::connect(ui->eventoscali, SIGNAL(valueChanged(int)), &adq, SLOT(Ceventoscali(int)));


ui->threshold->setSingleStep(0.01);
ui->threshold->setSuffix(" [V]");
ui->threshold->setMinimum(-1.25);
ui->threshold->setMaximum(1.25);
ui->threshold->setValue(-0.02);
QObject::connect(ui->threshold, SIGNAL(valueChanged(double)), &adq, SLOT(Cthreshold1(double)));

ui->histotime->setSingleStep(1);
ui->histotime->setSuffix(" [s]");
ui->histotime->setMinimum(0);
ui->histotime->setMaximum(3600);
ui->histotime->setValue(10);
QObject::connect(ui->histotime, SIGNAL(valueChanged(int)), &adq, SLOT(Ctiempoadq(int)));

_eventosalarma=1000;
ui->eventosalarma->setSingleStep(100);
ui->eventosalarma->setMinimum(0);
ui->eventosalarma->setMaximum(5000);
ui->eventosalarma->setValue(1000);
QObject::connect(ui->eventosalarma, SIGNAL(valueChanged(int)), this, SLOT(Ceventosalarma(int)));
QObject::connect(ui->eventosalarma, SIGNAL(valueChanged(int)), &adq, SLOT(Ceventosfoto(int)));


ui->calibratime->setSingleStep(1);
ui->calibratime->setSuffix(" [min]");
ui->calibratime->setMinimum(0);
ui->calibratime->setMaximum(60);
ui->calibratime->setValue(10);
QObject::connect(ui->calibratime, SIGNAL(valueChanged(int)), &adq, SLOT(Ccristaltime(int)));

    QWidget* popupWidget = new QWidget();
    popupWidget->setWindowFlags(Qt::Popup);

}


*/
//////////////////////////////////////////////////////////
///////////////////rateplot///////////////////////////
///////////////////////////////////////////////////////////

void MainWindow::plotRates(char AoB, int event, double key){

static double lastPointKey = 0;

    double value1 = event; 
   std::cout<<value1<<std::endl;
   if(AoB=='A'){

        ui->PlotTrack->graph(0)->addData(key, value1);
    // remove data of lines that's outside visible range:key, value1
    //ui->PlotTrack->graph(0)->removeDataBefore(key-55);
    // rescale value (vertical) axis to fit the current data:
        ui->PlotTrack->graph(0)->rescaleValueAxis(true);
        lastPointKey = key;
 // make key axis range scroll with the data (at a constant range size of 8):
       // ui->PlotTrack->graph(0)->keyAxis()->setRange(key+0.25, 50, Qt::AlignRight);
        //ui->PlotTrack->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->PlotTrack->replot();
    }
   if(AoB=='B'){


        ui->PlotTrack->graph(1)->addData(key, value1);
    // remove data of lines that's outside visible range:key, value1
    //ui->PlotTrack->graph(0)->removeDataBefore(key-55);
    // rescale value (vertical) axis to fit the current data:
        ui->PlotTrack->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
 // make key axis range scroll with the data (at a constant range size of 8):
      //  ui->PlotTrack->graph(1)->keyAxis()->setRange(key+0.25, 50, Qt::AlignRight);

    }
   ui->PlotTrack->xAxis->setRange(key, 40, Qt::AlignRight);
   ui->PlotTrack->yAxis->rescale();
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
   

}

//////////////////////////////////////////////////////////
///////////////////histograms///////////////////////////
///////////////////////////////////////////////////////////


void MainWindow::histoplot(const vectorDouble &datA, const vectorDouble &datB){

    int binwidth=(int)((in_histEnd-in_histStart)/in_binsinplot);
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

  for (int i=0; i<datA.size(); ++i) {
      if(x[i]>PA_B1 && x[i]<PA_E1)P_R[0]+=datA[i];
      if(x[i]>PA_B2 && x[i]<PA_E2)P_R[1]+=datA[i];
      if(x[i]>PA_B3 && x[i]<PA_E3)P_R[2]+=datA[i];
      if(x[i]>PB_B1 && x[i]<PB_E1)P_R[3]+=datB[i];
      if(x[i]>PB_B2 && x[i]<PB_E2)P_R[4]+=datB[i];
      if(x[i]>PB_B3 && x[i]<PB_E3)P_R[5]+=datB[i];
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

void MainWindow::BegA1(int val){

    this->PA_B1=val;

    infLine1->setPen(QPen(Qt::red));
    infLine1->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine1->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotA->replot();
}
void MainWindow::BegA2(int val){

    this->PA_B2=val;

    infLine2->setPen(QPen(Qt::green));
    infLine2->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine2->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotA->replot();

}
void MainWindow::BegA3(int val){
    this->PA_B3=val;

    infLine3->setPen(QPen(Qt::yellow));
    infLine3->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine3->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotA->replot();
}
void MainWindow::EndA1(int val){
    this->PA_E1=val;

    infLine4->setPen(QPen(Qt::red));
    infLine4->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine4->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotA->replot();
}
void MainWindow::EndA2(int val){
    this->PA_E2=val;

    infLine5->setPen(QPen(Qt::green));
    infLine5->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine5->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotA->replot();
}
void MainWindow::EndA3(int val){
    this->PA_E3=val;

    infLine6->setPen(QPen(Qt::yellow));
    infLine6->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine6->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotA->replot();
}
void MainWindow::BegB1(int val){
    this->PB_B1=val;

    infLine7->setPen(QPen(Qt::red));
    infLine7->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine7->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotB->replot();
}
void MainWindow::BegB2(int val){
    this->PB_B2=val;

    infLine8->setPen(QPen(Qt::green));
    infLine8->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine8->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotB->replot();

}
void MainWindow::BegB3(int val){
    this->PB_B3=val;

    infLine9->setPen(QPen(Qt::yellow));
    infLine9->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine9->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotB->replot();
}
void MainWindow::EndB1(int val){
    this->PB_E1=val;

    infLine10->setPen(QPen(Qt::red));
    infLine10->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine10->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotB->replot();
}
void MainWindow::EndB2(int val){
    this->PB_E2=val;

    infLine11->setPen(QPen(Qt::green));
    infLine11->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine11->point2->setCoords(val, 1);  // location of point 2 in plot coordinate
//this
    ui->PlotB->replot();
}
void MainWindow::EndB3(int val){
    this->PB_E3=val;

    infLine12->setPen(QPen(Qt::yellow));
    infLine12->point1->setCoords(val, 0);  // location of point 1 in plot coordinate
    infLine12->point2->setCoords(val, 1);  // location of point 2 in plot coordinate

    ui->PlotB->replot();
}

/*void MainWindow::Chang_track(bool val){
    if(ui->trackA1->isChecked())PA_T1=true;
        else PA_T1=false;
    if(ui->trackA2->isChecked())PA_T1=true;
    if(ui->trackA3->isChecked())PA_T1=true;
    if(ui->trackB1->isChecked())PA_T1=true;
    if(ui->trackB2->isChecked())PA_T1=true;
    if(ui->trackB3->isChecked())PA_T1=true;

    ui->PlotTrack->graph(0)->data()->clear();
}*/

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


	
       while(adq.isRunning() || anl.isRunning())usleep(100);
       usleep(1000);
       event->accept();


    //else event->ignore();

    
}
/*
void MainWindow::Ceventosalarma(int eventosalarma){

_eventosalarma=eventosalarma;

}
*/
