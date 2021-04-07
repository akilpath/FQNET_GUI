 #ifndef ANALISIS_H
#define ANALISIS_H 


#include <QObject>
#include <QtCore>
#include <adqui.h>
#include <iostream>
#include "TFile.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1F.h"
#include "TF1.h"
#include "TSpectrum.h"



class analisis : public QThread
{
    Q_OBJECT
  

public:


void run()
    {
       //histoanalisis(const datadqi &data, int event, int nmuest);
    }

	explicit analisis();
	~analisis();	
	

public slots:
    

  	void histoanalisis(const datadqi &data, int event, int nmuest);
	void anlpedestal(const datadqi &data, int event, int nmuest);
	void anlcalibracristal(const datadqi &data, int event, int nmuest);

signals:
    	void analisiscompletado(const datadqidouble &dat);
	void anlpedestalcompletado(const datadqidouble &dat, int xset, int a);
	void finanlcristal(const datadqidouble &dat, int xset, int a);

private:


};

#endif // ANALISIS_H
