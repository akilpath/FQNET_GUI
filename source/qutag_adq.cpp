 #include <adqui.h>
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt



//////////////////////////////////////////////////
//////constructor, inicializa el conversor////////
//////////////////////////////////////////////////
adquiclass::adquiclass(){
	
	

  }
  /*else{
	printf("El conversor esta con problemas\n");printf("error %d\n", ret);terminate();
	}*/
	
}

/////////////////////////////////////////
////////loop de adquisicion//////////////
////////////////////////////////////////


 void adquiclass::adquisichon(){


	
	else{

		ret = CAEN_DGTZ_ClearData(handle);
		gettimeofday(&ti,NULL);
	
//////////////////////adquisision ad infinitum//////////////////

		while(1){
			
	
			conta=0;
			contaeve=0;
			k=0;
			s=0;
		
			gettimeofday(&ti,NULL);
			//time = t.tv_sec-ti.tv_sec;

			for (time = 0 ;time < _tiempoadq; gettimeofday(&t,NULL), time = t.tv_sec-ti.tv_sec) {


				while(_pause)sleep(1);
				c = checkCommand();


				if (c == 1) {
     					printf("TEMINATOR\n");
					ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
					ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    					CAEN_DGTZ_CloseDigitizer(handle);
    					terminate();
				}

				if (c == 2){
     					printf("TEMINATOR\n");
					ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
					ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    					CAEN_DGTZ_CloseDigitizer(handle);
   					terminate();
				}

	
				if(_stop)break;
				//ahora guarda en buffer la info y en bsize el tamaño de la info guardada en buffer
				ret = CAEN_DGTZ_ReadData(handle,CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT,buffer,(uint32_t *)&bsize);

				if(ret!=0){
					printf("error %d\n", ret);
					emit error1();break;
				}
				//entrega en numEvents el numero de eventos capturados
				ret = CAEN_DGTZ_GetNumEvents(handle,buffer,bsize,(uint32_t *)&numEvents);

				conta +=numEvents;//if(conta<10)printf("conta %d\n", conta);

				fflush(stdout);

				/*if(ret!=0){
					printf("reinicialice/encienda el conversor\n");
					emit error1();break;
		
				}*/

				for (unsigned int i=0;i<numEvents;i++) {

					datascope.clear();

					//evtptr es un puntero al evento en particular i
					ret = CAEN_DGTZ_GetEventInfo(handle,buffer,bsize,0,&eventInfo,(char **)&evtptr);
		
					ret = CAEN_DGTZ_DecodeEvent(handle,evtptr,(void **)&Evt);	


					for (j=0;j<Evt->ChSize[0];j++){				
						data.append(*(Evt->DataChannel[0]+j));
						line++;//printf("conta %d\n", j);
						if(Evt!=0)datascope.append(*(Evt->DataChannel[0]+j));
					}
				}


				//emit scope(datascope);
				
				contaeve+=numEvents;				
				if(time>k){

					k++;
					double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
					emit finadqeven(contaeve, key);
					if(contaeve > _eventosfoto)emit adquifoto();
					contaeve=0;emit scope(datascope);
				}
				
			}
			

			if(ret!=0){
				printf("error %d\n", ret);
				break;
			}

			
	
			printf("salgo for adquisicion (10 sec)\n");

			if(_stop)break;
			if(conta!=0)emit finadqhist(data, conta, line);
			printf("emit final adq\n");
			data.clear();conta=0;line=0;
			
		}//while(1)//////////////////////////////////////////

	}//else
	_stop=false;printf("sali del while\n");
	
}


////////////////////////////////////////////////
//////////slots para pausar/reanudar la adq////
/////////////////////////////////////////////////

void adquiclass::detener(){
	_pause=true;
}

void adquiclass::continuar(){
	_pause=false;
}

void adquiclass::stopadq(){
	if(_stop)terminate();
	_stop=true;printf("stopadq\n");
	
}

/////////////////////////////////////////////////////////////////
/////////reinicializa el conversor//////////////////////////////
/////////////////////////////////////////////////////////////////


void adquiclass::reset(){

	_threshold1=8061;
	handle=0;

	habilitados=0xf;
	Evt = NULL;
	buffer= NULL ;
	evtptr = NULL;
	_stop=false;

	triggermode = CAEN_DGTZ_TRGMODE_ACQ_ONLY;	//para uso con el proyecto
	acqmode = CAEN_DGTZ_SW_CONTROLLED;			//control por software
	line=0;//c = 0;
	i = sizeof(CAEN_DGTZ_TriggerMode_t);
	ret = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_USB,0,0,0,&handle);		 //configuracion para uso con USB (linktype,linknum,0,0)

	//printf("error1 %d\n", ret);

	if(ret==-1){
		printf("reinicialice/encienda el conversor (reset)\n");
		emit error1();
	}

  if(ret==0 || ret==-25){
		// resetting Digitizer//
          //printf("error2 %d\n", ret);
	ret = CAEN_DGTZ_Reset(handle);	//printf("error3 %d\n", ret);
	ret = CAEN_DGTZ_GetInfo(handle, &BoardInfo);//usleep(100);  printf("error3 %d\n", ret);	//printf("debug\n");		//guarda en BoardInfo informacion sobre el modulo
	ret = CAEN_DGTZ_SetRecordLength(handle,25);			// samples a grabar por acquisition windows CAMBIAR es decir tamaño de buffer
	ret = CAEN_DGTZ_SetChannelEnableMask(handle,habilitados); 		// no disponible en el DT5740





	//ret = CAEN_DGTZ_SetSWTriggerMode(handle, triggermode);			//modo software trigger 
	//ret = CAEN_DGTZ_SetExtTriggerInputMode(handle, triggermode); 		//modo trigger externo
	ret = CAEN_DGTZ_SetChannelSelfTrigger(handle,triggermode,0xf); 	// Set trigger on channel 0 to be ACQ_ONLY
	//ret = CAEN_DGTZ_SetChannelGroupMask(handle, 3, 7);		printf("error %d\n", ret);	//canales que contribuyen al evento de los grupos especificados solo en DT5740
	
	ret = CAEN_DGTZ_SetPostTriggerSize(handle, 2); 			//% a grabar por cada trigger del record length
	ret = CAEN_DGTZ_SetAcquisitionMode(handle, acqmode);			// modo de adquisicion
	ret = CAEN_DGTZ_SetIOLevel(handle, CAEN_DGTZ_IOLevel_NIM); 		// entrada salida TTL puede ser CAEN_DGTZ_IOLevel_NIM
 
	ret = CAEN_DGTZ_SetChannelTriggerThreshold(handle,0,_threshold1);//-20mV		// 14 bits, distribuidos según el rango. [-1.125 , -1.125], [0 , 2.25]
	ret = CAEN_DGTZ_SetChannelTriggerThreshold(handle,1,9000);		
	ret = CAEN_DGTZ_SetChannelTriggerThreshold(handle,2,10000);	
	ret = CAEN_DGTZ_SetChannelTriggerThreshold(handle,3,10000);	
	ret = CAEN_DGTZ_SetMaxNumEventsBLT(handle,1);			//numero maximo de eventos por transferencia

	printf("firmware %s\n", (char *)&BoardInfo.ROC_FirmwareRel);
	printf("firmware %s\n", (char *)&BoardInfo.AMC_FirmwareRel);
	printf("model %s\n", (char *)&BoardInfo.ModelName);


	uint32_t registros;
	ret= CAEN_DGTZ_ReadRegister(handle, 0x810C, &registros);//trigger source enable mask register
	registros |= (0x0<<24); //coincidencias para el autotrigger
	ret= CAEN_DGTZ_WriteRegister(handle, 0x810C, registros);
	ret= CAEN_DGTZ_ReadRegister(handle, 0x810C, &registros);
	ret = CAEN_DGTZ_MallocReadoutBuffer(handle,&buffer,(uint32_t *)&size);		

	/*printf("presione 's' para comenzar la adquisision\n");
    	printf("presione 'k' para detener la adquisision\n");
    	printf("presione 'q' para salir de la adquisision\n\n");
    	while (1) {
		c = checkCommand();
		if (c == 9) break;
		if (c == 2) {printf("llegue"); terminate();}
		usleep(100);
    	}*/


	ret = CAEN_DGTZ_SWStartAcquisition(handle);	


	x = 0;
	
	
  }

}

///////////////////////////////////////////////////////////////////////////////////
/////////////calculo del pedestal, calibracion/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////



void adquiclass::pedestal(){

//stopadq();sleep(1);

ret = CAEN_DGTZ_SetSWTriggerMode(handle, triggermode);			//modo software trigger 
printf("inicio de la calibracion \n");
if(ret==-1){
		printf("reinicialice/encienda el conversor\n");
		emit error1();
	}



	else{

	
		gettimeofday(&ti,NULL);
	
//////////////////////adquisision ad infinitum//////////////////
		conta=0;
		k=0;

		gettimeofday(&ti,NULL);
		while(1){			
			//sleep(1);
			ret= CAEN_DGTZ_SendSWtrigger(handle);

			gettimeofday(&t,NULL);
			time = t.tv_sec-ti.tv_sec;



				c = checkCommand();


				if (c == 1) {
     					printf("TEMINATOR\n");
					ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
					ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    					CAEN_DGTZ_CloseDigitizer(handle);
    					terminate();
				}

				if (c == 2){
     					printf("TEMINATOR\n");
					ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
					ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    					CAEN_DGTZ_CloseDigitizer(handle);
   					terminate();
				}

				

				//ahora guarda en buffer la info y en bsize el tamaño de la info guardada en buffer
				ret = CAEN_DGTZ_ReadData(handle,CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT,buffer,(uint32_t *)&bsize);

				if(ret!=0){
					printf("reinicialice/encienda el conversor TERMINATOR\n");
					emit error1();break;
				}
				//entrega en numEvents el numero de eventos capturados
				ret = CAEN_DGTZ_GetNumEvents(handle,buffer,bsize,(uint32_t *)&numEvents);

				conta +=numEvents;


				for (unsigned int i=0;i<numEvents;i++) {

					//evtptr es un puntero al evento en particular i
					ret = CAEN_DGTZ_GetEventInfo(handle,buffer,bsize,i,&eventInfo,(char **)&evtptr);
		
					ret = CAEN_DGTZ_DecodeEvent(handle,evtptr,(void **)&Evt);	


					for (j=0;j<Evt->ChSize[0];j++){				
						data.append(*(Evt->DataChannel[0]+j));
						line++;
					}
				}


				

				//gettimeofday(&t,NULL);
				//time = t.tv_sec-ti.tv_sec;
	
			//printf(".");
			if(conta>_eventospedestal){
				
				break;
			}
			

			/*if(ret!=0){
				//printf("reinicialice/encienda el conversor\n");
				break;
			}*/


		}//while(1)//////////////////////////////////////////

	 	double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
		emit finadqeven(contaeve, key);

		emit finpedestal(data, conta, line);
		printf("\n emit final cali\n");
		data.clear();conta=0;line=0;

	}//else

calibracristal();
}


 void adquiclass::calibracristal(){


	if(ret==-1){
		printf("reinicialice/encienda el conversor\n");
		emit error1();
	}

	else{

		ret = CAEN_DGTZ_ClearData(handle);
		gettimeofday(&ti,NULL);
	
//////////////////////adquisision ad infinitum//////////////////

			
	
			conta=0;
			contaeve=0;
			k=0;
			s=0;
		
			gettimeofday(&ti,NULL);
			//time = t.tv_sec-ti.tv_sec;

			for (time = 0 ;time < _tiempocalibracristal; gettimeofday(&t,NULL), time = t.tv_sec-ti.tv_sec) {

				if(_stop)break;
				while(_pause)sleep(1);
				c = checkCommand();


				if (c == 1) {
     					printf("TEMINATOR\n");
					ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
					ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    					CAEN_DGTZ_CloseDigitizer(handle);
    					terminate();
				}

				if (c == 2){
     					printf("TEMINATOR\n");
					ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
					ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
    					CAEN_DGTZ_CloseDigitizer(handle);
   					terminate();
				}

	
				
				//ahora guarda en buffer la info y en bsize el tamaño de la info guardada en buffer
				ret = CAEN_DGTZ_ReadData(handle,CAEN_DGTZ_SLAVE_TERMINATED_READOUT_MBLT,buffer,(uint32_t *)&bsize);

				if(ret!=0){
					printf("error %d\n", ret);
					emit error1();
				}
				//entrega en numEvents el numero de eventos capturados
				ret = CAEN_DGTZ_GetNumEvents(handle,buffer,bsize,(uint32_t *)&numEvents);

				conta +=numEvents;//if(conta<10)printf("conta %d\n", conta);

				fflush(stdout);

				/*if(ret!=0){
					printf("reinicialice/encienda el conversor\n");
					emit error1();break;
		
				}*/

				for (unsigned int i=0;i<numEvents;i++) {

					datascope.clear();

					//evtptr es un puntero al evento en particular i
					ret = CAEN_DGTZ_GetEventInfo(handle,buffer,bsize,0,&eventInfo,(char **)&evtptr);
		
					ret = CAEN_DGTZ_DecodeEvent(handle,evtptr,(void **)&Evt);	


					for (j=0;j<Evt->ChSize[0];j++){				
						data.append(*(Evt->DataChannel[0]+j));
						line++;//printf("conta %d\n", j);
						if(Evt!=0)datascope.append(*(Evt->DataChannel[0]+j));
					}
				}


				
				contaeve+=numEvents;				
				if(time>k){

					k++;
					double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
					emit finadqeven(contaeve, key);
					contaeve=0;emit scope(datascope);
				}
				
			}
			


			
	
			printf("salgo for adquisicion (10 sec)\n");

			
			if(conta!=0)emit fincalibracristal(data, conta, line);
			printf("emit final calibra cristal\n");
			data.clear();conta=0;line=0;
			

	}//else
printf("sali del while\n");
	
}


//////////////////////////
///////destructor//////////
//////////////////////////

adquiclass::~adquiclass()
{
ret = CAEN_DGTZ_FreeEvent(handle,(void **)&Evt);
ret = CAEN_DGTZ_FreeReadoutBuffer(&buffer);
ret =  CAEN_DGTZ_CloseDigitizer(handle);
//terminate();

}

///////////////////////
////////getch////////////
/////////////////////////

int adquiclass::checkCommand() {
	int c = 0;//printf("check\n");
	if(!kbhit())
			return 0;

	c = getch();
	switch (c) {
		case 's': 
			return 9;
			break;
		case 'k':
			return 1;
			break;
		case 'q':
			return 2;
			break;
	}
	return 0;
}

/////////////////////////////////////////
//////slot para cambiar threshold////////
////////////////////////////////////////


void adquiclass::Cthreshold1(double threshold1)
{
_threshold1=(int)8192*threshold1/1.25+8192;
//printf("%d", _threshold1)
ret = CAEN_DGTZ_SetChannelTriggerThreshold(handle,0,_threshold1);
}

///////////////////////////////////////////////////////
//////slot para cambiar numero eventos pedestal////////
//////////////////////////////////////////////////////


void adquiclass::Ceventoscali(int eventospedestal)
{
_eventospedestal=eventospedestal;
}

void adquiclass::Ctiempocali(int tiempocali)
{
_tiempocali=tiempocali;
}

void adquiclass::Ctiempoadq(int tiempoadq)
{

_tiempoadq=tiempoadq;
}

void adquiclass::Ccristaltime(int cristaltime)
{
_tiempocalibracristal=cristaltime;
}

void adquiclass::Ceventosfoto(int eventosfoto)
{
_eventosfoto=eventosfoto;
}
void adquiclass::tipoadq1()
{
  _tipoadq=1;
  start();
}

void adquiclass::tipoadq2()
{
  _tipoadq=2;
  start();
}

