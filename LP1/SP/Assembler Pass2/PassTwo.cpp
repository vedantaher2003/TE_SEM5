#include<bits/stdc++.h>
using namespace std;

class Tokenizer{

    public:
    
    vector<vector<string>> tokenizeIc(){
        
        vector<vector<string>> allTokens;
        ifstream inputFile;
        inputFile.open("tc1_ic.txt", ios::out);

        string line;
        while(getline(inputFile, line)){
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while(getline(ss, token, ' ')){
                tokens.push_back(token);
            }
            allTokens.push_back(tokens);
        }

        return allTokens;
    }

    vector<vector<string>> tokenizeSymT(){
        
        vector<vector<string>> allTokens;
        ifstream inputFile;
        inputFile.open("tc1_symt.txt");

        string line;
        while(getline(inputFile, line)){
            vector<string> tokens;
            stringstream ss(line);
            string token;
            while(getline(ss, token, ' ')){
                tokens.push_back(token);
            }
            allTokens.push_back(tokens);
        }

        return allTokens;
    }

    vector<vector<string>> tokenizeLit(){
        
        vector<vector<string>> allTokens;
        ifstream inputFile;
        inputFile.open("tc1_lit.txt");

        string line;
        while(getline(inputFile, line)){
            vector<string> tokens;
            stringstream ss(line);
            string token;
            while(getline(ss, token, ' ')){
                tokens.push_back(token);
            }
            allTokens.push_back(tokens);
        }

        return allTokens;
    }

};

class Pass2{

    public:
    Tokenizer tknz;
    vector<vector<string>> icSet;
    vector<vector<string>> symSet;
    vector<vector<string>> litSet;
    vector<string> mCode;

    Pass2(){
        this->icSet = tknz.tokenizeIc();
        this->symSet = tknz.tokenizeSymT();
        this->litSet = tknz.tokenizeLit();
    }

    void printMCode(){
        for(auto i: mCode){
            cout<<i<<endl;
        }
    }

    void performPass2(){

        for(auto i: icSet){
            
            if(i[0]=="-1"){
                continue;
            }
            else if(i[1].substr(1, 2)=="IS"){
                
                // IF ONLY LC AND IC FOR MNEMONIC
                string code = i[0] + " " + i[1].substr(4,2) + " ";
                
                // IF IC FOR BOTH OP
                if(i.size() == 4){

                    // ADD MC FOR OP1
                    code += i[2].substr(1,1) + " ";
                    
                    // OP2 HAS SYMT ENTRY
                    if(i[3][1] == 'S'){
                        vector<string> symEntry = symSet[stoi(i[3].substr(3,2))-1];
                        code += symEntry[2] + " ";
                    }
                    // OP2 HAS LIT ENTRY
                    else if(i[3][1] == 'L'){
                        vector<string> litEntry = litSet[stoi(i[3].substr(3,2))-1];
                        code += litEntry[2] + " ";
                    }

                }
                
                mCode.push_back(code);

            }
            else if(i[1].substr(1, 2)=="DL"){

                string code = i[0];

                if(i[1].substr(4,2)=="01"){
                    code += " 0 0 " + i[2].substr(4,1);
                }

                mCode.push_back(code);

            }

        }

    }

};

int main(){
    Pass2 p2;
    p2.performPass2();
    p2.printMCode();
    return 0;
}