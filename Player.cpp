#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

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

Player::Player(string n, int exp, int acc, int eff, int ins, int dp, int adv, int pt, int l){
    playerName=n;
    experience=exp;
    accuracy=acc;
    efficiency=eff;
    insight=ins;
    discoveryPoints=dp;
    advisor=adv;
    pathType=pt;
    lane=-1;
}

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

void Player::setName(string n){
    playerName=n;
}
void Player::setExperience(int exp){
    experience=exp;
}
int Player::setAccuracy(int acc){
    accuracy=acc;
}
int Player::setEfficiency(int eff){
    efficiency=eff;
}
int Player::setInsight(int ins){
    insight=ins;
}
int Player::setDiscoveryPts(int dp){
    discoveryPoints=dp;
}
int Player::setAdvisor(int adv){
    advisor=adv;
}
int Player::setPathType(int pt){
    pathType=pt;
}
int Player::setLane(int l){
    lane=l;
}