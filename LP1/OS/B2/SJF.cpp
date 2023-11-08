#include<bits/stdc++.h>
using namespace std;

class Process{
    public:
    char pN;
    int arrivalT;
    int burstT;
    int completionT;
    int turnAroundT;
    int waitingT;
    int remainingT;
    int priority;

    Process(char pN, int at, int bt){
        this->pN = pN;
        this->arrivalT = at;
        this->burstT = bt;
        this->priority = -1;
        this->completionT = -1;
        this->turnAroundT = -1;
        this->waitingT = -1;
        this->remainingT = bt;
    }


    bool operator<(const Process& other) const {
        return remainingT > other.remainingT;
    }

};

class SJFScheduling{
    public:
    vector<Process> Processes;

    void calCompletionTime(){

        sort(Processes.begin(), Processes.end(), [](const Process& a, const Process& b) {
            return a.arrivalT < b.arrivalT;
        });

        vector<Process> temp;
        priority_queue<Process> q;
        int currentT = 0;

        while(!q.empty() || !Processes.empty()){

            while(!Processes.empty() && Processes.front().arrivalT<=currentT){
                q.push(Processes.front());
                Processes.erase(Processes.begin());
            }

            if(!q.empty()){
                
                Process p = q.top();
                q.pop();

                currentT++;
                p.remainingT--;

                if(p.remainingT>0){
                    q.push(p);
                }else{
                    p.completionT = currentT;
                    temp.push_back(p);
                }

            }else{
                currentT++;
            }

        }

        Processes = temp;

    }

    void calTurnAroundTime(){
        for(int i=0; i<Processes.size(); i++){
            Processes[i].turnAroundT = Processes[i].completionT - Processes[i].arrivalT;
        }
    }

    void calWaitingTime(){
        for(int i=0; i<Processes.size(); i++){
            Processes[i].waitingT = Processes[i].turnAroundT - Processes[i].burstT;
        }
    }

    void process(){
        calCompletionTime();
        calTurnAroundTime();
        calWaitingTime();
    }

    void inputProcesses(int n){
        for(int i=0; i<n; i++){
            char pn;
            int at, bt, p;
            cout<<"ProcessNo : ";
            cin>>pn;
            cout<<"Arival Time : ";
            cin>>at;
            cout<<"Burst Time : ";
            cin>>bt;
            cout<<endl;
            Process pr(pn, at, bt);
            Processes.push_back(pr);
        }
    }

    void displayProcesses(){
        for(auto i: Processes){
            cout<<i.pN<<"\t"<<i.arrivalT<<"\t"<<i.burstT<<"\t"<<i.completionT<<"\t"<<i.turnAroundT<<"\t"<<i.waitingT<<endl;
        }
    }

    void displayGantt(){
        cout<<"0-"<<Processes[0].completionT<<":"<<Processes[0].pN<<endl;
        for(int i=1; i<Processes.size(); i++){
            cout<<Processes[i-1].completionT<<"-"<<Processes[i].completionT<<":"<<Processes[i].pN<<endl;
        }
    }

};

int main(){
    SJFScheduling sjfs;
    sjfs.inputProcesses(4);
    sjfs.process();
    sjfs.displayProcesses();
    sjfs.displayGantt();
    return 0;
}