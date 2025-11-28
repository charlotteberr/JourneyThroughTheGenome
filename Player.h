#include <string>

using namespace std;

class Player{
    private:
        string playerName;
        int experience;
        int accuracy;
        int efficiency;
        int insight;
        int discoveryPoints;
        int advisor;
        int pathType;
        int lane;
    public:
        Player(); // default constructor
        Player(string n, int exp, int acc, int eff, int ins, int dp); // parameterized constructor

        string getName(); //getters
        int getExperience();
        int getAccuracy();
        int getEfficiency();
        int getInsight();
        int getDiscoveryPts();
        int getAdvisor();
        int getPathType();
        int getLane();

        void setName(string n); //setters
        void setExperience(int exp);
        void setAccuracy(int acc);
        void setEfficiency(int eff);
        void setInsight(int ins);
        void setDiscoveryPts(int dp);
        void setAdvisor(int adv);
        void setPathType(int pt);
        void setLane(int l);

        void addAccuracy(int amount);
        void addEfficiency(int amount);
        void addInsight(int amount);
        void addDiscoveryPts(int amount);
};