#include <qutag_anl.h>



#define SLEEP(x) usleep(x)






qutaganl::qutaganl(){

events.reserve(TIMESTAMP_COUNT+1);
anlclock = 1;

Hist1start=1;
Hist2start=1;
Hist1end=800;
Hist2end=800;

//Chang_anlAvilable(true);

file.open("dataTest.csv");

}

void qutaganl::run(){

previouskey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
updateConditions();
emit(Chang_anlAvilable(true));
}


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
    anlbusy=true;


std::cout<<"tsvalid  :"<<tsvalid<<std::endl;

    for ( int i=0 ; i<tsvalid; i++) {
            ChannelIndex = (int)vectorChannels[i];
            if(ChannelIndex == in_startChan){
                j=i+1;
                if(j>=tsvalid)break; // do not allow the pointer go outside the allocated memory
                StopIndex=(int)vectorChannels[j];

                while(StopIndex!=in_startChan){
                    //std::cout<<(int)vectorChannels[j]<<std::endl;
                    diffh = vectorTimetags[j]-vectorTimetags[i];
                   // if(i<50)std::cout<<"channel " <<(int)vectorChannels[i]<<" and " <<(int)vectorChannels[j]<<"   |||   diff  "<<diffh+in_histStart<<std::endl;
                    //if(diffh+in_histStart>in_histStart && diffh+in_histStart<in_histEnd){
                            for (int ii=0; ii<3; ii++) {//over the 3 curves of tab2
                                for (int jj=0; jj<2; jj++) {//check the condition of at one side of the &
                                   if(tab2_plot[ii][jj] == 0 && StopIndex == in_PlotACh2){
                                        if(diffh+in_histStart>tab2_ranges[ii][jj][0] && diffh+in_histStart<tab2_ranges[ii][jj][1])flag[ii][jj]=true;
                                        //if(i<50)if(ii==0) std::cout<<"ranges  :"<<tab2_ranges[ii][jj][0]<<"   "<<tab2_ranges[ii][jj][1]<<"  \\  "<< diffh+in_histStart<<"   "<<jj<<std::endl;
                                        //std::cout<<flag[jj]<<std::endl;
                                    }
                                    if(tab2_plot[ii][jj] == 1 && StopIndex == in_PlotBCh2){
                                        if(diffh+in_histStart>tab2_ranges[ii][jj][0] && diffh+in_histStart<tab2_ranges[ii][jj][1])flag[ii][jj]=true;
                                        //if(i<50)if(ii==0) std::cout<<"ranges  :"<<tab2_ranges[ii][jj][0]<<"   "<<tab2_ranges[ii][jj][1]<<"  \\  "<< diffh+in_histStart<<"   "<<jj<<std::endl;
                                    }
                                }
                               // if(i<50)if(ii==0)std::cout<<flag[ii][0]<<"    "<<flag[ii][1]<<std::endl;

                            }

                    //}

                    j++;
                    if(j>=tsvalid)break;
                    StopIndex=(int)vectorChannels[j];
                }
                for (int ii=0; ii<3; ii++) {//over the 3 curves of tab2
                     if(flag[ii][0] && flag[ii][1])counterplot[ii]++;
                     flag[ii][0]=0;flag[ii][1]=0;
                     //if(i<50)if(ii==0)std::cout<<"------------------"<<std::endl;
                }
            }
        }



    key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    //std::cout<<key-previouskey<<std::endl;

    if(key-previouskey>adqtime_2){
    emit rates_tab2(counterplot[0], counterplot[1], counterplot[2], key);
     counterplot[0]=0;counterplot[1]=0;counterplot[2]=0;
     previouskey=key;
    }
   /*if(tsvalid>100){
        for ( int i=startindex; i < 100; i++ ) {
            if(vectorChannels[i]==in_startChan)i=localstart;tab2_ranges[ii][jj][k]

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
    anlbusy=false;
}


void qutaganl::updateConditions(){
    //while(anlbusy){std::cout<<"quechuchawn:"<<std::endl;}
   emit CombinationChange(true);
    for (int ii=0; ii<3; ii++) {//recorro los graficos
        for (int jj=0; jj<2; jj++) {//recorro A & B
            for (int k=0 ;k<2;k++) {//recorro inicio o fin
                tab2_ranges[ii][jj][k] = Plot_Win_BoE[ tab2_plot[ii][jj] ][ tab2_win[ii][jj] ][k];
            }

        }
    }

}
