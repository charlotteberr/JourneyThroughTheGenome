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
void Player::setAccuracy(int acc){
    accuracy=acc;
}
void Player::setEfficiency(int eff){
    efficiency=eff;
}
void Player::setInsight(int ins){
    insight=ins;
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