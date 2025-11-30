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
    srand(time(0));
    Board board;
    Player characterInfo[5]; //for reading in characters.txt
    Player players[2];

    ifstream inFile;
    inFile.open("characters.txt");
    string line;
    int index=0;
    if(inFile.fail()){
        cout<<"Error opening characters.txt"<<endl;
        return 1;
    }
    else{
        while(getline(inFile, line)){    // loads the 5 characters and their stats in characters.txt into an index of characterInfo
            vector<string> parts=split(line,'|');
            string n=parts[0];
            int exp=stoi(parts[1]);
            int acc=stoi(parts[2]);
            int eff=stoi(parts[3]);
            int ins=stoi(parts[4]);
            int dp=stoi(parts[5]);

            characterInfo[index]=Player(n, exp, acc, eff, ins, dp);
            index++;
        }
    }
    inFile.close();

    cout<<endl<<"Welcome to the Journey Through the Genome!"<<endl;
    cout<<"Here we have the 5 characters to choose from..."<<endl;
    cout<<endl;
    for(int i=0;i<5;i++){  //display all 5 characters info
        cout<<i+1<<". ";
        cout<<characterInfo[i].getName()<<" | Experience: "<<characterInfo[i].getExperience();
        cout<<" | Accuracy: "<<characterInfo[i].getAccuracy()<<" | Efficiency: "<<characterInfo[i].getEfficiency();
        cout<<" | Insight: "<<characterInfo[i].getInsight()<<" | DP: "<<characterInfo[i].getDiscoveryPts()<<endl;
    }
    cout<<endl;
    cout<<"PLAYER 1, choose your character (Type a number 1-5): ";
    int choice1;
    cin>>choice1;
    while (choice1 < 1 || choice1 > 5) {
        cout << "Invalid choice. Please choose a number from 1 to 5: ";
        cin >> choice1;
    }
    players[0]=characterInfo[choice1-1];
    cout<<"PLAYER 2, choose your character (Type a number 1-5, not including "<<choice1<<"): ";
    int choice2;
    cin>>choice2;
    while (choice2 < 1 || choice2 > 5 || choice2 == choice1) {
        cout << "Choose a different character (1-5, not " << choice1 << "): ";
        cin >> choice2;
    }
    players[1]=characterInfo[choice2-1];

    cout<<endl;
    cout<<"Time to choose your paths... "<<endl;
    cout<<"| 1 | Training Fellowship"<<endl;
    cout<<"This path equips your scientist with essential traits (accuracy, efficiency, and insight) needed for future challenges. "<<endl;
    cout<<"Requires an investment of -5000 DP. But, gives +500 ACC, +500 EFF, and +1000 INS."<<endl;
    cout<<"You will choose an advisor who grants a special ability that protects them during random events that negatively impact DP."<<endl;
    cout<<endl<<"| 2 | Direct Lab Assignment"<<endl;
    cout<<"This option lets your scientist jump directly into the life of DNA sequencing."<<endl;
    cout<<"Gives an immediate boost of +5000 DP. Also gives +200 ACC, +200 EFF, +200 INS."<<endl;
    cout<<"No advisor is given."<<endl;

    cout<<endl<<"PLAYER 1, choose your path (Type 1 or 2): ";
    cin>>choice1;
    if(choice1==1){
        cout<<endl<<"Choose your advisor... "<<endl;
        inFile.open("advisor.txt");
        if(inFile.fail()){
            cout<<"Failed to open advisor.txt"<<endl;
            return 1;
        }
        else{
            while(getline(inFile,line)){
                cout<<line<<endl;
            }
        }
        inFile.close();
        cout<<"Type a number 1-5: ";
        int advisorChoice;
        cin>>advisorChoice;
        players[0].setPathType(0);
        players[0].setAdvisor(advisorChoice);
        players[0].addDiscoveryPts(-5000);
        players[0].addAccuracy(500);
        players[0].addEfficiency(500);
        players[0].addInsight(1000);
    }
    else{
        players[0].setPathType(1);
        players[0].addDiscoveryPts(5000);
        players[0].addAccuracy(200);
        players[0].addEfficiency(200);
        players[0].addInsight(200);
    }

    cout<<endl<<"PLAYER 2, choose your path (Type 1 or 2): ";
    cin>>choice2;
    if(choice2==1){
        cout<<endl<<"Choose your advisor... "<<endl;
        inFile.open("advisor.txt");
        if(inFile.fail()){
            cout<<"Failed to open advisor.txt"<<endl;
            return 1;
        }
        else{
            while(getline(inFile,line)){
                cout<<line<<endl;
            }
        }
        inFile.close();
        cout<<"Type a number 1-5: ";
        int advisorChoice;
        cin>>advisorChoice;
        players[1].setPathType(0);
        players[1].setAdvisor(advisorChoice);
        players[1].addDiscoveryPts(-5000);
        players[1].addAccuracy(500);
        players[1].addEfficiency(500);
        players[1].addInsight(1000);
    }
    else{
        players[1].setPathType(1);
        players[1].addDiscoveryPts(5000);
        players[1].addAccuracy(200);
        players[1].addEfficiency(200);
        players[1].addInsight(200);
    }

    players[0].setLane(0);
    players[1].setLane(1);

    cout<<endl<<"Starting Board..."<<endl;
    board.displayBoard();

    bool p1Finished=false;
    bool p2Finished=false; // becomes true when they finish their lane
    int currentPlayer=0; // tracking which players turn it is

    while(!p1Finished || !p2Finished){
        if ((currentPlayer==0 && p1Finished) || (currentPlayer==1 && p2Finished)) {   // skips player turn if they already finished
            cout<<endl<<"Player "<<currentPlayer + 1<<" has already finished and skips this turn."<<endl;
            currentPlayer=1-currentPlayer;
            continue;
        }
        cout<<endl<<"------------------------------------------";
        cout<<endl<<"             PLAYER "<<currentPlayer+1<<"'s TURN              ";
        cout<<endl<<"------------------------------------------";
        bool turnFinished=false;
        while(!turnFinished){
            cout<<endl<<"Choose an option from the menu...";
            cout<<endl<<"| 1 | Check Player Progress";
            cout<<endl<<"| 2 | Review Character";
            cout<<endl<<"| 3 | Check Board Postion";
            cout<<endl<<"| 4 | Review Advisor";
            cout<<endl<<"| 5 | Move Forward"<<endl;
            cout<<endl<<"Choice: ";
            int menuChoice;
            cin>>menuChoice;
            if(menuChoice==1){
                cout<<endl<<"Option 1 choices..."<<endl;
                cout<<"| 1 | Review Discovery Points"<<endl;
                cout<<"| 2 | Review Trait Stats"<<endl;
                int menu1Choice;
                cout<<endl<<"Choice: ";
                cin>>menu1Choice;
                if(menu1Choice==1){
                    cout<<endl<<"Discovery Points: "<<players[currentPlayer].getDiscoveryPts()<<endl;
                }
                else{
                    cout<<endl<<"Accuracy: "<<players[currentPlayer].getAccuracy();
                    cout<<endl<<"Efficiency: "<<players[currentPlayer].getEfficiency();
                    cout<<endl<<"Insight: "<<players[currentPlayer].getInsight()<<endl;
                }
            }
            else if(menuChoice==2){
                cout<<endl<<"Name: "<<players[currentPlayer].getName();
                cout<<endl<<"Experience: "<<players[currentPlayer].getExperience();
                if(players[currentPlayer].getPathType()==0){
                    cout<<endl<<"Path Type: Training Fellowship"<<endl;
                }
                else{
                    cout<<endl<<"Path Type: Direct Lab Assignment"<<endl;
                }
            }
            else if(menuChoice==3){
                cout<<endl<<"Current Position: Tile "<<board.getPlayerPosition(currentPlayer)<<" / 51"<<endl;
                board.displayBoard();
            }
            else if(menuChoice==4){
                if(players[currentPlayer].getAdvisor()==0){
                    cout<<endl<<"Your player has no advisor"<<endl;
                }
                else{
                    if(players[currentPlayer].getAdvisor()==1){
                        cout<<endl<<"Advisor: Dr. Aliquot";
                        cout<<endl<<"Ability: A master of the \"wet lab\", assisting in avoiding contamination.\n";
                    }
                    else if(players[currentPlayer].getAdvisor()==2){
                        cout<<endl<<"Advisor: Dr. Assembler";
                        cout<<endl<<"Ability: An expert who helps improve efficiency and streamlines pipelines.\n";
                    }
                    else if(players[currentPlayer].getAdvisor()==3){
                        cout<<endl<<"Advisor: Dr. Pop-Gen";
                        cout<<endl<<"Ability: A genetics specialist with insight for identifying rare genetic variants\n";
                    }
                    else if(players[currentPlayer].getAdvisor()==4){
                        cout<<endl<<"Advisor: Dr. Bio-Script";
                        cout<<endl<<"Ability: The genius behind the data analysis, helps debug code.\n";
                    }
                    else if(players[currentPlayer].getAdvisor()==5){
                        cout<<endl<<"Advisor: Dr. Loci";
                        cout<<endl<<"Ability: Your biggest supporter assisting you in learning the equipment.\n";
                    }
                }
            }
            else if(menuChoice==5){
                int roll = rand() % 6+1;
                cout<<endl<<"You rolled a "<<roll<<"!"<<endl;
                cout<<endl;
                bool reachedEnd=false;
                for(int step=0; step<roll; step++){
                    reachedEnd=board.movePlayer(currentPlayer);
                    if(reachedEnd){
                        break;
                    }
                }
                board.displayBoard();
                
                if(reachedEnd){
                    cout<<endl<<"Player "<<currentPlayer+1<<" reached the end of the board!"<<endl;
                    if(currentPlayer==0){
                        p1Finished=true;
                    }
                    else{
                        p2Finished=true;
                    }
                }
                else{
                    int pos=board.getPlayerPosition(currentPlayer);
                    char color=board.getTileColor(currentPlayer, pos); // get position and color on that position
                    if(color=='G'){

                    }
                    else if(color=='U'){
                        
                    }
                    else if(color=='B'){
                        
                    }
                    else if(color=='P'){
                        
                    }
                    else if(color=='R'){
                        
                    }
                    else if(color=='T'){
                        
                    }
                    else{
                        cout<<"\nInvalid Tile Type.";
                    }
                }

                turnFinished=true;
            }
            else{
                cout<<endl<<"Invalid Menu Option. Try Again."<<endl;
            }
        }
        currentPlayer=1-currentPlayer;
    }
}