#include <qutag_adq.h>
#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt
#include <time.h>
#define SLEEP(x) usleep(x)






//////////////////////////////////////////////////
//////constructor////////
//////////////////////////////////////////////////
qutagadq::qutagadq(){

    timetags.reserve(TIMESTAMP_COUNT+1);
    channelsTDC.reserve(TIMESTAMP_COUNT+1);
    break_=false;
    adqpause_=false;
    histodataA=0;
    histodataB=0;


    printf( ">>> tdcbase version: %f\n", TDC_getVersion() );
    rc = TDC_init( -1 );                                 /* Accept every device */
    checkRc( "TDC_init", rc );

    rc = TDC_getTimebase( &timeBase );
    checkRc( "TDC_getTimebase", rc );
    printf( ">>> timebase: %g ps\n", timeBase * 1.e12 );
    fflush(stdout);


    rc = TDC_enableChannels( 0xff );                     /* Use all channels */
    checkRc( "TDC_enableChannels", rc );

    rc = TDC_setTimestampBufferSize( TIMESTAMP_COUNT );
    checkRc( "TDC_setTimestampBufferSize", rc );

    rc = TDC_setExposureTime( 1000 );
    checkRc( "TDC_setExposureTime", rc );

    RoF[1]=0;
    RoF[2]=0;
    RoF[3]=0;


    //rc = TDC_configureFilter(1, FILTER_COINC, 3);
   /* rc = TDC_configureSignalConditioning(0, SCOND_MISC, 1, .1);
    rc = TDC_configureSignalConditioning(1, SCOND_MISC, 0, .50);
    rc = TDC_configureSignalConditioning(2, SCOND_MISC, 0, -0.150);
    rc = TDC_configureSignalConditioning(3, SCOND_MISC, 0, -0.150);
    rc = TDC_configureSignalConditioning(4, SCOND_MISC, 1, .1);
    checkRc( "TDC_configureSignalConditioning", rc );*/



    //rc = TDC_enableMarkers(0);        //WHY IS THIS NOT WORKING??
    //checkRc( "TDC_enableMarkers", rc);

    //rc = TDC_setExposureTime( EXP_TIME );
    //checkRc( "TDC_setExposureTime", rc );

    rc = TDC_setCoincidenceWindow( 90000 ); /* 30ns */
    checkRc( "TDC_setCoincidenceWindow", rc );


    SLEEP( 1e3 );
    TDC_getCoincCounters( coincCnt, NULL );
    SLEEP( 1e3 );
    TDC_getCoincCounters( coincCnt, NULL );
    SLEEP(1e6);
    TDC_getCoincCounters( coincCnt, NULL );



    req.tv_sec = 0;
    req.tv_nsec = microsec * 1000L;

    fflush(stdout);



    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            ActHist[i][j]=0;
        }
    }
    rc = TDC_getTimebase( &timeBase );

    checkRc( "TDC_getTimebase", rc );
    printf( ">>> timebase: %g ps\n", timeBase * 1.e12 );

    rc = TDC_enableStartStop( 1 );
    checkRc( "TDC_enableStartStop", rc );


}

void qutagadq::run(){

lautrun();
//andrewrun();
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




	
}



 qutagadq::~qutagadq(){

TDC_deInit();

 }


 float qutagadq::rate(int ch_rate)
 {
   return ((float)ch_rate/(float)EXP_TIME)*1.e3/1.e6;//convert to Hz then to MHz
 }


 int qutagadq::get_max_collection_time( float rate )
 {
   return (int)((float)TIMESTAMP_COUNT*0.90/rate);//rate in MHz so time is in us
 }





int qutagadq::filterset(){

    int maskA=0x00 , maskB=0x00, maskC=0x00;

    maskA|=0x1<<(in_PlotACh2);
    maskA|=0x1<<(in_startChan);

    maskB|=0x1<<(in_PlotBCh1);
    maskB|=0x1<<(in_startChan);

    maskC|=0x1<<(in_PlotACh2);
    maskC|=0x1<<(in_PlotBCh2);
    //maskC|=0x1<<(in_startChan);

   /* std::cout<<"filter channel : "<<in_startChan<<"  , mask : "<<maskC<<std::endl;
    std::cout<<"filter channel : "<<in_PlotACh2<<"  , mask : "<<maskA<<std::endl;
    std::cout<<"filter channel : "<<in_PlotBCh2<<"  , mask : "<<maskB<<std::endl;*/
    rc = TDC_configureFilter(in_startChan, FILTER_SYNC , maskC);
    checkRc( "TDC_configureFilter clock", rc );
    rc = TDC_configureFilter(in_PlotACh2, FILTER_NONE, maskA);
    checkRc( "TDC_configureFilter mask A", rc );
    rc = TDC_configureFilter(in_PlotBCh2, FILTER_NONE, maskB);
    checkRc( "TDC_configureFilter mask B", rc );

    return 0;
}







 void qutagadq::lautrun(){
    // setHistograms();

  TDC_clearAllHistograms ();

  //filterset();
  //Int32 coincWin = in_histEnd-in_histStart;
  //rc =TDC_setCoincidenceWindow(coincWin);
  //checkRc( "TDC_enableStartStop", rc );
    double previous_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    double current_time;

     while(!break_){
         current_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        // std::cout<< current_time-previous_time <<std::endl;
         if((current_time-previous_time) > 1000*in_adqtime){
             getHisto();
             previous_time = current_time;
         }
         getTimeStamps();
         QThread::msleep(100);

     }

 }

 void qutagadq::getHisto(){
    //std::cout<<"gethisto"<<std::endl;
    if(paramschange)setHistograms();
    if(rc)return;

     if (histodataA != 0) {
         delete [] histodataA;
     }

     histodataA = new Int32 [in_binsinplot];

     if (histodataB != 0) {
         delete [] histodataB;
     }

     histodataB = new Int32 [in_binsinplot];

    /* std::cout<<"binsinplot adq  :  "<< in_binsinplot<<std::endl;
     std::cout<<"plot 1A  :  "<< in_PlotACh1<<std::endl;
     std::cout<<"plot 2A  :  "<< in_PlotACh2<<std::endl;
*/

     // Retreive and print selected start stop histogram
     if(in_PlotACh1==in_PlotBCh1 && in_PlotACh2==in_PlotBCh2)
       rc = TDC_getHistogram(in_PlotACh1, in_PlotACh2, 0, histodataA, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );
     else rc = TDC_getHistogram(in_PlotACh1, in_PlotACh2, 1, histodataA, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );

       checkRc( "TDC_getHistogram A", rc );
      // printf( ">>> Histogram 1-2:     valid=%d tooSmall=%d tooBig=%d\n", count, tooSmall, tooBig );
      // printf( ">>>                    starts=%d  stops=%d expTime=%g s\n", eventsA, eventsB, expTime * timeBase );
      /* printf( ">>>       Bin Time   Counter global      Counter 1-2\n" );
       for ( i = 0; i < HIST_BINCOUNT; ++i ) {
        ////// "Bin Time" is the lower limit of the bin
         printf( ">>> %12fns %16d %16d\n", i * bin2ns, histodataA[i]);
       }*/
       //std::copy(histodataA, histodataA + HIST_BINCOUNT, std::back_inserter(histo2vector));

        count1=count;

       QVector<double> dataA(in_binsinplot);
       for (int i=0; i<in_binsinplot; ++i){

           dataA[i]=(double) histodataA[i];
       }


      /* std::cout<<"in_binsinplot  :  "<< in_binsinplot<<std::endl;
       std::cout<<"plot 1B  :  "<< in_PlotBCh1<<std::endl;
        std::cout<<"plot 2B  :  "<< in_PlotBCh2<<std::endl;*/


       rc = TDC_getHistogram(in_PlotBCh1, in_PlotBCh2, 1, histodataB, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );
       checkRc( "TDC_getHistogram B", rc );

      //  printf( ">>> Histogram 1-2:     valid=%d tooSmall=%d tooBig=%d\n", count, tooSmall, tooBig );
       // printf( ">>>                    starts=%d  stops=%d expTime=%g s\n", eventsA, eventsB, expTime * timeBase );
        /*printf( ">>>       Bin Time   Counter global      Counter 1-2\n" );
        for ( i = 0; i < HIST_BINCOUNT; ++i ) {
         ////// "Bin Time" is the lower limit of the bin
          printf( ">>> %12fns %16d %16d\n", i * bin2ns, histodataA[i]);
        }
*/

       count2=count;

       QVector<double> dataB(in_binsinplot);

       for (int i=0; i<in_binsinplot; ++i){

           dataB[i]=(double) histodataB[i];
       }

       if(count1 != 0 || count2 !=0)emit(qutaghist(dataA, dataB));
       dataA.clear();
       dataB.clear();

 }


 void qutagadq::getTimeStamps(){
    timetags.clear();channelsTDC.clear();
     rc = TDC_getLastTimestamps( 1, timestamps, channels, &tsValid );
     checkRc( "TDC_getHistogram A", rc );
     std::copy(timestamps, timestamps + tsValid, std::back_inserter(timetags));
     std::copy(channels, channels + tsValid, std::back_inserter(channelsTDC));
     if(tsValid>0 && anlAvilable){
         emit dataready(timetags, channelsTDC, (int)tsValid);
     }

 }

 void qutagadq::setHistograms(){


     /////////calculate histogram parameters///////////

     HIST_BINWIDTH=(int)(in_histEnd-in_histStart)/in_binsinplot;
     HIST_BINCOUNT=in_binsinplot;
     filterset();

    /* std::cout<<"HIST_BINWIDTH  :  "<< HIST_BINWIDTH<<std::endl;
     std::cout<<"HIST_BINCOUNT  :  "<< HIST_BINCOUNT<<std::endl;
     std::cout<<"HIST_BINWIDTH  *  HIST_BINCOUNT  :  "<< HIST_BINWIDTH*HIST_BINCOUNT<<std::endl;*/
     bin2ns = HIST_BINWIDTH * timeBase * 1.e9;

     /////////////create the histograms on the FPGA only if is necesary/////////////

     if(ActHist[in_PlotACh1][in_PlotACh2]==0){
         firstChanHist=in_PlotACh1;
         secondChanHist=in_PlotACh2;
         ActHist[in_PlotACh1][in_PlotACh2]=1;
        // std::cout<<"quewepasahermano  "<<std::endl;
         rc = TDC_addHistogram( firstChanHist, secondChanHist, 1 );
         checkRc( "TDC_addHistogram", rc );
         //std::cout<<"quewepasahermano 2 "<<std::endl;
     }


     if(in_PlotACh1!=in_PlotBCh1 || in_PlotACh2!=in_PlotBCh2){
         if(ActHist[in_PlotBCh1][in_PlotBCh2]==0){
             firstChanHist=in_PlotBCh1;
             secondChanHist=in_PlotBCh2;
             ActHist[in_PlotBCh1][in_PlotBCh2]=1;
             rc = TDC_addHistogram( firstChanHist, secondChanHist, 1 );
             checkRc( "TDC_addHistogram", rc );
         }
     }
    if((HIST_BINWIDTH!= HIST_BINWIDTH_out || HIST_BINCOUNT!=HIST_BINCOUNT_out) && HIST_BINWIDTH>1){
      HIST_BINWIDTH_out= HIST_BINWIDTH;
      HIST_BINCOUNT_out = HIST_BINCOUNT;
      rc = TDC_setHistogramParams( HIST_BINWIDTH_out, HIST_BINCOUNT_out );
      checkRc( "TDC_setHistogramParams", rc );

    }

    //////////////fix the delay////////////

    //std::cout<<in_PlotACh1 <<std::endl;
    for (int i=0;i<5;i++) {
        if(i==in_PlotACh1 || i==in_PlotBCh1)delays[i]=in_histStart;
        else delays[i]=0;
        std::cout<<delays[i]<<"   ";

    }
    std::cout<<std::endl;
    rc = TDC_setChannelDelays(delays);
    checkRc( "TDC_setChannelDelays", rc );

    //filterset();


     paramschange=false;
    std::cout<<" paramschange  :  "<<  paramschange<<std::endl;

 }

 void qutagadq::changThreshold(int ch, double val){

     rc = TDC_configureSignalConditioning(ch, SCOND_MISC, RoF[ch], val);
     checkRc( "TDC_configureSignalConditioning", rc );

 }


