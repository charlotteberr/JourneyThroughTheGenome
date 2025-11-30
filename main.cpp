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

struct RandomEvent{
    string description;
    int pathType;
    int advisorProtection;
    int dpChange;
};

vector<RandomEvent> loadRandomEvents(string filename){
    vector<RandomEvent> events;
    ifstream inFile;
    inFile.open(filename);
    string line;
    while(getline(inFile,line)){
        if(line.length()==0) continue;
        if(line[0]=='/') continue;
        vector<string> parts=split(line, '|');
        RandomEvent event;
        event.description=parts[0];
        event.pathType=stoi(parts[1]);
        event.advisorProtection=stoi(parts[2]);
        event.dpChange=stoi(parts[3]);

        events.push_back(event);
    }
    return events;
}

Player processGreenTile(Player p, vector<RandomEvent> events){
    if(rand()%2==0){
        cout<<endl<<"No event triggered on this tile...\n";
        return p;
    }
    int index=rand()% events.size();
    RandomEvent event=events[index];
    if(p.getPathType() != event.pathType){
        cout<<"\nThis event does not affect your path...\n";
        return p;
    }
    else{
        cout<<"\n----EVENT TRIGGERED----\n";
        cout<<endl<<event.description<<endl;
        if(event.dpChange<0){
            if(p.getAdvisor()==event.advisorProtection && event.advisorProtection!=0){
                cout<<endl<<"Your advisor protected you from this event! No DP change occurs.\n";
            }
            else{
                cout<<endl<<"You lose "<<event.dpChange<<" DP...\n";
                p.addDiscoveryPts(event.dpChange);
            }
        }
        else{
            cout<<endl<<"You gain +"<<event.dpChange<<" DP!\n";
            p.addDiscoveryPts(event.dpChange);
        }
        return p;
    }
}

struct Riddle{
    string question;
    string answer;
};

vector<Riddle> loadRiddles(string filename){
    vector<Riddle> riddles;
    ifstream inFile;
    inFile.open(filename);
    string line;
    while(getline(inFile,line)){
        if(line.length()==0) continue;
        if(line[0]=='Q') continue;
        vector<string> parts=split(line, '|');
        Riddle riddle;
        riddle.question=parts[0];
        riddle.answer=parts[1];

        riddles.push_back(riddle);
    }
    return riddles;
}

Player processPurpleTile(Player p, vector<Riddle> riddles){
    int index=rand()% riddles.size();
    Riddle riddle=riddles[index];
    cout<<endl<<riddle.question<<endl;
    cout<<"\nAnswer: ";
    string answer;
    cin.ignore();
    getline(cin, answer);
    if(answer==riddle.answer){
        cout<<endl<<"----Correct!----\n";
        cout<<endl<<"You gain +500 DP!\n";
        p.addDiscoveryPts(500);
    }
    else{
        cout<<endl<<"----WRONG----";
        cout<<endl<<"The answer was | "<<riddle.answer<<" | You loose -500 DP...\n";
        p.addDiscoveryPts(-500);
    }
    return p;
}

string generateRandomDNA(int length){
    string dna="";
    string bases="ACGT";
    for(int i=0; i<length; i++){
        int r =rand()%4;
        dna+=bases[r];
    }
    return dna;
}

double strandSimilarity(string strand1, string strand2){
    int matches=0;
    if(strand1.length()!=strand2.length()){
        cout<<endl<<"Strands are unequal in length. Similarity Score: 0\n";
    }
    else{
        for(int i=0; i<strand1.length();i++){
            if(strand1[i]==strand2[i]){
                matches++;
            }
        }
    }
    double similarity=static_cast<double>(matches)/strand1.length();
    return similarity;
}

Player processBlueTile(Player p){
    cout<<endl<<"-----DNA TASK 1: Similarity (Equal-Length)-----\n";
    cout<<"\nA reference DNA strand has been generated and you must type in your own strand of equal length to compare\n";
    cout<<"Remember DNA strands use bases A, C, G, and T. Enter all caps no spaces.\n";
    int randomLength=rand()%5+4;
    string referenceStrand=generateRandomDNA(randomLength);
    cout<<endl<<"Reference strand: "<<referenceStrand<<endl;
    cout<<"You strand: ";
    string playerStrand;
    cin>>playerStrand;
    double similarity=strandSimilarity(referenceStrand, playerStrand);
    if(playerStrand.length()!=referenceStrand.length()){
        cout<<endl<<"Automatic failure! Strands are unequal in length.\n"<<endl;
        p.addAccuracy(-200);
        p.addInsight(-200);
        p.addDiscoveryPts(-500);
    }
    cout<<endl<<"Similarity score: "<<similarity<<endl;
    if(similarity>=0.8){
        cout<<endl<<"Excellent match!\n";
        p.addAccuracy(200);
        p.addInsight(200);
        p.addDiscoveryPts(1000);
    }
    if(similarity<0.8 && similarity>=0.5){
        cout<<endl<<"Good match.\n";
        p.addAccuracy(100);
        p.addInsight(100);
        p.addDiscoveryPts(500);
    }
    else{
        cout<<endl<<"Poor match...\n";
        p.addAccuracy(-100);
        p.addInsight(-100);
        p.addDiscoveryPts(-500);
    }
    cout<<endl<<"----Updated Stats----"<<endl;
    cout<<endl<<"Accuracy: "<<p.getAccuracy()<<endl;
    cout<<"Insight: "<<p.getInsight()<<endl;
    cout<<"Discovery Points: "<<p.getDiscoveryPts()<<endl;

    return p;
}

int bestStrandMatch(string inputStrand, string targetStrand){
    if(inputStrand.length()==0 || targetStrand.length()==0){
        return -1;
    }
    if(targetStrand.length()>inputStrand.length()){
        return -1;
    }
    if(targetStrand.length()==inputStrand.length()){
        return -1;
    }
    double bestScore=-1;
    int bestIndex=-1;
    for(int i=0; i<=inputStrand.length()-targetStrand.length();i++){
        string window=inputStrand.substr(i,targetStrand.length());
        double score=strandSimilarity(window, targetStrand);
        if(score>bestScore){
            bestScore=score;
            bestIndex=i;
        }
    }
    return bestIndex;
}

Player processPinkTile(Player p){
    cout<<endl<<"-----DNA TASK 2: Similarity (Unequal-Length)-----\n";
    cout<<"You have a longer DNA strand and a shorter pattern.\n";
    cout<<"The goal is to find where the shorter strand matches best inside the longer one.\n";
    cout<<"Use only the letters A, C, G, and T. All caps, no spaces.\n\n";
    string inputStrand;
    string targetStrand;
    cout<<"Enter the LONGER DNA strand: ";
    cin>>inputStrand;
    cout<<"Enter the SHORTER DNA strand: ";
    cin>>targetStrand;

    int index=bestStrandMatch(inputStrand, targetStrand);
    if(index==-1){
        cout<<endl<<"Could not find a valid alignment...\n";
        p.addAccuracy(-200);
        p.addInsight(-200);
        p.addDiscoveryPts(-500);
        return p;
    }

    string bestWindow=inputStrand.substr(index, targetStrand.length());
    double bestScore=strandSimilarity(bestWindow, targetStrand);

    cout<<endl<<"Best alignment starts at: "<<index<<endl;
    cout<<"Best matching segment: "<<bestWindow<<endl;
    cout<<"Target strand: "<<targetStrand<<endl;
    cout<<"Similarity Score: "<<bestScore<<endl;

    if(bestScore>=0.8){
        cout<<endl<<"Excellent match!\n";
        p.addAccuracy(200);
        p.addInsight(200);
        p.addDiscoveryPts(1000);
    }
    if(bestScore<0.8 && bestScore>=0.5){
        cout<<endl<<"Good match.\n";
        p.addAccuracy(100);
        p.addInsight(100);
        p.addDiscoveryPts(500);
    }
    else{
        cout<<endl<<"Poor match...\n";
        p.addAccuracy(-100);
        p.addInsight(-100);
        p.addDiscoveryPts(-500);
    }
    cout<<endl<<"----Updated Stats----"<<endl;
    cout<<endl<<"Accuracy: "<<p.getAccuracy()<<endl;
    cout<<"Insight: "<<p.getInsight()<<endl;
    cout<<"Discovery Points: "<<p.getDiscoveryPts()<<endl;

    return p;
}

void indentifyMutations(string inputStrand, string targetStrand){
    cout<<"\n-----Mutation Report-----\n";
    int startIndex=bestStrandMatch(inputStrand, targetStrand);
    if(startIndex==-1){
        cout<<"\nNo valid alignment found.\n";
        return;
    }
    for(int i=0;i<startIndex;i++){  //deletions before best index
        cout<<endl<<"Deletion | "<<inputStrand[i]<<" at index "<<i<<endl;
    }
    for(int i=0;i<targetStrand.length();i++){ //substitutions in window
        if(inputStrand[startIndex+i]!=targetStrand[i]){
            cout<<endl<<"Substitution | "<<inputStrand[startIndex+i]<<" -> "<<targetStrand[i]<<" at index "<<(startIndex+i)<<endl;
        }
    }
    for(int i=startIndex+targetStrand.length(); i<inputStrand.length(); i++){ //deletions after window
        cout<<endl<<"Deletion | "<<inputStrand[i]<<" at index "<<i<<endl;
    }
}

Player processRedTile(Player p){
    cout<<endl<<"-----DNA TASK 3: Mutation Identification-----\n";
    cout<<"The strands will be aligned first using best similarity.\n";
    cout<<"Then substitutions and deletions will be reported.\n";
    cout<<"Use only A, C, G, and T. All caps, no spaces.\n\n";
    string inputStrand;
    string targetStrand;
    cout<<"Enter the LONGER DNA strand: ";
    cin>>inputStrand;
    cout<<"Enter the SHORTER DNA strand: ";
    cin>>targetStrand;

    indentifyMutations(inputStrand, targetStrand);

    int index=bestStrandMatch(inputStrand, targetStrand);
    string bestWindow=inputStrand.substr(index, targetStrand.length());
    double bestScore=strandSimilarity(bestWindow, targetStrand);

    if(bestScore>=0.8){
        cout<<endl<<"Excellent mutation analysis!\n";
        p.addAccuracy(200);
        p.addInsight(200);
        p.addDiscoveryPts(1000);
    }
    if(bestScore>=0.5){
        cout<<endl<<"Moderate mutation detection.\n";
        p.addAccuracy(100);
        p.addInsight(100);
        p.addDiscoveryPts(500);
    }
    else{
        cout<<endl<<"Weak mutation identification...\n";
        p.addAccuracy(-100);
        p.addInsight(-100);
        p.addDiscoveryPts(-500);
    }
    cout<<endl<<"----Updated Stats----"<<endl;
    cout<<endl<<"Accuracy: "<<p.getAccuracy()<<endl;
    cout<<"Insight: "<<p.getInsight()<<endl;
    cout<<"Discovery Points: "<<p.getDiscoveryPts()<<endl;

    return p;
}

void transcribeDNAtoRNA(string strand){
    cout<<endl<<"\n----DNA to RNA Transcription----\n";
    cout<<"DNA Strand: "<<strand<<endl;
    string rna="";
    for(int i=0;i<strand.length();i++){
        if(strand[i]=='T'){
            rna+='U';
        }
        else{
            rna+=strand[i];
        }
    }
    cout<<"RNA Strand: "<<rna<<endl;
}

Player processBrownTile(Player p){
    cout<<endl<<"-----DNA TASK 4: RNA Transcription-----\n";
    cout<<"You will convert a DNA strand into RNA.\n";
    cout<<"Remember: T becomes U.\n";
    cout<<"Use only A, C, G, and T. All caps, no spaces.\n\n";
    cout<<"Enter the DNA strand to transcribe: ";
    string strand;
    cin>>strand;
    transcribeDNAtoRNA(strand);
    cout<<"\nSuccessful transcription improves lab efficiency!\n";
    p.addEfficiency(300);
    p.addDiscoveryPts(600);
    cout<<endl<<"\n----Updated Stats----"<<endl;
    cout<<endl<<"Efficiency: "<<p.getEfficiency()<<endl;
    cout<<"Discovery Points: "<<p.getDiscoveryPts()<<endl;

    return p;
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

    vector<RandomEvent> randomEvents=loadRandomEvents("random_events.txt");  // loading in files for events/riddles
    vector<Riddle> riddles=loadRiddles("riddles.txt"); 

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
                        players[currentPlayer]=processGreenTile(players[currentPlayer], randomEvents);
                    }
                    else if(color=='U'){
                        players[currentPlayer]=processPurpleTile(players[currentPlayer], riddles);
                    }
                    else if(color=='B'){
                        players[currentPlayer]=processBlueTile(players[currentPlayer]);
                    }
                    else if(color=='P'){
                        players[currentPlayer]=processPinkTile(players[currentPlayer]);
                    }
                    else if(color=='R'){
                        players[currentPlayer]=processRedTile(players[currentPlayer]);
                    }
                    else if(color=='T'){
                        players[currentPlayer]=processBrownTile(players[currentPlayer]);
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
    cout<<endl<<"========================================"<<endl;
    cout<<"                GAME OVER               "<<endl;
    cout<<"========================================"<<endl;
    for(int i=0;i<2;i++){
        int accPoints=players[i].getAccuracy()/100;
        int effPoints=players[i].getEfficiency()/100;
        int insPoints=players[i].getInsight()/100;
        int bonus=(accPoints+effPoints+insPoints)*1000;
        cout<<endl<<"Player "<<(i+1)<<" earns "<<bonus<<" bonus points from traits!\n";
        players[i].addDiscoveryPts(bonus);
    }
    for(int i=0;i<2;i++){
        cout<<"\nFinal Stats for Player "<<(i+1)<<" | "<<players[i].getName()<<" |\n";
        cout<<"  Accuracy:   "<<players[i].getAccuracy()<<endl;
        cout<<"  Efficiency: "<<players[i].getEfficiency()<<endl;
        cout<<"  Insight:    "<<players[i].getInsight()<<endl;
        cout<<"  DP:         "<<players[i].getDiscoveryPts()<<endl;
    }
    int dp1=players[0].getDiscoveryPts();
    int dp2=players[1].getDiscoveryPts();

    cout<<endl<<"========================================"<<endl;
    if(dp1>dp2){
        cout<<endl<<"| WINNER | Player 1 - "<<players[0].getName()<< "with "<<dp1<<" Discovery Points!\n";
    }
    else if(dp2>dp1){
        cout<<endl<<"| WINNER | Player 2 - "<<players[1].getName()<< "with "<<dp2<<" Discovery Points!\n";
    }
    else if(dp1==dp2){
        cout<<endl<<"| TIE | Both players have equal Discovery Points!\n";
    }

    ofstream outFile;
    outFile.open("game_stats.txt");
    if(outFile.is_open()){
        outFile<<"Journey Through the Genome - Final Game Stats\n\n";
        for(int i = 0; i < 2; i++){
            outFile<<"Player "<<(i+1)<<" | "<<players[i].getName()<<" |\n";
            outFile<<"  Accuracy:   "<<players[i].getAccuracy()<<endl;
            outFile<<"  Efficiency: "<<players[i].getEfficiency()<<endl;
            outFile<<"  Insight:    "<<players[i].getInsight()<<endl;
            outFile<<"  DP:         "<<players[i].getDiscoveryPts()<<endl;
        }
        outFile.close();
        cout << "\nGame stats written to game_stats.txt\n";
    }
    else{
        cout << "\nError: could not write game_stats.txt\n";
    }

    return 0;
}