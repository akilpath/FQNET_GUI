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

    rc = TDC_setExposureTime( 100 );
    checkRc( "TDC_setExposureTime", rc );


    //rc = TDC_configureFilter(1, FILTER_COINC, 3);
    rc = TDC_configureSignalConditioning(0, SCOND_MISC, 1, .1);
    rc = TDC_configureSignalConditioning(1, SCOND_MISC, 1, .1);
    rc = TDC_configureSignalConditioning(2, SCOND_MISC, 1, .1);
    rc = TDC_configureSignalConditioning(3, SCOND_MISC, 1, .1);
    rc = TDC_configureSignalConditioning(4, SCOND_MISC, 1, .1);
    checkRc( "TDC_configureSignalConditioning", rc );



    //rc = TDC_enableMarkers(0);        //WHY IS THIS NOT WORKING??
    //checkRc( "TDC_enableMarkers", rc);

    //rc = TDC_setExposureTime( EXP_TIME );
    //checkRc( "TDC_setExposureTime", rc );

    rc = TDC_setCoincidenceWindow( 1000000 ); /* 100ns */
    checkRc( "TDC_setCoincidenceWindow", rc );


    SLEEP( 1e3 );
    TDC_getCoincCounters( coincCnt, NULL );
    SLEEP( 1e3 );
    TDC_getCoincCounters( coincCnt, NULL );
    SLEEP(1e6);
    TDC_getCoincCounters( coincCnt, NULL );

    //rc = TDC_configureSignalConditioning(4, SCOND_MISC, 1, .1);

   // TOTAL_RATE = rate(coincCnt[0]+coincCnt[1]+coincCnt[2]+coincCnt[3]+coincCnt[4]);

    ///////////////////LINE commented because definition on .h/////////////////
    //COLLECT_TIME = get_max_collection_time(TOTAL_RATE);/* Time [us] for data acquisition per round */


    //printf("total rate is: %.3f MHz \n", TOTAL_RATE);



    //for(i = 0; i < 100; i++){
    //    TDC_getLastTimestamps( 1, timestamps, channels, &tsValid );
    //    usleep(1);
    //    std::cout << "tsValid is: " << tsValid << "\n";
        //printf("tsValid is: %d \n", tsValid);
        //fflush(stdout);
    //}

    req.tv_sec = 0;
    req.tv_nsec = microsec * 1000L;

    fflush(stdout);

    /*
    if (TOTAL_RATE == 0) {
            printf("\n\nNo signals detected. Exiting...\n\n");
            fflush(stdout);
            TDC_deInit();
            return;
    }
    */

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




 /*void qutagadq::filterconfigure(int clockchannel)
 {
     int masktype = 15; //will be changed depending on clockchannel
     printf("this channel will be filtered: %d \n", clockchannel);
     fflush(stdout);
     // want to use all other channels as masks for whatever channels is used as the clock

     if(clockchannel == 0){masktype = 15;}      //1111 in binary, or use 31 if 5 channels supported
     if(clockchannel == 1){masktype = 14;}      //1110
     if(clockchannel == 2){masktype = 13;}      //1101
     if(clockchannel == 3){masktype = 11;}      //1011
     if(clockchannel == 4){masktype = 7;}       //0111

    TDC_FilterType filtertype;
    Int32 mask = 0;

     //rc = TDC_configureSignalConditioning(2, SCOND_MISC, 1, 0.3);
     //rc = TDC_setFiveChannelMode(1);
     rc = TDC_configureFilter(clockchannel, FILTER_SYNC, masktype);
     checkRc( "TDC_configureFilter", rc );

     printf("intermediate mask type is: %d \n", masktype);
     rc = TDC_getFilter(clockchannel, &filtertype, &mask);
     usleep(1000);
     checkRc( "TDC_getFilter", rc );
     printf("filtertype is: %d and mask type is %d \n", filtertype, mask);

 }*/

int qutagadq::filterset(){

    int maskA=0x00 , maskB=0x00, maskC=0x00;
    maskA|=0x1<<(in_PlotACh2);
    maskA|=0x1<<(in_startChan);
    maskB|=0x1<<(in_PlotBCh2);
    maskB|=0x1<<(in_startChan);
    std::cout<<"filter channel : "<<in_startChan<<"  , mask : "<<maskC<<std::endl;
    std::cout<<"filter channel : "<<in_PlotACh2<<"  , mask : "<<maskA<<std::endl;
    std::cout<<"filter channel : "<<in_PlotBCh2<<"  , mask : "<<maskB<<std::endl;
    rc = TDC_configureFilter(in_startChan+1, FILTER_NONE, maskC);
    checkRc( "TDC_configureFilter clock", rc );
    rc = TDC_configureFilter(in_PlotACh1+1, FILTER_COINC, maskA);
    checkRc( "TDC_configureFilter mask A", rc );
    rc = TDC_configureFilter(in_PlotBCh2+1, FILTER_COINC, maskB);
    checkRc( "TDC_configureFilter mask B", rc );

    return 0;
}




 /*void qutagadq::andrewrun(){

    //filterconfigure(1);

     Int32 tsValidsum = 0;
     begin = clock();
     time_t start_time;
     time_t final_time;

     while(a < 10*4640*10000){

         channelsTDC.clear(); //clear the vectors
         timetags.clear();
         //******************************************
         // main aquisition loop
         //******************************************
         while(adqpause_)usleep(100);




         TDC_getLastTimestamps( 1, timestamps, channels, &tsValid );

         //usleep(2);

         //nanosleep((const struct timespec[]){{0, 20000L}}, NULL);
         tsValidsum = tsValidsum + tsValid;


         if (tsValid != 0){
                 printf("nonzero tsValid is: %ld \n", tsValid);
                 fflush(stdout);
         }
         if (a < 20){
             printf("tsValid is OTHER: %ld \n", tsValid);
             fflush(stdout);
             if (a == 19){
                 printf("\n\n");
             }
         }
         if (a == 1000){
             tsValidsum = 0;
             begin = clock();
             start_time = time(NULL);
         }


         //std::copy(timestamps, timestamps + TIMESTAMP_COUNT, std::back_inserter(timetags));
         //std::copy(channels, channels + TIMESTAMP_COUNT, std::back_inserter(channelsTDC));

         if (tsValid != 0){
             if (tsValid == TIMESTAMP_COUNT){
                 printf("Error: Buffer overflow \n");
                 continue;
             }
             std::copy(timestamps, timestamps + tsValid, std::back_inserter(timetags));
             std::copy(channels, channels + tsValid, std::back_inserter(channelsTDC));
             emit dataready(timetags, channelsTDC, tsValid);

         }
         tsValid = 0;



         //************** debug
         if (debug){
             printf("\n");
             printf("new times: %" PRId64 "\n", timetags[0]);
             printf("lastdata: %" PRId64 "\n", timetags.last());
             printf("timetags length: %d \n", timetags.size());

             printf("new data: %d \n", channelsTDC[0]);
             printf("new data: %d \n", channelsTDC[1]);
             printf("new data: %d \n", channelsTDC[2]);
             printf("last data: %d \n", channelsTDC.last());
             printf("tsValid: %d \n", tsValid);
             printf("\n");
             fflush(stdout);
         }


         //exec();


         /*
         if (notfirstrun){
             if (tsValid <= 2000){
                 sleeptime = int(1.2*sleeptime);
                 if (debug3){
                     printf("going up \n");
                     printf("old tsValid: %d \n", tsValid);
                     printf("new sleeptime: %d \n", sleeptime);
                     fflush(stdout);
                 }
             }

             if (tsValid >= 9000){
                 sleeptime = int(sleeptime/1.2);
                 if (debug3){
                     printf("going down \n");
                     printf("old tsValid: %d \n", tsValid);
                     printf("new sleeptime: %d \n", sleeptime);
                     fflush(stdout);
                 }
             }

             if (tsValid > 2000 && tsValid < 9000){
                 //send data to analysis thread


                 //emit dataready(timetags, channelsTDC, tsValid);

                 //channelsTDC.clear(); //clear the vectors
                 //timetags.clear();
                 //emit finished();
             }

         }





         //notfirstrun = 1;
         //usleep(int(sleeptime));


         //channelsTDC.clear(); //clear the vectors
         //timetags.clear();
         //tsValid = 0;



         a++;
        }

       end = clock();
       cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
       final_time = time(NULL);
       printf("clock delta: %f \n", cpu_time_used);
       printf("tsValidsum is: %ld \n", tsValidsum);
       printf("start actual time is: %ld \n", start_time);
       printf("final actual time is: %ld \n", final_time);
       printf("delta actual time is: %ld \n", final_time - start_time);
       printf("avg timestamps per second is: %ld \n", tsValidsum/(final_time - start_time));
       fflush(stdout);



 }*/


 void qutagadq::lautrun(){
    // setHistograms();

  TDC_clearAllHistograms ();

  //filterset();


     while(!break_){

         getHisto();

         QThread::msleep(1000*in_adqtime);
     }

 }

 void qutagadq::getHisto(){

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

     std::cout<<"binsinplot adq  :  "<< in_binsinplot<<std::endl;
     std::cout<<"plot 1A  :  "<< in_PlotACh1<<std::endl;
     std::cout<<"plot 2A  :  "<< in_PlotACh2<<std::endl;


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


       std::cout<<"in_binsinplot  :  "<< in_binsinplot<<std::endl;
       std::cout<<"plot 1B  :  "<< in_PlotBCh1<<std::endl;
        std::cout<<"plot 2B  :  "<< in_PlotBCh2<<std::endl;


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

 void qutagadq::setHistograms(){

     /////////calculate histogram parameters///////////

     HIST_BINWIDTH=(int)(in_histEnd-in_histStart)/in_binsinplot;
     HIST_BINCOUNT=in_binsinplot;
     filterset();

     std::cout<<"HIST_BINWIDTH  :  "<< HIST_BINWIDTH<<std::endl;
     std::cout<<"HIST_BINCOUNT  :  "<< HIST_BINCOUNT<<std::endl;
     std::cout<<"HIST_BINWIDTH  *  HIST_BINCOUNT  :  "<< HIST_BINWIDTH*HIST_BINCOUNT<<std::endl;
     bin2ns = HIST_BINWIDTH * timeBase * 1.e9;
    //if(filterset() != 0)return;

     /////////////create the histograms on the FPGA only if is necesary/////////////

     if(ActHist[in_PlotACh1][in_PlotACh2]==0){
         firstChanHist=in_PlotACh1;
         secondChanHist=in_PlotACh2;
         ActHist[in_PlotACh1][in_PlotACh2]=1;
         std::cout<<"quewepasahermano  "<<std::endl;
         rc = TDC_addHistogram( firstChanHist, secondChanHist, 1 );
         checkRc( "TDC_addHistogram", rc );
         std::cout<<"quewepasahermano 2 "<<std::endl;
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
