//
// Created by student on 09.11.2018.
//

#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H

#include <iostream>

class Passenger {
public:
    int arriveTime,boardTime,luggageTime,securityTime,time;
    char vip,luggage;
    Passenger(int arriveTime,int boardTime, int luggageTime, int securityTime, char vip, char luggage);
    void setTime(int time);
    //bool X_less(Passenger const &l, Passenger const &r);
   // bool operator<(Passenger const &l, Passenger const &r);
    Passenger(const Passenger& pss);
    Passenger& operator=(const Passenger& pss);
    Passenger(Passenger&& pss);
    Passenger& operator=(Passenger&& pss);
    ~Passenger();
};
#endif //PROJECT2_PASSENGER_H
