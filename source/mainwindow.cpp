
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

setupPlotA(ui->PlotB);
setupPlotA(ui->PlotA);
setupPlotA(ui->PlotTrack);
//setupPlotA(ui->PlotA);



  setupsignalslot();

setWindowTitle(QString("INQNET TDC"));
/*QPixmap pixmap("/home/cptlab/Desktop/INQNET_GUI/source/logo15.png");
ui->label_8->setPixmap(pixmap);
//ui->label_8->setMask(pixmap.mask());
ui->label_8->show();*/
 
 // statusBar()->clearMessage();

  /*ui->histograma->replot();
  ui->rate->replot();
  ui->customcali->replot();
  ui->scope->replot();


f.start();  

anl.start();

*/
adq.start();
anl.start();

}


/*
void MainWindow::getImg(QImage* img)   //This code will update the image
 {
 ui->imageLabel->setPixmap(QPixmap::fromImage(*img));
 delete img;
 }*/


void MainWindow::setupPlotA(QCustomPlot *scope){


scope->plotLayout()->clear();

QCPAxisRect *wideAxisRect = new QCPAxisRect(scope);


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

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabel("Counts");
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabel("Time");

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);

  wideAxisRect->setRangeZoom(Qt::Horizontal);


  


 //scope->plotLayout()->addElement(0, 0, title1);
 scope->plotLayout()->addElement(0, 0, wideAxisRect);



  QCPGraph *graph1 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));


  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),4));
  graph1->setPen(QPen(QColor(100, 100, 100), 2));




  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  scope->setBackground(plotGradient);
  /*QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  scope->axisRect()->setBackground(axisRectGradient);*/

  scope->rescaleAxes();
  scope->yAxis->setRange(0, 2);
}
/*

/////////////////////////////////////////////////////////
//////////setup histograma pestaña calibracion/////////
/////////////////////////////////////////////////////////


void MainWindow::setupCustomCali(QCustomPlot *customcali){

 customcali->plotLayout()->clear();

QCPAxisRect *wideAxisRect = new QCPAxisRect(customcali);


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

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabel("Cuentas");
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabel("Energia");

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);

  wideAxisRect->setRangeZoom(Qt::Horizontal);


  
	QCPPlotTitle *title1 = new QCPPlotTitle(customcali);
	title1->setText("Histograma de la Radiación");
	title1->setFont(QFont("sans", 12, QFont::Bold));
	title1->setTextColor(Qt::white);

 customcali->plotLayout()->addElement(0, 0, title1);
 customcali->plotLayout()->addElement(1, 0, wideAxisRect); 



  QCPGraph *graph1 = customcali->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));


  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),4));
  graph1->setPen(QPen(QColor(100, 100, 100), 2));




  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  customcali->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  customcali->axisRect()->setBackground(axisRectGradient);



 // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customcali->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


}


*/

/*void MainWindow::setupHistoPlot(QCustomPlot *histograma){



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

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabel("Cuentas");
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabel("Energia");

  wideAxisRect->axis(QCPAxis::atLeft, 0)->setLabelColor(Qt::white);
  wideAxisRect->axis(QCPAxis::atBottom, 0)->setLabelColor(Qt::white);

  wideAxisRect->setRangeZoom(Qt::Horizontal);



  
QCPPlotTitle *title1 = new QCPPlotTitle(histograma);
title1->setText("Histograma de la Radiación");
title1->setFont(QFont("sans", 12, QFont::Bold));
title1->setTextColor(Qt::white);




  histograma->plotLayout()->addElement(0, 0, title1);
  histograma->plotLayout()->addElement(1, 0, wideAxisRect); 


  QCPGraph *graph1 = histograma->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  QCPGraph *graph2 = histograma->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));

  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),4));
  graph1->setPen(QPen(QColor(100, 100, 100), 2));



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

    qRegisterMetaType<timetagsPP>("timetagsPP");
    qRegisterMetaType<channelsTDCPP>("channelsTDCPP");


QObject::connect(ui->startChan, SIGNAL(valueChanged(int)), &adq, SLOT(clockchange(int)));

QObject::connect(&adq, SIGNAL(dataready(timetagsPP, channelsTDCPP, int)), &anl, SLOT(inputdata(timetagsPP, channelsTDCPP, int)),Qt::QueuedConnection);

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

///////////////////////////////////////
////////////grafico osciloscopio////////
//////////////////////////////////////
void MainWindow::scopeplot(const datadqi &datach1)
{

	float aux=0;
	int muestxevent=datach1.size();
	

	QVector<double>volta;

		for(int j=0; j<muestxevent; j++){    
   
			aux=(((1.25*datach1[j])/8192)-1.25);
			volta.push_back(aux);
		}
	
  QVector<double> x;
  
  for (int i=0; i<muestxevent; ++i)x.push_back(i*10);


  ui->scope->graph(0)->clearData();
  // pass data points to graphs:
  ui->scope->graph(0)->setData(x, volta);
  //let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  ui->scope->graph(0)->rescaleAxes();


  ui->scope->replot();

  volta.clear();
  x.clear();
}

////////////////////////////////////////////////
//////////////grafico eventos////////////////////
////////////////////////////////////////////////
*/
void MainWindow::plotRates(int event, double key){

static double lastPointKey = 0;

    double value1 = event; 
    // add data to lines:
    //ui->eventrate->display(event);
   //if(event<_eventosalarma)ui->rate->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white),8));
   //else ui->rate->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),8));

    ui->PlotTrack->graph(0)->addData(key, value1);
    // remove data of lines that's outside visible range:key, value1
    //ui->PlotTrack->graph(0)->removeDataBefore(key-55);
    // rescale value (vertical) axis to fit the current data:
    ui->PlotTrack->graph(0)->rescaleValueAxis(true);
    lastPointKey = key;


  
 // make key axis range scroll with the data (at a constant range size of 8):
   ui->PlotTrack->graph(0)->keyAxis()->setRange(key+0.25, 50, Qt::AlignRight);
   ui->PlotTrack->replot();


   //prom=0;
   //promedio.prepend(event);
   //for(int i=0; i<promedio.size(); i++)prom=prom+promedio[i];
   //prom=prom/promedio.size();
   //ui->mediamovil->display(prom);
   //if(promedio.size()>50)promedio.resize(50);
   

}
/*
//////////////////////////////////////////////////////////
///////////////////histograma///////////////////////////
///////////////////////////////////////////////////////////


void MainWindow::tiemporeal(const datadqidouble &dat)
{



	QVector<double> x(dat.size()); 
	if(_xpedestal==0 && _xcristal==0){
		for (int i=0; i<dat.size(); ++i)x[i] = i;
	}
	else{	double delta=_xcristal-_xpedestal;
		for (int i=0; i<dat.size(); ++i){
			x[i] = (1435/delta)*(i-_xpedestal);
		}
	}

  ui->histograma->graph(0)->clearData();
  // pass data points to graphs:
  ui->histograma->graph(0)->setData(x, dat);
  //let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  ui->histograma->graph(0)->rescaleAxes();


  ui->histograma->replot();


  x.clear();



	
}
*/




MainWindow::~MainWindow()
{
  delete ui;
}

/*void MainWindow::screenShot()
{

  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);

  QString fileName = "pantallazo.png";
  //fileName.replace(" ", "");
  pm.save(fileName);
  //qApp->quit();
}
*/
/*
//////////////////////////////////////
/////////llamado a foto///////////////
/////////////////////////////////////
void MainWindow::tfoto(){
	if(fotodisponible){	
		fotodisponible=false;	
		fotodisponible = f.tomafoto();
		cout<<"."<<endl;
	}
}
*/
/*
//////////////////////////////////////
////////////popup error///////////////
/////////////////////////////////////
void MainWindow::error1(){	
	QMessageBox msgBox;
	msgBox.setText("reinicialice/encienda el conversor.");
	msgBox.exec();
}
*/

void MainWindow::closeEvent (QCloseEvent *event)
{
 
       

	
        event->accept();

    //else event->ignore();

    
}
/*
void MainWindow::Ceventosalarma(int eventosalarma){

_eventosalarma=eventosalarma;

}
*/
