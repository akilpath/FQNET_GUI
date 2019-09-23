#include "analisis.h"

analisis::analisis(){

}

analisis::~analisis(){

}

void analisis::histoanalisis(const datadqi &datach1, int totaleventos, int totalmuestras){


FILE *asdf;
asdf = fopen("histogramdata.txt","w");

using namespace std;





  int Hmin = 0;
  int Hmax = 0;
  int nbins= 0;

 
	int aux=0;//integrador

 
cout << "totalmuestras:" << totalmuestras << endl;
	
cout  << "totaleventos:"<< totaleventos << endl;



	int muestxevent;
	if(totaleventos!=0){muestxevent=(totalmuestras+1)/totaleventos;cout<< "muestxevent:"  << muestxevent << endl;}
	else muestxevent=0;


///////////integrar los datos del canal 1////////////////

  	vector<float>HD;//Histogram data (salida del integrador)

	for(int i=0; i<totaleventos; i++){
		for(int j=0; j<muestxevent; j++){       
			
			aux=aux+datach1[j+muestxevent*i];
		}
				
		HD.push_back(aux);fprintf(asdf,"%d\n", aux);aux=0;
	}

	//cout<<"tamaño HD:"<<HD.size()<<endl;
	//for (int i=0; i<totaleventos; ++i)cout<<HD[i]<<endl;

        if(HD.size()!=0){
    	//Hmin = *min_element(HD.begin(), HD.end());;cout << "Hmin:" << Hmin << endl;
    	//Hmax = *max_element(HD.begin(), HD.end());;cout << "Hmax:" << Hmax << endl;
	Hmin=208000;
	Hmax=222000;
	nbins= Hmax-Hmin;cout << "nbins:" << nbins << endl<<endl;
	}
	else nbins=1;
	
	QVector<double>dat1(nbins);dat1[0]=0;
	for(int i=1; i<nbins; i++){
		for(int j=0; j<totaleventos; j++){
			if( (i+Hmin)==HD[j]  )dat1[i]++;
			
		}
	}


	QVector<double>dat(nbins);
	for(int i=0; i<nbins; i++)dat[i]=dat1[nbins-i];


	dat1.clear();



  emit analisiscompletado(dat);

  HD.clear();
  dat.clear();


} 

void analisis::anlpedestal(const datadqi &datacali, int totaleventos, int totalmuestras){



using namespace std;



  int Hmin = 0;
  int Hmax = 0;
  int nbins= 0;

 
	int aux=0;//integrador

 
cout << "totalmuestras:" << totalmuestras << endl;
	
cout  << "totaleventos:"<< totaleventos << endl;



	int muestxevent;
	if(totaleventos!=0){muestxevent=(totalmuestras+1)/totaleventos;cout<< "muestxevent:"  << muestxevent << endl;}
	else muestxevent=0;


  	vector<float>HD;//Histogram data (salida del integrador)

	for(int i=0; i<totaleventos; i++){
		for(int j=0; j<muestxevent; j++){       
			
			aux=aux+datacali[j+muestxevent*i];
		}
				
		HD.push_back(aux);aux=0;
	}

	//cout<<"tamaño HD:"<<HD.size()<<endl;
	//for (int i=0; i<totaleventos; ++i)cout<<HD[i]<<endl;

        if(HD.size()!=0){
    	//Hmin = *min_element(HD.begin(), HD.end());;cout << "Hmin:" << Hmin << endl;
    	//Hmax = *max_element(HD.begin(), HD.end());;cout << "Hmax:" << Hmax << endl;
	Hmin=208000;
	Hmax=222000;	
	nbins= Hmax-Hmin;;cout << "nbins:" << nbins << endl<<endl;
	}
	else nbins=1;


	QVector<double>dat1(nbins);
	for(int i=0; i<nbins; i++){
		for(int j=0; j<totaleventos; j++){
			if( (i+Hmin)==HD[j]  )dat1[i]++;/////////////<= mejor
			
		}
	}


	QVector<double>dat(nbins);
	for(int i=0; i<nbins; i++)dat[i]=dat1[nbins-i];


	dat1.clear();
	


	TH1F *pedestal=new TH1F("cali", "calititulo", nbins, Hmin, Hmax);
	

	for(int i=0; i<totaleventos; i++)pedestal->Fill(HD[i]);

	TSpectrum *peak=new TSpectrum(5);
	int npeaks = peak->Search(pedestal,4,"",0.05);
	float *peaksX=peak->GetPositionX();
	float *peaksY=peak->GetPositionY();
	cout<<222000-*peaksX<<endl<<*peaksY<<endl<<*(peaksX+1)<<endl<<*(peaksY+1)<<endl;
	int ancho=60;
	int centropre=*peaksX;
	int altopre=*peaksY;


		TF1 *func1 = new TF1("func1","gaus", centropre-ancho, centropre+ancho); //hago un fit de la gausiana, con el primer parametro de nombre 0.
				
				func1->SetParameters(altopre, centropre, ancho); 
				//func1->SetParLimits(0,4,6); // parametro 0 entre 4 y 6 (media entre 4 y 6)
				//func1->SetParLimits(1,0,100); parametro 1 entre 0 y 100 (sigma entre 0 y 100)
				//func1->SetParLimits(2,0,500000); //parametro 2 entre 0 y 500000 (constante entre 0 y 500000). No conveniente mejor funcion de peaksY.
				pedestal->Fit("func1","R+");//RB+
				Double_t par2[3];				
				func1->GetParameters(par2);cout<<222000-par2[0]<<endl;
				
	delete pedestal;	
//	pedestal->~TH1F();





  emit anlpedestalcompletado(dat, centropre, 1);

  HD.clear();
  dat.clear();
  

} 


void analisis::anlcalibracristal(const datadqi &datach1, int totaleventos, int totalmuestras){


FILE *asdf;
asdf = fopen("histogramdata.txt","w");

using namespace std;





  int Hmin = 0;
  int Hmax = 0;
  int nbins= 0;

 
	int aux=0;//integrador

 
cout << "totalmuestras:" << totalmuestras << endl;
	
cout  << "totaleventos:"<< totaleventos << endl;



	int muestxevent;
	if(totaleventos!=0){muestxevent=(totalmuestras+1)/totaleventos;cout<< "muestxevent:"  << muestxevent << endl;}
	else muestxevent=0;


///////////integrar los datos del canal 1////////////////

  	vector<float>HD;//Histogram data (salida del integrador)

	for(int i=0; i<totaleventos; i++){
		for(int j=0; j<muestxevent; j++){       
			
			aux=aux+datach1[j+muestxevent*i];
		}
				
		HD.push_back(aux);fprintf(asdf,"%d\n", aux);aux=0;
	}

	//cout<<"tamaño HD:"<<HD.size()<<endl;
	//for (int i=0; i<totaleventos; ++i)cout<<HD[i]<<endl;

        if(HD.size()!=0){
    	//Hmin = *min_element(HD.begin(), HD.end());;cout << "Hmin:" << Hmin << endl;
    	//Hmax = *max_element(HD.begin(), HD.end());;cout << "Hmax:" << Hmax << endl;
	Hmin=208000;
	Hmax=222000;
	nbins= Hmax-Hmin;cout << "nbins:" << nbins << endl<<endl;
	}
	else nbins=1;
	
	QVector<double>dat1(nbins);dat1[0]=0;
	for(int i=1; i<nbins; i++){
		for(int j=0; j<totaleventos; j++){
			if( (i+Hmin)==HD[j]  )dat1[i]++;
			
		}
	}


	QVector<double>dat(nbins);
	for(int i=0; i<nbins; i++)dat[i]=dat1[nbins-i];


	dat1.clear();



//for (int i=700; i<710; ++i)cout<<dat[i]<<endl;



  if(muestxevent!=0){

	TH1F *cristal=new TH1F("cali", "calititulo", nbins, Hmin, Hmax);
	

	for(int i=0; i<totaleventos; i++){cristal->Fill(HD[i]);}

	TSpectrum *peak=new TSpectrum(5);
	int npeaks = peak->Search(cristal,10,"",0.3);
	float *peaksX=peak->GetPositionX();
	float *peaksY=peak->GetPositionY();
	for(int i=0; i<10; i++)cout<<Hmax-*(peaksX+i)<<"      "<<*(peaksX+i)<<"            "<<*(peaksY+i)<<endl;

	TF1 *func2 = new TF1("func2","gaus",211412,212388); //hago un fit de la gausiana, con el primer parametro de nombre 0.
				
				func2->SetParameters(10, 212000,250); 
				/*func2->SetParLimits(0,4,6);
				func2->SetParLimits(1,-635800,635800);
				func2->SetParLimits(2,0,500);*/
				//func2->SetLineColor(kRed);
				cristal->Fit("func2","RB+");
				Double_t par2[3];				
				func2->GetParameters(&par2[0]);cout<<par2[0]<<endl;
				
	
	cristal->~TH1F();fclose(asdf);
	emit finanlcristal(dat, par2[0], 2);
  }

  

  HD.clear();
  dat.clear();


} 


