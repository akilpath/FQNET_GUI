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
  setGeometry(200, 200, 1500, 800);



//setupPlotA(ui->PlotA);

//dbc.DBConnect("localhost", 3306, "INQNET_GUI", "GUI", "Teleport1536!");

 setupsignalslot();

setWindowTitle(QString("INQNET TDC"));


setupHistoPlot(ui->PlotB);
setupHistoPlot(ui->PlotA);
setupHistoPlot(ui->PlotC);
setupratePlot(ui->PlotTrack);
setupratePlot_tab2(ui->PlotTab2);

for (int i=0;i<18;i++) {
    if(i<6)infLine[i] = new QCPItemStraightLine(ui->PlotA);
    if((i>5) && (i<12)) infLine[i] = new QCPItemStraightLine(ui->PlotB);
    if(i>11)infLine[i] = new QCPItemStraightLine(ui->PlotC);
}

ui->thch1->setValue(0.25);
ui->thch2->setValue(-0.08);
ui->thch3->setValue(-0.08);
ui->thch4->setValue(-0.08);
ui->cw->setValue(50000);

//for (int i=0;i<9;i++)P_R[i]=0;
//for (int i=0;i<9;i++)P_T[i]=false;

ui->plot1_1->setValue(0);
ui->plot1_2->setValue(0);
ui->win1_1->setValue(0);
ui->win1_2->setValue(0);

ui->histStart->setValue(69000);
ui->histEnd->setValue(78500);
/*ui->histStart->setValue(1000);
ui->histEnd->setValue(10000);*/

ui->binsinplot->setValue(1000);
ui->adqtime->setValue(10);//update rate Adq time


ui->BegA1->setValue(70700);
ui->BegA2->setValue(72600);
ui->BegA3->setValue(74600);
ui->EndA1->setValue(72100);
ui->EndA2->setValue(73900);
ui->EndA3->setValue(75900);

ui->BegB1->setValue(71600);
ui->BegB2->setValue(73600);
ui->BegB3->setValue(75600);
ui->EndB1->setValue(72800);
ui->EndB2->setValue(74800);
ui->EndB3->setValue(76800);

ui->BegC1->setValue(71600);
ui->BegC2->setValue(73600);
ui->BegC3->setValue(75600);
ui->EndC1->setValue(72800);
ui->EndC2->setValue(74800);
ui->EndC3->setValue(76800);

ui->PlotAChn1->setValue(1);
ui->PlotAChn2->setValue(3);
ui->PlotBChn1->setValue(1);
ui->PlotBChn2->setValue(2);
ui->PlotCChn1->setValue(1);
ui->PlotCChn2->setValue(4);
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

/*ui->tab2_plot1->setChecked(true);
ui->tab2_plot2->setChecked(true);
ui->tab2_plot3->setChecked(true);
*/

lastPointKey_tab1 = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
lastPointKey_tab2 = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;


ui->rof1->addItem(tr("Rise"));
ui->rof1->addItem(tr("Fall"));
ui->rof1->addItem(tr("hola"));


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

  QCPGraph *graph3 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::blue),4));
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

  QCPGraph *graph4 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),4));
  graph3->setPen(QPen(QColor(252, 175, 62), 2));

  QCPGraph *graph5 = scope->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  graph3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::red),4));
  graph3->setPen(QPen(QColor(173, 127, 168), 2));


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


    //QTimer::singleShot(0, this, SLOT(showFullScreen()));


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
    QObject::connect(ui->PlotCChn1, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_PlotCChn1(int)));
    QObject::connect(ui->PlotCChn2, SIGNAL(valueChanged(int)), this, SLOT(Chang_in_PlotCChn2(int)));

    QObject::connect(ui->PlotAChn1, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotAChn1(int)));
    QObject::connect(ui->PlotAChn2, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotAChn2(int)));
    QObject::connect(ui->PlotBChn1, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotBChn1(int)));
    QObject::connect(ui->PlotBChn2, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotBChn2(int)));
    QObject::connect(ui->PlotCChn1, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotCChn1(int)));
    QObject::connect(ui->PlotCChn2, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_PlotCChn2(int)));

    QObject::connect(ui->PlotAChn1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotAChn1(int)));
    QObject::connect(ui->PlotAChn2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotAChn2(int)));
    QObject::connect(ui->PlotBChn1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotBChn1(int)));
    QObject::connect(ui->PlotBChn2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotBChn2(int)));
    QObject::connect(ui->PlotCChn1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotCChn1(int)));
    QObject::connect(ui->PlotCChn2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_in_PlotCChn2(int)));




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

    QObject::connect(ui->BegC1, SIGNAL(valueChanged(int)), this, SLOT(BegC1(int)));
    QObject::connect(ui->BegC2, SIGNAL(valueChanged(int)), this, SLOT(BegC2(int)));
    QObject::connect(ui->BegC3, SIGNAL(valueChanged(int)), this, SLOT(BegC3(int)));

    QObject::connect(ui->EndC1, SIGNAL(valueChanged(int)), this, SLOT(EndC1(int)));
    QObject::connect(ui->EndC2, SIGNAL(valueChanged(int)), this, SLOT(EndC2(int)));
    QObject::connect(ui->EndC3, SIGNAL(valueChanged(int)), this, SLOT(EndC3(int)));

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

    QObject::connect(ui->BegC1, SIGNAL(valueChanged(int)), &anl, SLOT(BegC1(int)));
    QObject::connect(ui->BegC2, SIGNAL(valueChanged(int)), &anl, SLOT(BegC2(int)));
    QObject::connect(ui->BegC3, SIGNAL(valueChanged(int)), &anl, SLOT(BegC3(int)));

    QObject::connect(ui->EndC1, SIGNAL(valueChanged(int)), &anl, SLOT(EndC1(int)));
    QObject::connect(ui->EndC2, SIGNAL(valueChanged(int)), &anl, SLOT(EndC2(int)));
    QObject::connect(ui->EndC3, SIGNAL(valueChanged(int)), &anl, SLOT(EndC3(int)));

    QObject::connect(ui->trackA1, SIGNAL(toggled(bool)), this, SLOT(Chang_track1(bool)));
    QObject::connect(ui->trackA2, SIGNAL(toggled(bool)), this, SLOT(Chang_track2(bool)));
    QObject::connect(ui->trackA3, SIGNAL(toggled(bool)), this, SLOT(Chang_track3(bool)));
    QObject::connect(ui->trackB1, SIGNAL(toggled(bool)), this, SLOT(Chang_track4(bool)));
    QObject::connect(ui->trackB2, SIGNAL(toggled(bool)), this, SLOT(Chang_track5(bool)));
    QObject::connect(ui->trackB3, SIGNAL(toggled(bool)), this, SLOT(Chang_track6(bool)));
    QObject::connect(ui->trackC1, SIGNAL(toggled(bool)), this, SLOT(Chang_track7(bool)));
    QObject::connect(ui->trackC2, SIGNAL(toggled(bool)), this, SLOT(Chang_track8(bool)));
    QObject::connect(ui->trackC3, SIGNAL(toggled(bool)), this, SLOT(Chang_track9(bool)));

    QObject::connect(ui->plot1_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot1_1(int)));
    QObject::connect(ui->plot1_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot1_2(int)));
    QObject::connect(ui->plot2_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot2_1(int)));
    QObject::connect(ui->plot2_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot2_2(int)));
    QObject::connect(ui->plot3_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot3_1(int)));
    QObject::connect(ui->plot3_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot3_2(int)));
    QObject::connect(ui->plot4_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot4_1(int)));
    QObject::connect(ui->plot4_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot4_2(int)));
    QObject::connect(ui->plot5_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_plot5_2(int)));

    QObject::connect(ui->win1_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win1_1(int)));
    QObject::connect(ui->win1_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win1_2(int)));
    QObject::connect(ui->win2_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win2_1(int)));
    QObject::connect(ui->win2_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win2_2(int)));
    QObject::connect(ui->win3_1, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win3_1(int)));
    QObject::connect(ui->win3_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win3_2(int)));
    QObject::connect(ui->win5_2, SIGNAL(valueChanged(int)), &anl, SLOT(Chang_win5_2(int)));

    QObject::connect(ui->adqtime_2, SIGNAL(valueChanged(double)), &anl, SLOT(Chang_adqtime_2(double)));
    QObject::connect(ui->adqtime_2, SIGNAL(valueChanged(double)), this, SLOT(Chang_adqtime_2(double)));

    QObject::connect(&anl, SIGNAL(Chang_anlAvilable(bool)), &adq, SLOT(Chang_anlAvilable(bool)));

    QObject::connect(&anl, SIGNAL(CombinationChange(bool)), this, SLOT(CombinationChange(bool)));
   // QObject::connect(&anl, SIGNAL(CombinationChange(bool)), this, SLOT(CombinationChange(bool)));

    QObject::connect(&adq, SIGNAL(dataready(vectorInt64, vectorInt8, int)), &anl, SLOT(timestampANL(vectorInt64, vectorInt8, int)),Qt::QueuedConnection);


    QObject::connect(&anl, SIGNAL(anlongoing(bool)), &adq, SLOT(adqpausechange(bool)));

    QObject::connect(&adq, SIGNAL(qutaghist(vectorDouble, vectorDouble, vectorDouble)), this, SLOT(histoplot(vectorDouble, vectorDouble, vectorDouble)),Qt::QueuedConnection);
    //QObject::connect(&adq, SIGNAL(qutaghist(vectorDouble, vectorDouble)), this, SLOT(histoplot(vectorDouble, vectorDouble)), Qt::BlockingQueuedConnection);

    QObject::connect(&anl, SIGNAL(rates_tab2(int, int, int, int, int, double)), this, SLOT(plotRates_tab2(int, int, int, int, int, double)));

    QObject::connect(ui->thch1, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch1(double)));
    QObject::connect(ui->thch2, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch2(double)));
    QObject::connect(ui->thch3, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch3(double)));
    QObject::connect(ui->thch4, SIGNAL(valueChanged(double)), &adq, SLOT(Chang_in_thch4(double)));
    QObject::connect(ui->cw, SIGNAL(valueChanged(int)), &adq, SLOT(Chang_in_cw(int)));

    QObject::connect(ui->DBON, SIGNAL(valueChanged(int)), this, SLOT(turnONDB(int)));

    QObject::connect(ui->actionSave_state, SIGNAL(triggered(bool)), this, SLOT(SaveState(bool)));
    QObject::connect(ui->actionLoad_state, SIGNAL(triggered(bool)), this, SLOT(LoadState(bool)));

    QObject::connect(ui->tab2_plot1, SIGNAL(toggled(bool)), this, SLOT(tab2_plot1_activate(bool)));
    QObject::connect(ui->tab2_plot2, SIGNAL(toggled(bool)), this, SLOT(tab2_plot2_activate(bool)));
    QObject::connect(ui->tab2_plot3, SIGNAL(toggled(bool)), this, SLOT(tab2_plot3_activate(bool)));
    QObject::connect(ui->tab2_plot4, SIGNAL(toggled(bool)), this, SLOT(tab2_plot4_activate(bool)));
    QObject::connect(ui->tab2_plot5, SIGNAL(toggled(bool)), this, SLOT(tab2_plot5_activate(bool)));

    QObject::connect(ui->BSM, SIGNAL(released()), this, SLOT(setBSMmeas()));
    QObject::connect(ui->HOM, SIGNAL(released()), this, SLOT(setHOMmeas()));

    QObject::connect(ui->delayline, SIGNAL(valueChanged(int)), this, SLOT(Chang_delayline(int)));

    QObject::connect(this, SIGNAL(main_SaveAndValues(int, int, int , int , int, float , int )), &dbc, SLOT(SaveAndValues(int, int, int , int , int, float , int )));

    QObject::connect(this, SIGNAL(main_SaveRateValues( int, int , int , int , int , int , int , int , int , float)), &dbc, SLOT(SaveRateValues( int, int , int , int , int , int , int , int , int , float)));

    QObject::connect(ui->homscan_time, SIGNAL(valueChanged(int)), this, SLOT(Chang_homscan_time(int)));
    QObject::connect(ui->homscan, SIGNAL(toggled(bool)), this, SLOT(Chang_homscan(bool)));
}



//////////////////////////////////////////////////////////
///////////////////plotting///////////////////////////
///////////////////////////////////////////////////////////

void MainWindow::plotRates(char AoBoC, int event, double key){


    double value1 = event; 

   if(AoBoC=='A'){

        ui->PlotTrack->graph(0)->addData(key-lastPointKey_tab1, value1);
    // remove data of lines that's outside visible range:key, value1
    //ui->PlotTrack->graph(0)->removeDataBefore(key-55);
    // rescale value (vertical) axis to fit the current data:
        //ui->PlotTrack->graph(0)->rescaleValueAxis(true);
      //  lastPointKey_tab1 = key;
 // make key axis range scroll with the data (at a constant range size of 8):
       // ui->PlotTrack->graph(0)->keyAxis()->setRange(key+0.25, 50, Qt::AlignRight);
        //ui->PlotTrack->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->PlotTrack->replot();
    }
   if(AoBoC=='B'){


        ui->PlotTrack->graph(1)->addData(key-lastPointKey_tab1, value1);


    }
   if(AoBoC=='C'){
    //std::cout<<"que pasaaaaaaaaaaaaaaaaaaaaaa  line          "<<value1<<std::endl;

        ui->PlotTrack->graph(2)->addData(key-lastPointKey_tab1, value1);

    }

    ui->PlotTrack->xAxis->setRange(key-lastPointKey_tab1, 120, Qt::AlignRight);
   //ui->PlotTrack->yAxis->rescale();

    ui->PlotTrack->replot();

    if(trackRateChang && AoBoC=='A'){
        ui->PlotTrack->graph(0)->data()->clear();
        trackRateChang=false;
    }
    if(trackRateChang && AoBoC=='B'){
        ui->PlotTrack->graph(1)->data()->clear();
        trackRateChang=false;
    }
    if(trackRateChang && AoBoC=='C'){
        ui->PlotTrack->graph(2)->data()->clear();
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

void MainWindow::plotRates_tab2(int eventA, int eventB, int eventC, int orgate , int bsm, double key){


   double value1 = eventA;
   double value2 = eventB;
   double value3 = eventC;
   double value4 = orgate;
   double value5 = bsm;
   //std::cout<<value1<<std::endl;

        if(in_tab2_plot1)ui->PlotTab2->graph(0)->addData(key-lastPointKey_tab2, value1);
        //ui->PlotTab2->graph(0)->rescaleValueAxis(true);

        if(in_tab2_plot2)ui->PlotTab2->graph(1)->addData(key-lastPointKey_tab2, value2);
        //ui->PlotTab2->graph(1)->rescaleValueAxis(true);

        if(in_tab2_plot3)ui->PlotTab2->graph(2)->addData(key-lastPointKey_tab2, value3);
        //ui->PlotTab2->graph(2)->rescaleValueAxis(true);

        if(in_tab2_plot4)ui->PlotTab2->graph(3)->addData(key-lastPointKey_tab2, value4);
        //ui->PlotTab2->graph(2)->rescaleValueAxis(true);

        if(in_tab2_plot5)ui->PlotTab2->graph(4)->addData(key-lastPointKey_tab2, value5);
        //ui->PlotTab2->graph(2)->rescaleValueAxis(true);

    if(dbrunning && !in_homscan)emit main_SaveAndValues(eventA, eventB, eventC, orgate , bsm , in_adqtime_2, in_delayline);
    if(dbrunning && in_homscan){
        emit main_SaveAndValues(eventA, eventB, eventC, orgate , bsm , in_adqtime_2, prev_homscan);
        prev_homscan=in_delayline+in_homscan_time;
    }

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


void MainWindow::histoplot(const vectorDouble &datA, const vectorDouble &datB, const vectorDouble &datC){
    //std::cout<<" histoplot hermanitititototot"<< datB.size()<<"   "<<datC.size() <<std::endl;
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

  ui->PlotC->graph(0)->data()->clear();
  // pass data points to graphs:
  ui->PlotC->graph(0)->setData(x, datC);
  //let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  ui->PlotC->graph(0)->rescaleAxes();
  ui->PlotC->replot();



  for (int D=0; D<datA.size(); D++) {
      for (int i=0; i<9; i++) {
          if(i<3){
              if(x[D]>Plot_Win_BoE[0][i][0] && x[D]<Plot_Win_BoE[0][i][1])P_R[i]+=datA[D];
          }
          if(i>2 && i<6) {
              if(x[D]>Plot_Win_BoE[1][i-3][0] && x[D]<Plot_Win_BoE[1][i-3][1])P_R[i]+=datB[D];
          }
          if(i>5) {
              if(x[D]>Plot_Win_BoE[2][i-6][0] && x[D]<Plot_Win_BoE[2][i-6][1])P_R[i]+=datC[D];
          }

       }

  }

  ui->countA1->display(P_R[0]);
  ui->countA2->display(P_R[1]);
  ui->countA3->display(P_R[2]);
  ui->countB1->display(P_R[3]);
  ui->countB2->display(P_R[4]);
  ui->countB3->display(P_R[5]);
  ui->countC1->display(P_R[6]);
  ui->countC2->display(P_R[7]);
  ui->countC3->display(P_R[8]);

  //std::cout<<P_R[7]<<std::endl;

  if(dbrunning)emit main_SaveRateValues(P_R[0], P_R[1],  P_R[2], P_R[3], P_R[4], P_R[5], P_R[6], P_R[7], P_R[8], float(in_adqtime));
//std::cout<<P_R[7]<<std::endl;
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
  for (int i=0;i<9;i++){
      char AoBoC = char(NULL);
      if(P_T[i]){
          if(i<3)AoBoC='A';
          if(i>2 && i<6) AoBoC='B';
          if(i>5) AoBoC='C';
          //std::cout<<AoBoC<<"    "<<P_R[i]<<"    "<<i<<std::endl;

          plotRates(AoBoC, P_R[i], key);
      }
  }

  for (int i=0;i<9;i++)P_R[i]=0;
  x.clear();

	
}


void MainWindow::LinePlot(){

   ////int Plot_Win_BoE[2][3][2];

   for (int i=0; i<18; i++) {

        if(i==0 || i==3 || i==6 || i==9 || i==12 || i==15)infLine[i]->setPen(QPen(Qt::red));
        if(i==1 || i==4 || i==7 || i==10 || i==13 || i==16)infLine[i]->setPen(QPen(Qt::green));
       if(i==2 || i==5 || i==8 || i==11  || i==14 || i==17)infLine[i]->setPen(QPen(Qt::yellow));



        if(i<6){

            if(i<3)infLine[i]->point1->setCoords(Plot_Win_BoE[0][i][0], 0);
                else infLine[i]->point1->setCoords(Plot_Win_BoE[0][i-3][1], 0);
            if(i<3)infLine[i]->point2->setCoords(Plot_Win_BoE[0][i][0], 1);
                else infLine[i]->point2->setCoords(Plot_Win_BoE[0][i-3][1], 1);


            ui->PlotA->replot();

        }
        if(i>5 && i<12){
            if(i<9)infLine[i]->point1->setCoords(Plot_Win_BoE[1][i-6][0], 0);
                else infLine[i]->point1->setCoords(Plot_Win_BoE[1][i-6-3][1], 0);
            if(i<9)infLine[i]->point2->setCoords(Plot_Win_BoE[1][i-6][0], 1);
                else infLine[i]->point2->setCoords(Plot_Win_BoE[1][i-6-3][1], 1);

            ui->PlotB->replot();


        }
        if(i>11){
            if(i<15)infLine[i]->point1->setCoords(Plot_Win_BoE[2][i-12][0], 0);
                else infLine[i]->point1->setCoords(Plot_Win_BoE[2][i-12-3][1], 0);
            if(i<15)infLine[i]->point2->setCoords(Plot_Win_BoE[2][i-12][0], 1);
                else infLine[i]->point2->setCoords(Plot_Win_BoE[2][i-12-3][1], 1);

            ui->PlotC->replot();

        }
    }
//std::cout<<"que pasaaaaaaaaaaaaaaaaaaaaaa  line"<<std::endl;

   /*for (int i=0;i<3;i++) {
       for (int j ;j<3;j++) {
           for (int k;k<2;k++) {
           }
       }
   }*/
}


void MainWindow::turnONDB(int val){
    /*if(!dbc.isRunning() && dbrunning == 0 && val==1){
        dbc.run();
        dbrunning=val;
    }
    if(dbc.isRunning() && dbrunning == 1 && val==0){
        dbrunning = val;
        while(dbc.isRunning())usleep(100);
        dbc.~DBControl();
    }*/
    dbrunning=val;
}


void MainWindow::SaveState(bool a){
//std::cout<<"debug"<<std::cout;
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Current Configuration"), "",
            tr("Configuration (*.conf);;All Files (*)"));

   //QString fileName = "test";
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            QDataStream out(&file);

                    out.setVersion(QDataStream::Qt_4_5);
                    QMap<QString, int> mapint;
                    QMap<QString, double> mapdouble;
                    QString localstring;


                    for ( int i=0;i<3;i++) {
                           for (int j =0;j<3;j++) {
                               for (int k = 0;k<2;k++) {
                                   localstring = QString("Plot_Win_BoE[%1][%2][%3]").arg(i).arg(j).arg(k);
                                   //std::cout<< localstring.toStdString()<< std::endl;
                                    if(!mapint.contains(localstring))mapint.insert(localstring,Plot_Win_BoE[i][j][k]);
                                    else mapint.value(localstring, Plot_Win_BoE[i][j][k]);
                               }

                           }

                     }

                    for ( int i=0;i<3;i++) {
                           for (int j =0;j<2;j++) {
                                   localstring = QString("tab2_plot[%1][%2]").arg(i).arg(j);
                                   //std::cout<< localstring.toStdString()<< std::endl;
                                    if(!mapint.contains(localstring))mapint.insert(localstring,tab2_plot[i][j]);
                                    else mapint.value(localstring, tab2_plot[i][j]);
                               }
                     }

                    for ( int i=0;i<3;i++) {
                           for (int j =0;j<2;j++) {
                                   localstring = QString("tab2_win[%1][%2]").arg(i).arg(j);
                                   //std::cout<< localstring.toStdString()<< std::endl;
                                    if(!mapint.contains(localstring))mapint.insert(localstring,tab2_win[i][j]);
                                    else mapint.value(localstring, tab2_win[i][j]);
                               }
                     }

                    mapint.insert("in_startChan",in_startChan);
                    mapint.insert("in_PlotACh1",in_PlotACh1);
                    mapint.insert("in_PlotACh2",in_PlotACh2);
                    mapint.insert("in_PlotBCh1",in_PlotBCh1);
                    mapint.insert("in_PlotBCh2",in_PlotBCh2);
                    mapint.insert("in_PlotCCh1",in_PlotCCh1);
                    mapint.insert("in_PlotCCh2",in_PlotCCh2);
                    mapint.insert("in_histStart",in_histStart);
                    mapint.insert("in_histEnd",in_histEnd);
                    mapint.insert("in_binsinplot",in_binsinplot);

                    mapdouble.insert("in_adqtime", in_adqtime);
                    mapdouble.insert("adqtime_tab2", double(adqtime_tab2));

                    /*QMapIterator<QString,int>ip(mapint);
                    while (ip.hasNext()) {
                        ip.next();
                        std::cout<< ip.key().toStdString()<< ": " << ip.value() << std::endl;
                    }*/
                    out<<mapint;
                    out<<mapdouble;
            }

   // LoadState(1);
}



void MainWindow::LoadState(bool a){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Configuration"), "",
            tr("Configuration (*.conf);;All Files (*)"));
    //QString fileName = "test";
    if (fileName.isEmpty())
            return;
        else {

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
            QMap<QString, int> mapintout;
            QMap<QString, double> mapdoubleout;
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_5);
            in>>mapintout;

            /*QString localstring;
            for ( int i=0;i<3;i++) {
                   for (int j =0;j<3;j++) {
                       for (int k = 0;k<2;k++) {
                           localstring = QString("Plot_Win_BoE[%1][%2][%3]").arg(i).arg(j).arg(k);
                            if(mapintout.contains(localstring))Plot_Win_BoE[i][j][k]= mapintout.value(localstring);
                       }
                   }
             }*/
            if(mapintout.contains("tab2_plot[0][0]"))ui->plot1_1->setValue(mapintout.value("tab2_plot[0][0]"));
            if(mapintout.contains("tab2_plot[0][1]"))ui->plot1_2->setValue(mapintout.value("tab2_plot[0][1]"));
            if(mapintout.contains("tab2_plot[1][0]"))ui->plot2_1->setValue(mapintout.value("tab2_plot[1][0]"));
            if(mapintout.contains("tab2_plot[1][1]"))ui->plot2_2->setValue(mapintout.value("tab2_plot[1][1]"));
            if(mapintout.contains("tab2_plot[2][0]"))ui->plot3_1->setValue(mapintout.value("tab2_plot[2][0]"));
            if(mapintout.contains("tab2_plot[2][1]"))ui->plot3_2->setValue(mapintout.value("tab2_plot[2][1]"));

            if(mapintout.contains("tab2_win[0][0]"))ui->win1_1->setValue(mapintout.value("tab2_win[0][0]"));
            if(mapintout.contains("tab2_win[0][1]"))ui->win1_2->setValue(mapintout.value("tab2_win[0][1]"));
            if(mapintout.contains("tab2_win[1][0]"))ui->win2_1->setValue(mapintout.value("tab2_win[1][0]"));
            if(mapintout.contains("tab2_win[1][1]"))ui->win2_2->setValue(mapintout.value("tab2_win[1][1]"));
            if(mapintout.contains("tab2_win[2][0]"))ui->win3_1->setValue(mapintout.value("tab2_win[2][0]"));
            if(mapintout.contains("tab2_win[2][1]"))ui->win3_2->setValue(mapintout.value("tab2_win[2][1]"));



            if(mapintout.contains("Plot_Win_BoE[0][0][0]"))ui->BegA1->setValue(mapintout.value("Plot_Win_BoE[0][0][0]"));
            if(mapintout.contains("Plot_Win_BoE[0][1][0]"))ui->BegA2->setValue(mapintout.value("Plot_Win_BoE[0][1][0]"));
            if(mapintout.contains("Plot_Win_BoE[0][2][0]"))ui->BegA3->setValue(mapintout.value("Plot_Win_BoE[0][2][0]"));
            if(mapintout.contains("Plot_Win_BoE[0][0][1]"))ui->EndA1->setValue(mapintout.value("Plot_Win_BoE[0][0][1]"));
            if(mapintout.contains("Plot_Win_BoE[0][1][1]"))ui->EndA2->setValue(mapintout.value("Plot_Win_BoE[0][1][1]"));
            if(mapintout.contains("Plot_Win_BoE[0][2][1]"))ui->EndA3->setValue(mapintout.value("Plot_Win_BoE[0][2][1]"));

            if(mapintout.contains("Plot_Win_BoE[1][0][0]"))ui->BegB1->setValue(mapintout.value("Plot_Win_BoE[1][0][0]"));
            if(mapintout.contains("Plot_Win_BoE[1][1][0]"))ui->BegB2->setValue(mapintout.value("Plot_Win_BoE[1][1][0]"));
            if(mapintout.contains("Plot_Win_BoE[1][2][0]"))ui->BegB3->setValue(mapintout.value("Plot_Win_BoE[1][2][0]"));
            if(mapintout.contains("Plot_Win_BoE[1][0][1]"))ui->EndB1->setValue(mapintout.value("Plot_Win_BoE[1][0][1]"));
            if(mapintout.contains("Plot_Win_BoE[1][1][1]"))ui->EndB2->setValue(mapintout.value("Plot_Win_BoE[1][1][1]"));
            if(mapintout.contains("Plot_Win_BoE[1][2][1]"))ui->EndB3->setValue(mapintout.value("Plot_Win_BoE[1][2][1]"));

            if(mapintout.contains("Plot_Win_BoE[2][0][0]"))ui->BegC1->setValue(mapintout.value("Plot_Win_BoE[2][0][0]"));
            if(mapintout.contains("Plot_Win_BoE[2][1][0]"))ui->BegC2->setValue(mapintout.value("Plot_Win_BoE[2][1][0]"));
            if(mapintout.contains("Plot_Win_BoE[2][2][0]"))ui->BegC3->setValue(mapintout.value("Plot_Win_BoE[2][2][0]"));
            if(mapintout.contains("Plot_Win_BoE[2][0][1]"))ui->EndC1->setValue(mapintout.value("Plot_Win_BoE[2][0][1]"));
            if(mapintout.contains("Plot_Win_BoE[2][1][1]"))ui->EndC2->setValue(mapintout.value("Plot_Win_BoE[2][1][1]"));
            if(mapintout.contains("Plot_Win_BoE[2][2][1]"))ui->EndC3->setValue(mapintout.value("Plot_Win_BoE[2][2][1]"));


            if(mapintout.contains("in_startChan"))ui->startChan->setValue(mapintout.value("in_startChan"));
            if(mapintout.contains("in_PlotACh1"))ui->PlotAChn1->setValue(mapintout.value("in_PlotACh1"));
            if(mapintout.contains("in_PlotACh2"))ui->PlotAChn2->setValue(mapintout.value("in_PlotACh2"));
            if(mapintout.contains("in_PlotBCh1"))ui->PlotBChn1->setValue(mapintout.value("in_PlotBCh1"));
            if(mapintout.contains("in_PlotBCh2"))ui->PlotBChn2->setValue(mapintout.value("in_PlotBCh2"));
            if(mapintout.contains("in_PlotCCh1"))ui->PlotCChn1->setValue(mapintout.value("in_PlotCCh1"));
            if(mapintout.contains("in_PlotCCh2"))ui->PlotCChn2->setValue(mapintout.value("in_PlotCCh2"));
            if(mapintout.contains("in_histStart"))ui->histStart->setValue(mapintout.value("in_histStart"));
            if(mapintout.contains("in_histEnd"))ui->histEnd->setValue(mapintout.value("in_histEnd"));
            if(mapintout.contains("in_binsinplot"))ui->binsinplot->setValue(mapintout.value("in_binsinplot"));

            if(mapdoubleout.contains("in_adqtime"))ui->adqtime->setValue(mapdoubleout.value("in_adqtime"));
            if(mapdoubleout.contains("adqtime_tab2"))ui->adqtime_2->setValue(mapdoubleout.value("adqtime_tab2"));



               QMapIterator<QString,int>i(mapintout);
               while (i.hasNext()) {
                   i.next();
                   std::cout<< i.key().toStdString() <<  ": " << i.value() << std::endl;
               }
               in>>mapdoubleout;
               QMapIterator<QString,double>j(mapdoubleout);
               while (j.hasNext()) {
                   j.next();
                   std::cout<< j.key().toStdString() <<  ": " << j.value() << std::endl;
               }

    }

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setBSMmeas(){
    ui->tab2_plot1->setChecked(true);
    ui->tab2_plot2->setChecked(true);
    ui->tab2_plot3->setChecked(false);
    ui->tab2_plot4->setChecked(true);
    ui->tab2_plot5->setChecked(true);

    ui->plot1_1->setValue(0);
    ui->plot1_2->setValue(1);
    ui->plot2_1->setValue(0);
    ui->plot2_2->setValue(1);
    //ui->plot3_1->setValue(0);
    //ui->plot3_2->setValue(1);
    ui->plot4_1->setValue(0);
    ui->plot4_2->setValue(1);
    ui->plot5_2->setValue(3);

    ui->win1_1->setValue(0);
    ui->win1_2->setValue(2);
    ui->win2_1->setValue(2);
    ui->win2_2->setValue(0);
    ui->win5_2->setValue(0);
    //ui->win3_2->setValue(2);

}
void MainWindow::setHOMmeas(){


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
