#include <qutag_anl.h>

#include <iostream>//entradas y salidas por consola
#include <fstream>//archivos.txt
#define SLEEP(x) usleep(x)






qutaganl::qutaganl(){

events.reserve(TIMESTAMP_COUNT+1);
anlclock = 1;

Hist1start=1;
Hist2start=1;
Hist1end=800;
Hist2end=800;

}

void qutaganl::run(){



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





void qutaganl::inputdata(const vectorInt64 &TTdata, const channelsTDCPP &CHdata, int nevent){


    //****************** stops program early
    runcounter++;
    printf("run counter is now: %d \n", runcounter);
    fflush(stdout);
    if (runcounter > 10){
        TDC_deInit();
        exit( 1 );
        std::_Exit(0);
    }
    //****************** stops program early

    emit anlongoing(true);

    printf("ANL: tsvalid is: %d \n", nevent);
    if(TTdata.isEmpty()||CHdata.isEmpty())std::cout<<"is empty"<<std::endl;

    else{

            if(TTdata.size() != CHdata.size()) printf("ERROR: time and channel vector mismatch");
            fflush(stdout);


            for(i = 0; i < 20; i++){
                printf("ch data: %d \n", CHdata[i]);
            }
            if (debug){
                printf("firstdata sent: %" PRId64 "\n", TTdata[0]);
                printf("lastdata sent: %" PRId64 "\n", TTdata.last());
                printf("timetags length: %d", TTdata.size());
                printf("\n");



                printf("last data sent: %d \n", CHdata.last());
                printf("tsValid sent: %d \n", nevent);
                fflush(stdout);
            }

            arrindex = 0;
            for(int i = 0; i < TTdata.size(); i++){
                if (arrindex > (AVGLENGTH - 1)){
                    break;
                }
                if (CHdata[i] == anlclock){
                    sampleclocks[arrindex] = TTdata[i];
                    //printf("\n");
                    //printf("tags: %" PRId64 " \n", sampleclocks[arrindex]);
                    arrindex = arrindex + 1;
                }
            }

            for(i = 1; i < AVGLENGTH; i++){
                sampletimediffs[i-1] = sampleclocks[i] - sampleclocks[i-1];
                if (debug){
                    //printf("delta: %" RId64 " \n", sampletimediffs[i-1]);
                }
            }

            sum1 = 0;
            //printf("AVGLLENGTH is: %d", AVG_LENGTH);
            for (int i = 0; i < (AVGLENGTH - 1); i++) {
                sum1 = sum1 + sampletimediffs[i];
                //from 0 to 8: 9 terms
            }

            avgtimediff =   int(sum1/(AVGLENGTH - 1));
            if (debug2){
                printf("avgtimediff is: %d \n", avgtimediff);
            }
            fflush(stdout);

            prevclock = -1;
            evt = 0;
            ch = 0;
            tg = 0;


            clear_events(); //get the vector of 2D arrays ready for data input
            if (debug2){
                printf("rando element of events: %d \n", events[0][0][0]);
                printf("rando element of events: %d \n", events[0][3][0]);
                printf("rando element of events: %d \n", events[0][3][10]);
                printf("rando element of events: %d \n", events[100][2][5]);
                printf("rando element of events: %d \n", events[9000][3][5]);
                printf("rando element of events: %d \n", events[20][3][5]);
            }


            //TTdata.size()

            for( i = 0; i < 100; i++)
            {

                if (debug2){
                    printf("prevclock is: %" PRId64 " \n", prevclock);
                    fflush(stdout);
                }
                // this if statmetn should only pass once, very near the beginning of the for loop
                if (prevclock == -1 && CHdata[i] == anlclock){
                    clocknotfound = 0;
                    prevclock = TTdata[i];
                    init_prevclock = prevclock;
                    begin = prevclock + (avgtimediff/2);
                    // ******** theres are on top of each other
                    end = prevclock + (3*avgtimediff/2);
                    starttag = 1;
                    //you need to go strait to new event
                    if (debug2){
                        printf("        now prevclock is: %" PRId64 " \n", prevclock);
                    }
                }

                if (TTdata[i] < init_prevclock + (avgtimediff/2) || (prevclock == -1)){
                    printf("looking for 1st valid clock \n");
                    clocknotfound++;

                    if(clocknotfound > 100){
                        printf("error: clock not found in datastream. Continuing. \n");
                        //std::_Exit(0);
                    }
                    continue;
                }

                if (debug){
                    printf("some data from CHdata: %d %d %d %d %d \n", CHdata[0],CHdata[1],CHdata[2],CHdata[3], CHdata[4]);
                    fflush(stdout);
                }
                //*************check for unexpected errors:
                if (CHdata[i] < 1 || CHdata[i] > 4){
                    if (debug2){
                        printf("error: Ch not in expected range. Ch is: %d \n", CHdata[i]);
                        fflush(stdout);
                    }
                    continue;       //because we can't turn off markets they should be ignored
                }

                if (TTdata[i] < 1){
                    if (debug2){
                        printf("error: tag not in expected range. Tag is: %" PRId64 " \n", TTdata[i]);
                        fflush(stdout);
                    }
                }
                //*************

                if (debug2){
                    printf("avgtimediff is: %d \n", avgtimediff);
                }
                //end = prevclock + (3*avgtimediff/2);


                if (debug2){
                    printf("\n\n prevclock is: %" PRId64 " and begin is %" PRId64 " and end is %" PRId64 " and current tag is %" PRId64 " \n\n", prevclock, begin, end, TTdata[i]);
                }


                if (TTdata[i] >= end){
                    //new event
                    newevent = 1;
                    //printf("new event \n");
                    fflush(stdout);
                }

                if((TTdata[i] > begin) && (TTdata[i] < end)){

                    if (starttag){
                        newevent = 1;
                        //printf("new event \n");
                    }
                    if (starttag == 0){
                        newevent = 0;
                        if (debug2){
                            printf("continue event \n");
                            fflush(stdout);
                        }
                    }
                }

                if (TTdata[i] <= begin) {
                    printf("ERROR: this shouldnt happen \n");
                }

                if (starttag) newevent = 1;

                if (newevent){
                    if (debug2){
                        printf("evt is: %d and ch is %d and tg is %d \n", evt, ch, tg);
                    }
                    eventsum = 0;
                    for(ch = 0; ch < 4; ch++){
                        for(tg = 0; tg < TAGPCLOCK; tg++){
                            if (events[evt][ch][tg] != -1){

                                eventsum++;
                                if (debug2){
                                    printf(" then what is it: %" PRId64 " or integer: %d \n", events[evt][ch][tg], events[evt][ch][tg]);
                                    printf("eventsum is: %d \n", eventsum);
                                    printf("ch of event is: %d  and time is: %" PRId64 "\n", CHdata[i], TTdata[i]);
                                    fflush(stdout);
                                }
                            }
                        }
                    }
                    //eventsum is the toal number of tags for the current event.
                    //if less than or equal to 1, discard event. This does the same thing as the
                    //filter feature of the qutag

                    if( eventsum <=1) goodevent = 0;



                    if (goodevent){     //index i corresponds to 1st tag of new event. Was previous event good? Check its properties.
                        //identify the clock in this event that should be ready
                        clocksum = 0;
                        for (tg = 0; tg < TAGPCLOCK; tg++){
                            if(events[evt][anlclock - 1][tg] != -1){
                                clocksum++;
                            }
                        }
                        if((events[evt][anlclock - 1][0] != -1) && (clocksum == 1)){
                            //only one clock tag should exist in this event at position tg = 0
                            prevclock = events[evt][anlclock - 1][0];
                            begin = prevclock + (avgtimediff/2);
                            end = prevclock + (3*avgtimediff/2);

                            print_event(evt, anlclock);

                            if (debug2){
                                printf("generating multiple events. Final event has sum: %d \n", eventsum);
                                fflush(stdout);
                            }
                            evt++; //move onto next event

                        }
                    }
                    //if we didn't finsih up a good event above, then there is one or less tags currently in the event.
                    //Clear the event and put in first tag of new data
                    //clear event
                    goodevent = 1;
                    for(ch = 0; ch < 4; ch++){
                        for(tg = 0; tg < TAGPCLOCK; tg++){
                            events[evt][ch][tg] = -1;
                        }
                    }

                    if (debug2){
                        printf("first data: ch is %d and time is %" PRId64 " and evt is: %d \n", CHdata[i], TTdata[i], evt);
                        fflush(stdout);
                    }
                    tg = 0;

                    if(events[evt][CHdata[i] - 1][tg] == -1){
                        events[evt][CHdata[i] - 1][tg] = TTdata[i];
                        starttag = 0;
                    }

                }
                else{
                    for(tg = 0; tg < TAGPCLOCK; tg++){
                        if(events[evt][CHdata[i] - 1][tg] == -1){
                            if(tg > 0){
                                if (debug2){
                                    printf("putting more than 2nd tag in this event \n");
                                    fflush(stdout);
                                }
                            }
                            events[evt][CHdata[i] - 1][tg] = TTdata[i];
                            break; //only need to put in new tag once. Exit loop once put in.

                        }
                    }


                }
            }

            totalevents = evt + 1;  //because there is an event for evt = 0
            generate_deltavector(2, anlclock, totalevents);
            print_deltavector(deltavector, 20);
            fflush(stdout);

            //sort by first element of pairs
            std::sort(deltavector.begin(),deltavector.end());
            printf("\n *****sorted***** \n");
            print_deltavector(deltavector, 20);




            /*
            int j;
            int k;
            for(j = 0; j < 4; j++){
                for(i = 0; i < 4; i++){
                    printf("element of myarray: %d \n", my2darray[i][j]);
                }
            }

            */

            /*
            for(i = 0; i < 4; i++){
                printf("element of myarray: %d \n", myarray[i]);
            }

            */


            //initialize the vector of 2d arrays to -1
            //for(evt = 0; evt < TIMESTAMP_COUNT; evt++){
            //    for(ch = 0; ch < 4; ch++){
            //        for(tg = 0; tg < 10; tg++){
            //            events[evt][ch][tg] = -1;
            //        }
            //    }
            //}


            //************** debug
            if (debug){
                printf("rando element of events: %d \n", events[100][2][5]);
                printf("rando element of events: %d \n", events[9000][3][5]);
                printf("rando element of events: %d \n", events[20][3][5]);
            }

        }


    fflush(stdout);
    emit anlongoing(false);
}

qutaganl::~qutaganl(){

}


