#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include "Passenger.h"
using namespace std;
bool queueSort(Passenger const &l, Passenger const &r) {
    if(l.time==r.time){
        return l.arriveTime > r.arriveTime;
    }
    return l.time >= r.time ;
}
bool firstFlySort(Passenger const &l, Passenger const &r) {
    if(l.boardTime==r.boardTime){
        return l.arriveTime > r.arriveTime;
    }
    return l.boardTime > r.boardTime ;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }
    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;
    ifstream infile(argv[1]);
    string line;

    vector<string> input;
    /*
    //-getline(infile,line);

    //infile.get();
    //std::cout << infile.get() <<std::endl;
    //-int a = line.find(" ");
    //-int b = line.find_last_of(" ");
    //line.rfind(" ");

    //-cout <<a<<"-"<<b<<endl;

    //-std::cout <<line.substr(0,a)<<std::endl;
    //-std::cout <<line.at(a+1)<<std::endl;
    //-std::cout <<line.at(b+1)<<std::endl;
    //-std::cout <<line.size()<<std::endl;

    int P, L, S;
    P = stoi(line.substr(0,a));
    cout<< "P: "<< P;
    L = (line.at(a+1)-48);
    cout<< " L: " << L;
    S = line.at(b+1)-48;
    cout<< " S: " << S<<endl;
    */
    int P, L, S;

    infile >> P;
    //cout << "P: " << P;
    infile >> L;
    //cout << " L: " << L;
    infile >> S;
    //cout << " S: " << S << endl;
    vector<Passenger> passengers;
    Passenger *p;

    for (int i = 0; i < P; i++) {

        int arriveTime, boardTime, luggageTime, securityTime;
        char vip, luggage;
        infile >> arriveTime;
        infile >> boardTime;
        infile >> luggageTime;
        infile >> securityTime;
        infile >> vip;
        infile >> luggage;
        p = new Passenger(arriveTime, boardTime, luggageTime, securityTime, vip, luggage);
        passengers.push_back(*p);
    }
    float timer = 0;
    int late=0;
    float sum = 0;
    vector<Passenger> luggageCounters;
    vector<Passenger> securityCounters;
    queue<Passenger> luggageQueue;
    queue<Passenger> securityQueue;
    timer = passengers.at(0).arriveTime;
    bool finish = false;
    //********************************case1
    int x=0;
    bool bre= false;


    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            while (timer == passengers.at(x).arriveTime) {
                if (luggageCounters.size() < L) {
                    //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                    luggageCounters.push_back(passengers.at(x));
                    luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                    sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                } else {
                    luggageQueue.push(passengers.at(x));
                }
                x++;
                if (x == P) {
                    bre = true;
                    break;
                }

            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            while (luggageCounters.back().time == timer) {
                if (securityCounters.size() < S) {
                    luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                    securityCounters.push_back(luggageCounters.back());
                    sort(securityCounters.begin(), securityCounters.end(), queueSort);
                } else {
                    securityQueue.push(luggageCounters.back());
                }
                luggageCounters.pop_back();

                if (!luggageQueue.empty()){
                    while(luggageCounters.size()<L) {

                        luggageQueue.front().setTime(timer + luggageQueue.front().luggageTime);
                        luggageCounters.push_back(luggageQueue.front());
                        luggageQueue.pop();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue.empty()){
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {
                if(securityCounters.back().boardTime<timer){
                    late++;


                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue.empty()) {
                    while(securityCounters.size()<S) {

                        securityQueue.front().setTime(timer + securityQueue.front().securityTime);
                        securityCounters.push_back(securityQueue.front());
                        securityQueue.pop();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue.empty()&&luggageQueue.empty()&&x==P){
            finish = true;
        }
        //cout<<"Timer: "<<timer<<endl;
    }

    float avarage1 = sum/P;
    int late1 = late;

    //***************************************case2
    /*
    luggageCounters;
    securityCounters;
    luggageQueue;
    securityQueue;
     */

    vector<Passenger> luggageQueue2;
    vector<Passenger> securityQueue2;
    securityCounters.clear();
    luggageCounters.clear();
    securityQueue2.clear();
    luggageQueue2.clear();
    late=0;

    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;

    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            while (timer == passengers.at(x).arriveTime) {
                if (luggageCounters.size() < L) {
                    //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                    luggageCounters.push_back(passengers.at(x));
                    luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                    sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                } else {
                    luggageQueue2.push_back(passengers.at(x));
                    sort(luggageQueue2.begin(), luggageQueue2.end(), firstFlySort);
                }
                x++;
                if (x == P) {
                    bre = true;
                    break;
                }

            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            while (luggageCounters.back().time == timer) {
                if (securityCounters.size() < S) {
                    luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                    securityCounters.push_back(luggageCounters.back());
                    sort(securityCounters.begin(), securityCounters.end(), queueSort);
                } else {
                    securityQueue2.push_back(luggageCounters.back());
                    sort(securityQueue2.begin(),securityQueue2.end(),firstFlySort);
                }
                luggageCounters.pop_back();

                if (!luggageQueue2.empty()){
                    while(luggageCounters.size()<L) {

                        luggageQueue2.back().setTime(timer + luggageQueue2.back().luggageTime);
                        luggageCounters.push_back(luggageQueue2.back());
                        luggageQueue2.pop_back();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {

                if(securityCounters.back().boardTime<timer){
                    late++;
                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue2.empty()) {
                    while(securityCounters.size()<S) {
                        securityQueue2.back().setTime(timer + securityQueue2.back().securityTime);
                        securityCounters.push_back(securityQueue2.back());
                        securityQueue2.pop_back();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue2.empty()&&luggageQueue2.empty()&&x==P){
            finish = true;
        }
    }

    float avarage2 = sum/P;
    int late2 = late;


    //****************************************case3
    late=0;
    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;

    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            while (timer == passengers.at(x).arriveTime) {
                if (luggageCounters.size() < L) {
                    //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                    luggageCounters.push_back(passengers.at(x));
                    luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                    sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                } else {
                    luggageQueue.push(passengers.at(x));

                }
                x++;
                if (x == P) {
                    bre = true;
                    break;
                }

            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            while (luggageCounters.back().time == timer) {
                if (luggageCounters.back().vip == 'V') {
                    if (luggageCounters.back().boardTime < timer) {
                        late++;
                    }
                    sum += timer - luggageCounters.back().arriveTime;

                } else {
                    if (securityCounters.size() < S) {
                        luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                        securityCounters.push_back(luggageCounters.back());
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                    } else {
                        securityQueue.push(luggageCounters.back());

                    }
                }
                luggageCounters.pop_back();
                if (!luggageQueue.empty()) {
                    while (luggageCounters.size() < L) {
                        luggageQueue.front().setTime(timer + luggageQueue.front().luggageTime);
                        luggageCounters.push_back(luggageQueue.front());
                        luggageQueue.pop();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue.empty()) {
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {

                if(securityCounters.back().boardTime<timer){
                    late++;
                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue.empty()) {
                    while(securityCounters.size()<S) {
                        securityQueue.front().setTime(timer + securityQueue.front().securityTime);
                        securityCounters.push_back(securityQueue.front());
                        securityQueue.pop();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue.empty()&&luggageQueue.empty()&&x==P){
            finish = true;
        }
    }

    float avarage3 = sum/P;
    int late3 = late;

    //----------------------------------------case4

    late=0;
    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;

    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            while (timer == passengers.at(x).arriveTime) {

                if (luggageCounters.size() < L) {
                    //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                    luggageCounters.push_back(passengers.at(x));
                    luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                    sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                } else {
                    luggageQueue2.push_back(passengers.at(x));
                    sort(luggageQueue2.begin(), luggageQueue2.end(), firstFlySort);
                }
                x++;
                if (x == P) {
                    bre = true;
                    break;
                }

            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            while (luggageCounters.back().time == timer) {
                if (luggageCounters.back().vip == 'V') {
                    if (luggageCounters.back().boardTime < timer) {
                        late++;
                    }
                    sum += timer - luggageCounters.back().arriveTime;
                } else {
                    if (securityCounters.size() < S) {
                        luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                        securityCounters.push_back(luggageCounters.back());
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                    } else {
                        securityQueue2.push_back(luggageCounters.back());
                        sort(securityQueue2.begin(),securityQueue2.end(),firstFlySort);
                    }
                }
                luggageCounters.pop_back();

                if (!luggageQueue2.empty()){
                    while(luggageCounters.size()<L) {
                        luggageQueue2.back().setTime(timer + luggageQueue2.back().luggageTime);
                        luggageCounters.push_back(luggageQueue2.back());
                        luggageQueue2.pop_back();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {

                if(securityCounters.back().boardTime<timer){
                    late++;
                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue2.empty()) {
                    while(securityCounters.size()<S) {
                        securityQueue2.back().setTime(timer + securityQueue2.back().securityTime);
                        securityCounters.push_back(securityQueue2.back());
                        securityQueue2.pop_back();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue2.empty()&&luggageQueue2.empty()&&x==P){
            finish = true;
        }
    }
    float avarage4 = sum/P;
    int late4 = late;


    //*********************************case5

    late=0;
    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;

    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            while (timer == passengers.at(x).arriveTime) {
                if(passengers.at(x).luggage == 'N'){
                    //cout<< passengers.at(x).luggage<<endl;
                    if (securityCounters.size() < S) {
                        //passengers.at(x).setTime(passengers.at(x).securityTime + timer);
                        securityCounters.push_back(passengers.at(x));
                        securityCounters.back().setTime(timer+passengers.at(x).securityTime);
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                    } else {
                        securityQueue.push(passengers.at(x));
                    }
                }else {
                    if (luggageCounters.size() < L) {
                        //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                        luggageCounters.push_back(passengers.at(x));
                        luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                    } else {
                        luggageQueue.push(passengers.at(x));
                    }
                }
                x++;
                if (x == P) {
                    bre = true;
                    break;
                }
            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            while (luggageCounters.back().time == timer) {
                if (securityCounters.size() < S) {
                    luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                    securityCounters.push_back(luggageCounters.back());
                    sort(securityCounters.begin(), securityCounters.end(), queueSort);
                } else {
                    securityQueue.push(luggageCounters.back());
                }
                luggageCounters.pop_back();

                if (!luggageQueue.empty()){
                    while(luggageCounters.size()<L) {
                        luggageQueue.front().setTime(timer + luggageQueue.front().luggageTime);
                        luggageCounters.push_back(luggageQueue.front());
                        luggageQueue.pop();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue.empty()){
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {
                if(securityCounters.back().boardTime<timer){
                    late++;

                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue.empty()) {
                    while(securityCounters.size()<S) {

                        securityQueue.front().setTime(timer + securityQueue.front().securityTime);
                        securityCounters.push_back(securityQueue.front());
                        securityQueue.pop();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue.empty()&&luggageQueue.empty()&&x==P){
            finish = true;
        }
    }

    float avarage5 = sum/P;
    int late5 = late;
    //********************************case6

    late=0;
    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;
    /*
    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            if (timer == passengers.at(x).arriveTime) {
                if(passengers.at(x).luggage == 'N'){
                    if (securityCounters.size() < S) {
                        //passengers.at(x).setTime(passengers.at(x).securityTime + timer);
                        securityCounters.push_back(passengers.at(x));
                        securityCounters.back().setTime(timer+passengers.at(x).securityTime);
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                    } else {
                        securityQueue2.push_back(passengers.at(x));
                        sort(securityQueue2.begin(),securityQueue2.end(),firstFlySort);
                    }
                }else {
                    if (luggageCounters.size() < L) {
                        //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                        luggageCounters.push_back(passengers.at(x));
                        luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                    } else {
                        luggageQueue2.push_back(passengers.at(x));
                        sort(luggageQueue2.begin(), luggageQueue2.end(), firstFlySort);
                    }
                }

                x++;
                if (x == P) {
                    bre = true;
                    break;
                }

            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            //cout<<luggageCounters.back().time<<" " <<timer <<endl;
            while (luggageCounters.back().time == timer) {
                if (securityCounters.size() < S) {
                    luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                    securityCounters.push_back(luggageCounters.back());
                    sort(securityCounters.begin(), securityCounters.end(), queueSort);
                } else {
                    securityQueue2.push_back(luggageCounters.back());
                    sort(securityQueue2.begin(),securityQueue2.end(),firstFlySort);
                }

                luggageCounters.pop_back();

                if (!luggageQueue2.empty()){
                    while(luggageCounters.size()<L) {

                        luggageQueue2.back().setTime(timer + luggageQueue2.back().luggageTime);
                        luggageCounters.push_back(luggageQueue2.back());
                        luggageQueue2.pop_back();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {
                if(securityCounters.back().boardTime<timer){
                    late++;
                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue2.empty()) {
                    while(securityCounters.size()<S) {
                        securityQueue2.back().setTime(timer + securityQueue2.back().securityTime);
                        securityCounters.push_back(securityQueue2.back());
                        securityQueue2.pop_back();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue2.empty()&&luggageQueue2.empty()&&x==P){
            finish = true;
        }
    }
    */
    float avarage6 = sum/P;
    int late6 = late;

    //*******************************************case7


    late=0;
    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;

   while (!finish) {
       //looks if there are any passenger
       if(!bre) {
           while (timer == passengers.at(x).arriveTime) {
               if(passengers.at(x).luggage == 'N'){
                   if (securityCounters.size() < S) {
                       //passengers.at(x).setTime(passengers.at(x).securityTime + timer);
                       securityCounters.push_back(passengers.at(x));
                       securityCounters.back().setTime(timer+passengers.at(x).securityTime);
                       sort(securityCounters.begin(), securityCounters.end(), queueSort);
                   } else {
                       securityQueue.push(passengers.at(x));
                   }
               }else {
                   if (luggageCounters.size() < L) {
                       //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                       luggageCounters.push_back(passengers.at(x));
                       luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                       sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                   } else {
                       luggageQueue.push(passengers.at(x));

                   }
               }
               x++;
               if (x == P) {
                   bre = true;
                   break;
               }
           }
       }
       //looks if there are any empty luggage counters
       if (!luggageCounters.empty()) {
           //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
           while (luggageCounters.back().time == timer) {
               if (luggageCounters.back().vip == 'V') {
                   if (luggageCounters.back().boardTime < timer) {
                       late++;
                   }
                   sum += timer - luggageCounters.back().arriveTime;

               } else {
                   if (securityCounters.size() < S) {
                       luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                       securityCounters.push_back(luggageCounters.back());
                       sort(securityCounters.begin(), securityCounters.end(), queueSort);
                   } else {
                       securityQueue.push(luggageCounters.back());

                   }
               }
               luggageCounters.pop_back();
               if (!luggageQueue.empty()) {
                   while (luggageCounters.size() < L) {
                       luggageQueue.front().setTime(timer + luggageQueue.front().luggageTime);
                       luggageCounters.push_back(luggageQueue.front());
                       luggageQueue.pop();
                       sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                       if (luggageQueue.empty()) {
                           break;
                       }
                   }
               }
           }
       }
       //looks if there are any empty security counters
       if (!securityCounters.empty()) {
           //sort(securityCounters.begin(), securityCounters.end(), queueSort);
           while (securityCounters.back().time == timer) {
               if(securityCounters.back().boardTime<timer){
                   late++;
               }
               sum +=timer-securityCounters.back().arriveTime;
               securityCounters.pop_back();
               if (!securityQueue.empty()) {
                   while(securityCounters.size()<S) {
                       securityQueue.front().setTime(timer + securityQueue.front().securityTime);
                       securityCounters.push_back(securityQueue.front());
                       securityQueue.pop();
                       sort(securityCounters.begin(), securityCounters.end(), queueSort);
                       if (securityQueue.empty()){
                           break;
                       }
                   }
               }
           }
       }
       timer++;
       if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue.empty()&&luggageQueue.empty()&&x==P){
           finish = true;
       }
   }

    float avarage7 = sum/P;
    int late7 = late;



    //*******************************case8
    late=0;
    sum = 0;
    timer = passengers.at(0).arriveTime;
    finish = false;

    x=0;
    bre= false;
    while (!finish) {
        //looks if there are any passenger
        if(!bre) {
            if (timer == passengers.at(x).arriveTime) {

                if(passengers.at(x).luggage == 'N'){
                    if(passengers.at(x).vip == 'V'){

                    }else{
                        if (securityCounters.size() < S) {
                            //passengers.at(x).setTime(passengers.at(x).securityTime + timer);
                            securityCounters.push_back(passengers.at(x));
                            securityCounters.back().setTime(timer+passengers.at(x).securityTime);
                            sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        } else {
                            securityQueue2.push_back(passengers.at(x));
                            sort(securityQueue2.begin(),securityQueue2.end(),firstFlySort);
                        }
                    }
                }else {

                    if (luggageCounters.size() < L) {
                        //passengers.at(x).setTime(timer + passengers.at(x).luggageTime);
                        luggageCounters.push_back(passengers.at(x));
                        luggageCounters.back().setTime(timer+passengers.at(x).luggageTime);
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);


                    } else {

                        luggageQueue2.push_back(passengers.at(x));
                        //cout<<luggageQueue2.back().boardTime<<" "<<passengers.at(x).boardTime<<endl;
                        //cout<<"board 1:                     "<<luggageQueue2.back().boardTime<<endl;
                        //cout<<"arrive1:                     "<<luggageQueue2.back().arriveTime<<endl;
                        sort(luggageQueue2.begin(), luggageQueue2.end(), firstFlySort);
                        //cout<<"board2 :                     "<<luggageQueue2.back().boardTime<<endl;
                        //cout<<"arrive2:                     "<<luggageQueue2.back().arriveTime<<endl;
                    }
                }

                x++;
                if (x == P) {
                    bre = true;
                    break;
                }

            }
        }
        //looks if there are any empty luggage counters
        if (!luggageCounters.empty()) {
            //sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
            //cout<<luggageCounters.back().time<<" " <<timer <<endl;
            while (luggageCounters.back().time == timer) {

                if (luggageCounters.back().vip == 'V') {
                    if (luggageCounters.back().boardTime < timer) {
                        late++;
                    }
                    sum += timer - luggageCounters.back().arriveTime;
                } else {
                    if (securityCounters.size() < S) {
                        //luggageCounters.back().setTime(luggageCounters.back().securityTime + timer);
                        securityCounters.push_back(luggageCounters.back());
                        securityCounters.back().setTime(luggageCounters.back().securityTime+timer);
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                    } else {
                        securityQueue2.push_back(luggageCounters.back());
                        sort(securityQueue2.begin(),securityQueue2.end(),firstFlySort);
                    }
                }
                luggageCounters.pop_back();

                if (!luggageQueue2.empty()){
                    while(luggageCounters.size()<L) {

                        //luggageQueue2.back().setTime(timer + luggageQueue2.back().luggageTime);
                        luggageCounters.push_back(luggageQueue2.back());
                        luggageCounters.back().setTime(timer+luggageQueue2.back().luggageTime);
                        luggageQueue2.pop_back();
                        sort(luggageCounters.begin(), luggageCounters.end(), queueSort);
                        if (luggageQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        //looks if there are any empty security counters
        if (!securityCounters.empty()) {
            //sort(securityCounters.begin(), securityCounters.end(), queueSort);
            while (securityCounters.back().time == timer) {
                if(securityCounters.back().boardTime<timer){
                    late++;
                }
                sum +=timer-securityCounters.back().arriveTime;
                securityCounters.pop_back();

                if (!securityQueue2.empty()) {
                    while(securityCounters.size()<S) {
                        //securityQueue2.back().setTime(timer + securityQueue2.back().securityTime);
                        securityCounters.push_back(securityQueue2.back());
                        securityCounters.back().setTime(timer +securityQueue2.back().securityTime);
                        securityQueue2.pop_back();
                        sort(securityCounters.begin(), securityCounters.end(), queueSort);
                        if (securityQueue2.empty()){
                            break;
                        }
                    }
                }
            }
        }
        timer++;
        if(securityCounters.empty()&&luggageCounters.empty()&&securityQueue2.empty()&&luggageQueue2.empty()&&x==P){
            finish = true;
        }
    }

    float avarage8 = sum/P;
    int late8 = late;


    ofstream myfile;
    myfile.open (argv[2]);
    myfile <<avarage1 << " " << late1 <<endl;
    myfile <<avarage2 << " " << late2 <<endl;
    myfile <<avarage3 << " " << late3 <<endl;
    myfile <<avarage4 << " " << late4 <<endl;
    myfile <<avarage5 << " " << late5 <<endl;
    myfile <<avarage6 << " " << late6 <<endl;
    myfile <<avarage7 << " " << late7 <<endl;
    myfile <<avarage8 << " " << late8 <<endl;
    myfile.close();
    return 0;
}
