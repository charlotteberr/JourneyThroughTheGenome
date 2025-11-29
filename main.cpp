#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Board.h"
#include "Player.h"

using namespace std;

vector<string> split(string line, char delimiter){
    vector<string> parts;
    string temp="";
    for(int i=0;i<line.length();i++){
        if(line[i]==delimiter){
            parts.push_back(temp);
            temp="";
        }
        else{
            temp+=line[i];

        }
    }
    parts.push_back(temp);
    return parts;
}

int main(){

}