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
    histodataA=nullptr;
    histodataB=nullptr;
    histodataC=nullptr;
    anlAvilable=false;
    HIST_BINWIDTH=10;
    HIST_BINCOUNT=100;

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

    ///////////////initial thresholds and edges/////////////
    int temp_edge[1];
    double temp_thresh[1];
    rc = TDC_getSignalConditioning(1, temp_edge,temp_thresh);
    checkRc( "TDC_getSignalConditioning", rc );
    std::cout<<" ch1 edge : "<<*temp_edge<<"\t thresh"<<*temp_thresh<<std::endl;
    thresholds[1] = *temp_thresh;
    RoF[1] = bool(*temp_edge);
    rc = TDC_getSignalConditioning(2, temp_edge,temp_thresh);
    std::cout<<" ch2 edge : "<<*temp_edge<<"\t thresh"<<*temp_thresh<<std::endl;
    thresholds[2] = *temp_thresh;
    RoF[2] = bool(*temp_edge);
    rc = TDC_getSignalConditioning(3, temp_edge,temp_thresh);
    std::cout<<" ch3 edge : "<<*temp_edge<<"\t thresh"<<*temp_thresh<<std::endl;
    thresholds[3] = *temp_thresh;
    RoF[3] = bool(*temp_edge);
    rc = TDC_getSignalConditioning(4, temp_edge,temp_thresh);
    std::cout<<" ch4 edge : "<<*temp_edge<<"\t thresh"<<*temp_thresh<<std::endl;
    thresholds[4] = *temp_thresh;
    RoF[4] = bool(*temp_edge);


    /////////////filters//////

    TDC_FilterType temp_filtertype[1];
    Int32 temp_channelmask[1];
    rc = TDC_getFilter(1, temp_filtertype, temp_channelmask);
    filtertype[1]= *temp_filtertype;
    ch_filtermask[1] = *temp_channelmask;

    rc = TDC_getFilter(2, temp_filtertype, temp_channelmask);
    filtertype[2]= *temp_filtertype;
    ch_filtermask[2] = *temp_channelmask;

    rc = TDC_getFilter(3, temp_filtertype, temp_channelmask);
    filtertype[3]= *temp_filtertype;
    ch_filtermask[3] = *temp_channelmask;

    rc = TDC_getFilter(4, temp_filtertype, temp_channelmask);
    filtertype[4]= *temp_filtertype;
    ch_filtermask[4] = *temp_channelmask;

    loadtdcfiltertype();


    //std::cout<<"ADQ  rof"<<RoF[1]<<"rof"<<RoF[2]<<"rof"<<RoF[3]<<"rof"<<RoF[4]<<std::endl;


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

    fflush(stdout);

    rc = TDC_enableStartStop( 1 );
    checkRc( "TDC_enableStartStop", rc );


}

void qutagadq::run(){

lautrun();

}

/* Check return code and exit on error */
void qutagadq::checkRc( const char * fctname, int rc ){
  //std::cout<<"function: "<<fctname<< "     rc = "<<rc<<std::endl;
  if ( rc ) {
    printf("error\n");
    printf( ">>> %s: %s\n", fctname, TDC_perror( rc ) );
    QString errormessage= "error >>>" + QString(fctname) + ": " + QString(TDC_perror( rc ));
    if(rc == TDC_NotConnected)emit TDCerror("TDC not initialized, is disconnected or another instance is running");
    else emit TDCerror(errormessage);
    break_=true;
  }
}


 void qutagadq::adqui(){

}



 qutagadq::~qutagadq(){

TDC_deInit();

 }


/*
int qutagadq::filterset(){

    int maskA=0x00 , maskB=0x00, maskC=0x00;

    maskA|=0x1<<(in_PlotACh2);
    maskA|=0x1<<(in_startChan);

    maskB|=0x1<<(in_PlotBCh1);
    maskB|=0x1<<(in_startChan);

    maskC|=0x1<<(in_PlotACh2);
    maskC|=0x1<<(in_PlotBCh2);
    maskC|=0x1<<(in_PlotCCh2);
    //maskC|=0x1<<(in_startChan);

    std::cout<<"filter channel : "<<in_startChan<<"  , mask : "<<maskC<<std::endl;
    std::cout<<"filter channel : "<<in_PlotACh2<<"  , mask : "<<maskA<<std::endl;
    std::cout<<"filter channel : "<<in_PlotBCh2<<"  , mask : "<<maskB<<std::endl;
    //rc = TDC_configureFilter(in_startChan, FILTER_SYNC , maskC);
    //checkRc( "TDC_configureFilter clock", rc );
    rc = TDC_configureFilter(in_PlotACh2, FILTER_NONE, maskA);
    checkRc( "TDC_configureFilter mask A", rc );
    rc = TDC_configureFilter(in_PlotBCh2, FILTER_NONE, maskB);
    checkRc( "TDC_configureFilter mask B", rc );
    rc = TDC_configureFilter(in_PlotCCh2, FILTER_NONE, maskB);
    checkRc( "TDC_configureFilter mask B", rc );

    return 0;
}
*/

 void qutagadq::lautrun(){
    setHistograms();

  TDC_clearAllHistograms ();

  //Int32 coincWin = in_histEnd-in_histStart;
  //rc =TDC_setCoincidenceWindow(coincWin);
  //checkRc( "TDC_enableStartStop", rc );
    double previous_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    double current_time;

     while(!break_ && !rc){
         current_time = QDateTime::currentDateTime().toMSecsSinceEpoch();
        // std::cout<< current_time-previous_time <<std::endl;
         if((current_time-previous_time) > 1000*in_adqtime){           
             getHisto();//TDC_clearAllHistograms ();
             previous_time = current_time;
         }
         if(anlAvilable)getTimeStamps();
         QThread::msleep(10);

     }
    std::cout<<"adq thread broke"<<std::endl;
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

     if (histodataC != 0) {
         delete [] histodataC;
     }

     histodataC = new Int32 [in_binsinplot];

    /* std::cout<<"binsinplot adq  :  "<< in_binsinplot<<std::endl;
     std::cout<<"plot 1A  :  "<< in_PlotACh1<<std::endl;
     std::cout<<"plot 2A  :  "<< in_PlotACh2<<std::endl;
*/
     if(in_PlotACh1>=HIST_CH_MIN && in_PlotACh2>=HIST_CH_MIN && in_PlotACh1<=HIST_CH_MAX && in_PlotACh2<=HIST_CH_MAX
             && ActHist[in_PlotACh1][in_PlotACh2]==1){
         // Retreive and print selected start stop histogram
         if(in_PlotACh1==in_PlotBCh1 && in_PlotACh2==in_PlotBCh2 )
           rc = TDC_getHistogram(in_PlotACh1, in_PlotACh2, 0, histodataA, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );
         else rc = TDC_getHistogram(in_PlotACh1, in_PlotACh2, 1, histodataA, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );

           checkRc( "TDC_getHistogram A", rc );


            count1=count;

           dataA.resize(in_binsinplot);

           for (int i=0; i<in_binsinplot; ++i){

               dataA[i]=double(histodataA[i]);
           }


          /* std::cout<<"in_binsinplot  :  "<< in_binsinplot<<std::endl;
           std::cout<<"plot 1B  :  "<< in_PlotBCh1<<std::endl;
            std::cout<<"plot 2B  :  "<< in_PlotBCh2<<std::endl;*/
    }
     if(in_PlotBCh1>=HIST_CH_MIN && in_PlotBCh2>=HIST_CH_MIN && in_PlotBCh1<=HIST_CH_MAX && in_PlotBCh2<=HIST_CH_MAX
             && ActHist[in_PlotBCh1][in_PlotBCh2]==1){
           if(in_PlotCCh1==in_PlotBCh1 && in_PlotCCh2==in_PlotBCh2)
               rc = TDC_getHistogram(in_PlotBCh1, in_PlotBCh2, 0, histodataB, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );
           else rc = TDC_getHistogram(in_PlotBCh1, in_PlotBCh2, 1, histodataB, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );
           checkRc( "TDC_getHistogram B", rc );


           count2=count;

           dataB.resize(in_binsinplot);

           for (int i=0; i<in_binsinplot; ++i){

               dataB[i]=double( histodataB[i] );
           }

        }

     if(in_PlotCCh1>=HIST_CH_MIN && in_PlotCCh2>=HIST_CH_MIN && in_PlotCCh1<=HIST_CH_MAX && in_PlotCCh2<=HIST_CH_MAX
             && ActHist[in_PlotCCh1][in_PlotCCh2]==1){
            //std::cout<<"in_PlotCCh1= "<<in_PlotCCh1<<"     in_PlotCCh2 = "<<in_PlotCCh2<<std::endl;
           rc = TDC_getHistogram(in_PlotCCh1, in_PlotCCh2, 1, histodataC, &count, &tooSmall, &tooBig, &eventsA, &eventsB, &expTime );
           checkRc( "TDC_getHistogram C", rc );


           count3=count;

           dataC.resize(in_binsinplot);

           for (int i=0; i<in_binsinplot; ++i){

               dataC[i]=double (histodataC[i]);
           }
        }
//std::cout<<count1<<"  "<<count2<<"  "<< count3<<std::endl;
       if(count1 != 0 || count2 !=0 || count3 !=0)emit(qutaghist(dataA, dataB, dataC));

       dataA.clear();
       dataB.clear();
       dataC.clear();
 }


 void qutagadq::getTimeStamps(){
     //std::cout<<"gettimestanmps"<<std::endl;
     timetags.clear();channelsTDC.clear();
     rc = TDC_getLastTimestamps( 1, timestamps, channels, &tsValid );
     checkRc( "TDC_getLastTimestamps", rc );
     std::copy(timestamps, timestamps + tsValid, std::back_inserter(timetags));
     std::copy(channels, channels + tsValid, std::back_inserter(channelsTDC));     
     if(tsValid>0 && anlAvilable){
        // QThread::msleep(1);



         /*for ( int i=0; i < 20; i++ ) {
         //   printf("channel original:  %hd",channels[i]);
           std::cout<<"     channel :"<<(int)channels[i]<<"\t TTS: "<<timestamps[i]<<"       "<<timestamps[i+1]-timestamps[i]<<std::endl;
         }*/
        emit dataready(timetags, channelsTDC, int(tsValid));
     }
//std::cout<<"gethisto5"<<std::endl;
 }

 void qutagadq::setHistograms(){


     /////////calculate histogram parameters///////////

     HIST_BINWIDTH=in_binWidth;
     HIST_BINCOUNT=in_binsinplot;


     //std::cout<<"HIST_BINWIDTH  :  "<< HIST_BINWIDTH<<std::endl;
    // std::cout<<"HIST_BINCOUNT  :  "<< HIST_BINCOUNT<<std::endl;
     //std::cout<<"HIST_BINWIDTH  *  HIST_BINCOUNT  :  "<< HIST_BINWIDTH*HIST_BINCOUNT<<std::endl;
     bin2ns = HIST_BINWIDTH * timeBase * 1.e9;

     /////////////create the histograms on the FPGA only if is necesary/////////////

    // std::cout<<"A1: "<<in_PlotACh1<<", A2: "<<in_PlotACh2<<", B1: "<<in_PlotBCh1<<", B2: "<<in_PlotBCh2<<", C1: "<<in_PlotCCh1<<", C2: "<<in_PlotCCh2<<std::endl;
    if(in_PlotACh1>=HIST_CH_MIN && in_PlotACh2>=HIST_CH_MIN && in_PlotACh1<=HIST_CH_MAX && in_PlotACh2<=HIST_CH_MAX){
         if(ActHist[in_PlotACh1][in_PlotACh2]==0){
             firstChanHist=in_PlotACh1;
             secondChanHist=in_PlotACh2;
             ActHist[in_PlotACh1][in_PlotACh2]=1;
             std::cout<<"add hist A: "<<in_PlotACh1<<" and "<< in_PlotACh2<<std::endl;
             rc = TDC_addHistogram( firstChanHist, secondChanHist, 1 );
             checkRc( "TDC_addHistogram", rc );

         }
       }


    if(in_PlotBCh1>=HIST_CH_MIN && in_PlotBCh2>=HIST_CH_MIN && in_PlotBCh1<=HIST_CH_MAX && in_PlotBCh2<=HIST_CH_MAX){
         if(ActHist[in_PlotBCh1][in_PlotBCh2]==0){
             firstChanHist=in_PlotBCh1;
             secondChanHist=in_PlotBCh2;
             ActHist[in_PlotBCh1][in_PlotBCh2]=1;
             std::cout<<"add hist B: "<<in_PlotBCh1<<" and "<< in_PlotBCh2<<std::endl;
             rc = TDC_addHistogram( firstChanHist, secondChanHist, 1 );
             checkRc( "TDC_addHistogram", rc );
         }
       }
    if(in_PlotCCh1>=HIST_CH_MIN && in_PlotCCh2>=HIST_CH_MIN && in_PlotCCh1<=HIST_CH_MAX && in_PlotCCh2<=HIST_CH_MAX){
         if(ActHist[in_PlotCCh1][in_PlotCCh2]==0){
             firstChanHist=in_PlotCCh1;
             secondChanHist=in_PlotCCh2;
             ActHist[in_PlotCCh1][in_PlotCCh2]=1;
             std::cout<<"add hist C: "<<in_PlotACh1<<" and "<< in_PlotCCh2<<std::endl;
             rc = TDC_addHistogram( firstChanHist, secondChanHist, 1 );
             checkRc( "TDC_addHistogram", rc );
         }
     }

     /*rc = TDC_addHistogram( in_PlotACh1, in_PlotACh2, 1 );
     checkRc( "TDC_addHistogram", rc );
     rc = TDC_addHistogram(in_PlotBCh1, in_PlotBCh2, 1 );
     checkRc( "TDC_addHistogram", rc );
     rc = TDC_addHistogram( in_PlotCCh1, in_PlotCCh2, 1 );
     checkRc( "TDC_addHistogram", rc );*/

    if((HIST_BINWIDTH!= HIST_BINWIDTH_out || HIST_BINCOUNT!=HIST_BINCOUNT_out) && HIST_BINWIDTH>=1){
      HIST_BINWIDTH_out= HIST_BINWIDTH;
      HIST_BINCOUNT_out = HIST_BINCOUNT;
      std::cout<<"HIST_BINWIDTH  :  "<< HIST_BINWIDTH_out<<std::endl;
      std::cout<<"HIST_BINCOUNT  :  "<< HIST_BINCOUNT_out<<std::endl;
      rc = TDC_setHistogramParams( HIST_BINWIDTH_out, HIST_BINCOUNT_out );
      checkRc( "TDC_setHistogramParams", rc );

    }

    //////////////fix the delay////////////

    //std::cout<<in_PlotACh1 << "||||||||"<<in_PlotACh1 <<std::endl;
  /*  for (int i=0;i<5;i++) {
        if(i==in_PlotACh1 || i==in_PlotBCh1|| i==in_PlotCCh1)delays[i]=in_histStart;
        else delays[i]=0;
        std::cout<<delays[i]<<"   ";

    }
    std::cout<<std::endl;
    rc = TDC_setChannelDelays(delays);
    checkRc( "TDC_setChannelDelays", rc );
*/



     paramschange=false;
    //std::cout<<" paramschange  :  "<<  paramschange<<std::endl;

 }

 void qutagadq::changThreshold(int ch){

     rc = TDC_configureSignalConditioning(ch, SCOND_MISC, RoF[ch], thresholds[ch]);
     checkRc( "TDC_configureSignalConditioning", rc );

 }

 void qutagadq::set_delays(){
     rc = TDC_setChannelDelays(delays);
     checkRc( "TDC_setChannelDelays", rc );
 }

 void qutagadq::loadtdcfiltertype(){

     for (int i =0; i<5;i++) {
         if(filtertype[i]==FILTER_NONE)filtertypeSTR[i]="NONE";
         if(filtertype[i]==FILTER_MUTE)filtertypeSTR[i]="MUTE";
         if(filtertype[i]==FILTER_COINC)filtertypeSTR[i]="COINC";
         if(filtertype[i]==FILTER_SYNC)filtertypeSTR[i]="SYNC";
         if(filtertype[i]==FILTER_INVALID)filtertypeSTR[i]="INVALID";
         std::cout<<filtertypeSTR[i].toStdString()<<std::endl;
     }

 }
 void qutagadq::updatefiltertype(int ch){
    for (int i =0; i<5;i++) {
        if(filtertypeSTR[i]=="NONE")filtertype[i]=FILTER_NONE;
        if(filtertypeSTR[i]=="MUTE")filtertype[i]=FILTER_MUTE;
        if(filtertypeSTR[i]=="COINC")filtertype[i]=FILTER_COINC;
        if(filtertypeSTR[i]=="SYNC")filtertype[i]=FILTER_SYNC;
    }
    setfilter(ch);
 }

 void qutagadq::setfilter(int ch){
     rc = TDC_configureFilter(ch, filtertype[ch] , ch_filtermask[ch]);
     checkRc( "TDC_configureFilter", rc );
 }
