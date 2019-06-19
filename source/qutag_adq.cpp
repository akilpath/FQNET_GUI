 #include <qutag_adq.h>
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt



//////////////////////////////////////////////////
//////constructor////////
//////////////////////////////////////////////////
qutagadq::qutagadq(){
  /*else{
	printf("El conversor esta con problemas\n");printf("error %d\n", ret);terminate();
	}*/
	
}

void qutagadq::run(){

    rc = TDC_init( -1 );                                 /* Accept every device */
    checkRc( "TDC_init", rc );
}

/* Check return code and exit on error */
void qutagadq::checkRc( const char * fctname, int rc )
{
  if ( rc ) {
    printf( ">>> %s: %s\n", fctname, TDC_perror( rc ) );
    /* Don't quit on "not connected" to allow for demo mode */
    if ( rc != TDC_NotConnected ) {
      TDC_deInit();
      exit( 1 );
    }
  }
}
/////////////////////////////////////////
////////loop de adquisicion//////////////
////////////////////////////////////////


 void qutagadq::adqui(){


	



    //	gettimeofday(&ti,NULL);
	
//////////////////////adquisition loop/////////////////

		while(1){
			
	


            //gettimeofday(&ti,NULL);
            //time = t.tv_sec-ti.tv_sec;

            //for (time = 0 ;time < _tiempoadq; gettimeofday(&t,NULL), time = t.tv_sec-ti.tv_sec) {


                //while(_pause)sleep(1);




	
				if(_stop)break;

				if(ret!=0){
					printf("error %d\n", ret);
                    //emit error1();break;
				}

                //fflush(stdout);




                    //	data.append(*(Evt->DataChannel[0]+j));

					}



				//emit scope(datascope);
				

                /*if(time>k){

					k++;
					double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
					emit finadqeven(contaeve, key);
					if(contaeve > _eventosfoto)emit adquifoto();
					contaeve=0;emit scope(datascope);
                }*/
				

			

            /*if(ret!=0){
				printf("error %d\n", ret);
				break;
            }*/

			
	

            //if(_stop)break;
            //if(conta!=0)emit finadqhist(data, conta, line);
            //printf("emit final adq\n");
            //data.clear();

	
}


////////////////////////////////////////////////
//////////slots para pausar/reanudar la adq////
/////////////////////////////////////////////////

/*void adquiclass::detener(){
	_pause=true;
}
*/

 qutagadq::~qutagadq(){
   /*else{
     printf("El conversor esta con problemas\n");printf("error %d\n", ret);terminate();
     }*/

 }
