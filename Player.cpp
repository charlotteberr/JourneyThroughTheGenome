#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

//constructors
Player::Player(){
    playerName="";
    experience=0;
    accuracy=100;
    efficiency=100;
    insight=100;
    discoveryPoints=0;
    advisor=0;
    pathType=-1;
    lane=-1;
}

Player::Player(string n, int exp, int acc, int eff, int ins, int dp){
    playerName=n;
    experience=exp;
    accuracy=acc;
    efficiency=eff;
    insight=ins;
    discoveryPoints=dp;
    advisor=0;
    pathType=-1;
    lane=-1;
}

//getters
string Player::getName(){
    return playerName;
}
int Player::getExperience(){
    return experience;
}
int Player::getAccuracy(){
    return accuracy;
}
int Player::getEfficiency(){
    return efficiency;
}
int Player::getInsight(){
    return insight;
}
int Player::getDiscoveryPts(){
    return discoveryPoints;
}
int Player::getAdvisor(){
    return advisor;
}
int Player::getPathType(){
    return pathType;
}
int Player::getLane(){
    return lane;
}

//setters
void Player::setName(string n){
    playerName=n;
}
void Player::setExperience(int exp){
    experience=exp;
}
void Player::setAccuracy(int acc){
    if (acc<100){accuracy=100;}
    else {accuracy=acc;}
}
void Player::setEfficiency(int eff){
    if(eff<100){efficiency=100;}
    else{efficiency=eff;}
}
void Player::setInsight(int ins){
    if (ins<100){insight=100;}
    else{insight=ins;}
}
void Player::setDiscoveryPts(int dp){
    discoveryPoints=dp;
}
void Player::setAdvisor(int adv){
    advisor=adv;
}
void Player::setPathType(int pt){
    pathType=pt;
}
void Player::setLane(int l){
    lane=l;
}

//adders
void Player::addAccuracy(int amount){
    accuracy+=amount;
    if(accuracy<100){accuracy=100;}
}
void Player::addEfficiency(int amount){
    efficiency+=amount;
    if(efficiency<100){efficiency=100;}
}
void Player::addInsight(int amount){
    insight+=amount;
    if(insight<100){insight=100;}
}
void Player::addDiscoveryPts(int amount){
    discoveryPoints+=amount;
}
