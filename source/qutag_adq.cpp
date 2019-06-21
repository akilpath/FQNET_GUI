#include <qutag_adq.h>
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt
#define SLEEP(x) usleep(x)






//////////////////////////////////////////////////
//////constructor////////
//////////////////////////////////////////////////
qutagadq::qutagadq(){

    timetags.reserve(TIMESTAMP_COUNT);
    channelsTDC.reserve(TIMESTAMP_COUNT);
    //// goes here ////
	
}

void qutagadq::run(){

    rc = TDC_init( -1 );                                 /* Accept every device */
    checkRc( "TDC_init", rc );

    rc = TDC_getTimebase( &timeBase );
    checkRc( "TDC_getTimebase", rc );

    rc = TDC_enableChannels( 0xff );                     /* Use all channels */
    checkRc( "TDC_enableChannels", rc );

    rc = TDC_setTimestampBufferSize( TIMESTAMP_COUNT );
    checkRc( "TDC_setTimestampBufferSize", rc );

    rc = TDC_configureSignalConditioning(0, SCOND_MISC, 1, .2);
    rc = TDC_configureSignalConditioning(1, SCOND_MISC, 1, .2);
    rc = TDC_configureSignalConditioning(2, SCOND_MISC, 1, .2);
    rc = TDC_configureSignalConditioning(3, SCOND_MISC, 1, .2);
    rc = TDC_configureSignalConditioning(4, SCOND_MISC, 1, .2);
    checkRc( "TDC_configureSignalConditioning", rc );

    rc = TDC_setExposureTime( EXP_TIME );
    checkRc( "TDC_setExposureTime", rc );


    SLEEP( 1e3 );
    TDC_getCoincCounters( coincCnt, NULL );
    SLEEP( 1e3 );
    TDC_getCoincCounters( coincCnt, NULL );
    SLEEP(1e6);
    TDC_getCoincCounters( coincCnt, NULL );

    rc = TDC_configureSignalConditioning(4, SCOND_MISC, 1, .1);

    TOTAL_RATE = rate(coincCnt[0]+coincCnt[1]+coincCnt[2]+coincCnt[3]+coincCnt[4]);
    COLLECT_TIME = get_max_collection_time(TOTAL_RATE);/* Time [us] for data acquisition per round */


    printf("total rate is: %f", TOTAL_RATE);

    fflush(stdout);

    /*
    if (TOTAL_RATE == 0) {
            printf("\n\nNo signals detected. Exiting...\n\n");
            fflush(stdout);
            TDC_deInit();
            return;
    }
    */




}

/* Check return code and exit on error */
void qutagadq::checkRc( const char * fctname, int rc )
{
  if ( rc ) {
    printf("error\n");
    printf( ">>> %s: %s\n", fctname, TDC_perror( rc ) );
    /* Don't quit on "not connected" to allow for demo mode */
    if ( rc != TDC_NotConnected ) {
      printf("error\n");
      TDC_deInit();
      exit( 1 );
    }
  }
}




 void qutagadq::adqui(){

    //	gettimeofday(&ti,NULL);
	
//////////////////////adquisition loop/////////////////

		while(1){
            printf("running");
            TDC_getLastTimestamps( 1, timestamps, channels, &tsValid );
            SLEEP(1e6);

            std::copy(timestamps, timestamps + TIMESTAMP_COUNT, std::back_inserter(timetags));
            std::copy(channels, channels + TIMESTAMP_COUNT, std::back_inserter(channelsTDC));

            emit dataready(timetags, channelsTDC, tsValid);
            //gettimeofday(&ti,NULL);
            //time = t.tv_sec-ti.tv_sec;

            //for (time = 0 ;time < _tiempoadq; gettimeofday(&t,NULL), time = t.tv_sec-ti.tv_sec) {
//			if(_stop)break;
         //   while(_pause);

                //fflush(stdout);

                //emit finadqhist(data, event, nmuest);


                /*if(time>k){

					k++;
					double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
					emit finadqeven(contaeve, key);
					if(contaeve > _eventosfoto)emit adquifoto();
					contaeve=0;emit scope(datascope);
                }*/
							


        }

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


 //int foo(int a){

     //return 1;
 //}



 float qutagadq::rate(int ch_rate)
 {
   return ((float)ch_rate/(float)EXP_TIME)*1.e3/1.e6;//convert to Hz then to MHz
 }

 int qutagadq::get_max_collection_time( float rate )
 {
   return (int)((float)TIMESTAMP_COUNT*0.90/rate);//rate in MHz so time is in us
 }


 void qutagadq::clockchange(int clockchannel)
 {
     printf("clockchannel is: %d", clockchannel);
     fflush(stdout);
     //this is a test function. Set the clock channel to different voltage level
     TDC_configureSignalConditioning(2, SCOND_MISC, 1, 1);
 }
