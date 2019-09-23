#include <qutag_anl.h>



#define SLEEP(x) usleep(x)






qutaganl::qutaganl(){

events.reserve(TIMESTAMP_COUNT+1);
anlclock = 1;

Hist1start=1;
Hist2start=1;
Hist1end=800;
Hist2end=800;


file.open("dataTest.csv");

}

void qutaganl::run(){

 updateConditions();
emit(Chang_anlAvilable(true));
}


/*void qutaganl::clockchange(int clockchannel)
{
    anlclock = clockchannel;
    printf("anl knows clock is: %d \n", anlclock);
    fflush(stdout);

}
*/
void qutaganl::print_event(int EVT, int CLOCK){
    printf("Event number %d \n", EVT);
    printf("***************************************************** \n");
    /* not a priority
    switch(CLOCK){

    case 1:
        clock1 = "*****clock*****";
        clock2 = "               ";
        clock3 = "               ";
        clock4 = "               ";
    case 2:
        clock1 = "               ";
        clock2 = "*****clock*****";
        clock3 = "               ";
        clock4 = "               ";
    case 3:
        clock1 = "               ";
        clock2 = "               ";
        clock3 = "*****clock*****";
        clock4 = "               ";
    case 4:
        clock1 = "               ";
        clock2 = "               ";
        clock3 = "               ";
        clock4 = "*****clock*****";
    }
    printf("%s %s %s %s", clock1, clock2, clock3, clock4);

    */
    for (tg = 0; tg < TAGPCLOCK; tg++){
        for (ch = 0; ch < 4; ch++){
            printf("%17" PRId64 "     ", events[EVT][ch][tg]);
        }
        printf("\n");
    }
    printf("***************************************************** \n");

}


void qutaganl::clear_events()
{
    for(evt = 0; evt < TIMESTAMP_COUNT; evt++){
        for(ch = 0; ch < 4; ch++){
            for(tg = 0; tg < TAGPCLOCK; tg++){
                events[evt][ch][tg] = -1;
            }
        }
    }
evt = 0;
ch = 0;
tg = 0;
}


void qutaganl::generate_deltavector(int CHAN, int CLOCK, int TOTALEVENTS){
    //do clock tags usually occur only once per event?
    deltavector.clear();
    clocksum = 0;
    for (evt = 0; evt < 20; evt++){
        for (tg = 0; tg < 10; tg++){
            if (events[evt][CLOCK - 1][tg] != -1){
                clocksum++;
            }
        }
    }
    if (clocksum/20 > 2){
        printf("ERROR: more than 1 clock per event \n");
        return;
    }

    for (evt = 0; evt < TOTALEVENTS; evt++){
        clocksum = 0;
        for (tg = 0; tg < TAGPCLOCK; tg++){
            if (events[evt][CLOCK - 1][tg] != -1){
                clocksum++;
            }
        }
        if (clocksum != 1){
            printf("bad event \n");
            printf("clocksum is: %d", clocksum);
            continue;
        }
        else{
            for (tg = 0; tg < TAGPCLOCK; tg++){
                if (events[evt][CHAN - 1][tg] != -1){
                    //        *event*                   -         *clock*
                    delta = events[evt][CHAN - 1][tg] - events[evt][CLOCK - 1][0];
                    deltavector.push_back(std::make_pair( delta, evt ));
                }
            }

        }
    }



}


void qutaganl::print_deltavector(std::vector< std::pair <Int64,int> > VECTOR, int LENGTHTOPRINT){
    for (i = 0; i < VECTOR.size(); i++){
        printf("%18" PRId64 "     %d \n", VECTOR[i].first, VECTOR[i].second);
        fflush(stdout);
        if (i>LENGTHTOPRINT) break;
    }
}






qutaganl::~qutaganl(){
file.close();
}

void qutaganl::timestampANL(const vectorInt64 &vectorTimetags, const vectorInt8 &vectorChannels, int tsvalid){

    emit(Chang_anlAvilable(false));
   ///////////////////
////int xtime;/////
 ////   float adqtime_tab2;
 ////   int plot1_1, plot1_2, plot2_1, plot2_2, plot3_1, plot3_2;
////  int win1_1, win1_2, win2_1, win2_2, win3_1, win3_2;
 ////    int counterplot1=0, counterplot2=0, counterplot3=0;
////    int  in_startChan;
  ////  int in_PlotACh1, in_PlotACh2, in_PlotBCh1, in_PlotBCh2;
  /// in_histStart, in_histEnd;
  //////////////////
  ///




std::cout<<"tsvalid  :"<<tsvalid<<std::endl;


    for ( int i=0 ; i<tsvalid; i++) {
        ChannelIndex = (int)vectorChannels[i];
        if(ChannelIndex == in_startChan){
            j=i+1;
            StopIndex=(int)vectorChannels[j];
            while(StopIndex!=in_startChan){
                //std::cout<<(int)vectorChannels[j]<<std::endl;
                diffh = vectorTimetags[j]-vectorTimetags[i];
                //if(i<30)std::cout<<"diff  "<<diffh<<std::endl;
                if(diffh>in_histStart && diffh<in_histEnd){
                        for (int ii=0; ii<3; ii++) {//recorro los graficos
                            for (int jj=0; jj<2; jj++) {//recorro A & B
                               if(tab2_plot[ii][jj] == 0 && StopIndex == in_PlotACh2){

                                    if(diffh>tab2_ranges[ii][jj][0] && diffh<tab2_ranges[ii][jj][1])flag[jj]=true;
                                }
                                if(tab2_plot[ii][jj] == 1 && StopIndex == in_PlotBCh2){
                                    if(diffh>tab2_ranges[ii][jj][0] && diffh<tab2_ranges[ii][jj][1])flag[jj]=true;
                                }
                            }
                            if(flag[0]&&flag[1])counterplot[ii]++;
                            flag[0]=false;flag[1]=false;
                        }
                //if(diffh>tab2_ranges[0][0][0] && diffh<tab2_ranges[0][0][1])std::cout<<diffh<<std::endl;
                //if(flag[0])counterplot[0]++;
                //flag[0]=false;
                }
                j++;
                StopIndex=(int)vectorChannels[j];
            }
        }
    }

    std::cout<<counterplot[0]<<"\t"<<counterplot[1]<<"\t"<<counterplot[2]<<std::endl;
    counterplot[0]=0;counterplot[1]=0;counterplot[2]=0;
   /*if(tsvalid>100){
        for ( int i=startindex; i < 100; i++ ) {
            if(vectorChannels[i]==in_startChan)i=localstart;

           if(vectorChannels[i]==in_PlotACh2){
                std::cout<<"channel :"<<(int)vectorChannels[i]<<"\t TTS: "<<vectorTimetags[i]-vectorTimetags[localstart]<<std::endl;
            }
        }
    }*/

/*for ( int i=0; i < 20; i++ ) {
        std::cout<<"channel :"<<(int)vectorChannels[i]<<"\t TTS: "<<vectorTimetags[i]<<std::endl;
    }*/

/*for ( int i=0; i < 20; i++ ) {
        std::cout<<"channel :"<<(int)vectorChannels[i]<<"\t TTS: "<<vectorTimetags[i]<<std::endl;
        file<<(int)vectorChannels[i]<<","<<vectorTimetags[i]<<std::endl;
    }
*/

    emit(Chang_anlAvilable(true));
}







void qutaganl::updateConditions(){
    for (int i=0; i<3; i++) {//recorro los graficos
        for (int j=0; j<2; j++) {//recorro A & B
            for (int k=0 ;k<2;k++) {//recorro inicio o fin
                tab2_ranges[i][j][k] = Plot_Win_BoE[ tab2_plot[i][j] ][ tab2_win[i][j] ][k];
            }

        }
    }

}
