#include <qutag_adq.h>
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt



//////////////////////////////////////////////////
//////constructor////////
//////////////////////////////////////////////////
qutagadq::qutagadq(){

	
}

void qutagadq::run(){

    rc = TDC_init( -1 );                                 /* Accept every device */
    checkRc( "TDC_init", rc );

    rc = TDC_getTimebase( &timeBase );
    checkRc( "TDC_getTimebase", rc );

    rc = TDC_enableChannels( 0xff );                     /* Use all channels */
    checkRc( "TDC_enableChannels", rc );
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




 void qutagadq::adqui(){

    //	gettimeofday(&ti,NULL);
	
//////////////////////adquisition loop/////////////////

		while(1){

            TDC_getLastTimestamps( 1, timestamps, channels, &tsValid );
            //gettimeofday(&ti,NULL);
            //time = t.tv_sec-ti.tv_sec;

            //for (time = 0 ;time < _tiempoadq; gettimeofday(&t,NULL), time = t.tv_sec-ti.tv_sec) {
//			if(_stop)break;
         //   while(_pause);



                //fflush(stdout);






				//emit scope(datascope);
				

                /*if(time>k){

					k++;
					double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
					emit finadqeven(contaeve, key);
					if(contaeve > _eventosfoto)emit adquifoto();
					contaeve=0;emit scope(datascope);
                }*/
							


        }
            //if(_stop)break;
            //if(conta!=0)emit finadqhist(data, conta, line);
            //printf("emit final adq\n");
            //data.clear();

	
}




/*void adquiclass::detener(){
	_pause=true;
}
*/

 qutagadq::~qutagadq(){

TDC_deInit();

 }
