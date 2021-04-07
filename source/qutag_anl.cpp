#include <qutag_anl.h>



#define SLEEP(x) usleep(x)






qutaganl::qutaganl(){

//events.reserve(TIMESTAMP_COUNT+1);

Hist1start=1;
Hist2start=1;
Hist1end=800;
Hist2end=800;

//Chang_anlAvilable(true);

//file.open("dataTest.csv");

}

void qutaganl::run(){

previouskey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
updateConditions();
emit(Chang_anlAvilable(true));
}


/*void qutaganl::print_event(int EVT, int CLOCK){
    printf("Event number %d \n", EVT);
    printf("***************************************************** \n");


}*/


void qutaganl::clear_events()
{

}

/*void qutaganl::print_deltavector(std::vector< std::pair <Int64,int> > VECTOR, int LENGTHTOPRINT){
    for (i = 0; i < VECTOR.size(); i++){
        printf("%18" PRId64 "     %d \n", VECTOR[i].first, VECTOR[i].second);
        fflush(stdout);
        if (i>LENGTHTOPRINT) break;
    }
}
*/

qutaganl::~qutaganl(){
//file.close();
}

void qutaganl::timestampANL(const vectorInt64 &vectorTimetags, const vectorInt8 &vectorChannels, int tsvalid){

    emit(Chang_anlAvilable(false));
    anlbusy=true;

    int j;
//std::cout<<"tsvalid  :"<<tsvalid<<std::endl;
   // double prevclk;
    for ( int i=0 ; i<tsvalid; i++) {
            ChannelIndex = int(vectorChannels[i]);
            if(ChannelIndex == in_startChan){
                j=i+1;
                if(j>=tsvalid)break; // do not allow the pointer go outside the allocated memory
                StopIndex=int(vectorChannels[j]);
                //if(i<50)std::cout<<"clock cycle"<<std::endl;
                while(StopIndex!=in_startChan){
                    //std::cout<<(int)vectorChannels[j]<<std::endl;
                    diffh = vectorTimetags[j]-vectorTimetags[i];
                   //if(i<50)std::cout<<"channel " <<(int)vectorChannels[i]<<" and " <<(int)vectorChannels[j]<<"   |||   diff  "<<diffh+in_histStart<<std::endl;
                            for (int ii=0; ii<6; ii++) {//over the 5 curves of tab2
                                for (int jj=0; jj<2; jj++) {//check the condition of at one side of the &
                                    //if(ii<3 || (ii==4 && jj==1)){
                                   //if(ii==4 && jj==1) std::cout<<"tab 2 plot   :  "<<tab2_plot[ii][jj]<<std::endl;
                                        if(tab2_plot[ii][jj] == 0 && StopIndex == in_PlotACh2){
                                            if(diffh+in_histStart>tab2_ranges[ii][jj][0] && diffh+in_histStart<tab2_ranges[ii][jj][1])flag[ii][jj]=true;
                                            //if(i<50)if(ii==0) std::cout<<"ranges  :"<<tab2_ranges[ii][jj][0]<<"   "<<tab2_ranges[ii][jj][1]<<"  \\  "<< diffh+in_histStart<<"   "<<jj<<std::endl;
                                        }
                                        if(tab2_plot[ii][jj] == 1 && StopIndex == in_PlotBCh2){
                                            if(diffh+in_histStart>tab2_ranges[ii][jj][0] && diffh+in_histStart<tab2_ranges[ii][jj][1])flag[ii][jj]=true;
                                            //if(i<50)if(ii==0) std::cout<<"ranges  :"<<tab2_ranges[ii][jj][0]<<"   "<<tab2_ranges[ii][jj][1]<<"  \\  "<< diffh+in_histStart<<"   "<<jj<<std::endl;
                                        }
                                        if(tab2_plot[ii][jj] == 2 && StopIndex == in_PlotCCh2){
                                            if(diffh+in_histStart>tab2_ranges[ii][jj][0] && diffh+in_histStart<tab2_ranges[ii][jj][1])flag[ii][jj]=true;
                                            //if(i<50)if(ii==0) std::cout<<"ranges  :"<<tab2_ranges[ii][jj][0]<<"   "<<tab2_ranges[ii][jj][1]<<"  \\  "<< diffh+in_histStart<<"   "<<jj<<std::endl;
                                        }

                                   // }

                                }
                               // if(i<50)if(ii==0)std::cout<<flag[ii][0]<<"    "<<flag[ii][1]<<std::endl;
                            }

                    j++;
                    if(j>=tsvalid)break;
                    StopIndex=int(vectorChannels[j]);
                }
                flag[3][0]= flag[ tab2_plot[3][0] ][0] && flag[tab2_plot[3][0]][1];
                flag[3][1]= flag[ tab2_plot[3][1] ][0] && flag[tab2_plot[3][1]][1];
                flag[4][0]= flag[3][0] || flag[3][1];
                flag[5][0]= flag[3][0] || flag[3][1];

                for (int ii=0; ii<6; ii++) {//over the 3 curves of tab2
                     if(ii!=3)if(flag[ii][0] && flag[ii][1])counterplot[ii]++;
                     if(ii==3)if(flag[ii][0] || flag[ii][1])counterplot[ii]++;
                     //if(ii==4)if(flag[ii][1])counterplot[ii]++;
                     //if(i<50)if(ii==0)std::cout<<"------------------"<<std::endl;
                    }

                for (int ii=0; ii<6; ii++) {//over the 3 curves of tab2
                     flag[ii][0]=0;flag[ii][1]=0;

                    }
            }
        }



    key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    if(!borrame){firstkey=key;borrame=true;}

    if(key-previouskey>adqtime_2){

    emit rates_tab2(counterplot[0], counterplot[1], counterplot[2], counterplot[3], counterplot[4], counterplot[5], key);
        //std::cout<<key-firstkey<<std::endl;
         //file<<counterplot[0]<<","<<counterplot[1]<<","<<counterplot[2]<<","<<key-firstkey<<std::endl;
         //std::cout <<counterplot[0]<<","<<counterplot[1]<<","<<counterplot[2]<<","<<key-firstkey<<std::endl;
        for (int i=0; i<6; i++)counterplot[i]=0;
        previouskey=key;

    }


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
    for (int ii=0; ii<6; ii++) {//recorro los graficos
        for (int jj=0; jj<2; jj++) {//recorro A & B
            for (int k=0 ;k<2;k++) {//recorro inicio o fin
                if(ii<3 || (ii==4 && jj==1) || (ii==5 && jj==1) )tab2_ranges[ii][jj][k] = Plot_Win_BoE[ tab2_plot[ii][jj] ][ tab2_win[ii][jj] ][k];
                //if(ii==4 && jj==1)tab2_ranges[ii][jj][k] = Plot_Win_BoE[ tab2_plot[ii][jj] ][ tab2_win[ii][jj] ][k];

            }
        }
    }
}
