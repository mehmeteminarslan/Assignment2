//
// Created by student on 09.11.2018.
//

#include "Passenger.h"


Passenger::Passenger(int _arriveTime,int _boardTime, int _luggageTime, int _securityTime, char _vip, char _luggage){
    this->arriveTime = _arriveTime;
    this->boardTime = _boardTime;
    this->luggageTime = _luggageTime;
    this->securityTime = _securityTime;
    this->vip = _vip;
    this->luggage = _luggage;
    this->time=_arriveTime;

}
Passenger::Passenger(const Passenger &pss) {
    this->arriveTime = pss.arriveTime;
    this->boardTime = pss.boardTime;
    this->luggageTime = pss.luggageTime;
    this->securityTime = pss.securityTime;
    this->vip = pss.vip;
    this->luggage = pss.luggage;
    this->time=pss.time;
}
Passenger& Passenger::operator=(const Passenger &pss) {
    this->arriveTime = pss.arriveTime;
    this->boardTime = pss.boardTime;
    this->luggageTime = pss.luggageTime;
    this->securityTime = pss.securityTime;
    this->vip = pss.vip;
    this->luggage = pss.luggage;
    this->time=pss.time;

}
Passenger& Passenger::operator=(Passenger &&pss) {
    this->arriveTime = pss.arriveTime;
    this->boardTime = pss.boardTime;
    this->luggageTime = pss.luggageTime;
    this->securityTime = pss.securityTime;
    this->vip = pss.vip;
    this->luggage = pss.luggage;
    this->time=pss.time;

}
Passenger::Passenger(Passenger &&pss) {

    this->arriveTime = pss.arriveTime;
    this->boardTime = pss.boardTime;
    this->luggageTime = pss.luggageTime;
    this->securityTime = pss.securityTime;
    this->vip = pss.vip;
    this->luggage = pss.luggage;
    this->time=pss.time;
}
//bool Passenger::X_less(Passenger const &l, Passenger const &r) {

  //   return l.time < r.time;
//}
//bool Passenger::operator<(Passenger const &l, Passenger const &r) {
  //  return l.time<r.time;
//}
void Passenger::setTime(int time) {
    this->time = time;
}
Passenger::~Passenger() {

}