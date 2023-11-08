#include<bits/stdc++.h>
using namespace std;

class FIFOPageReplace{
    
    public:
    int capacity;
    queue<int> pageQueue;
    unordered_set<int> pageSet;
    vector<unordered_set<int>> memoryStates;
    vector<int> pages;
    int hit = 0;
    int miss = 0;

    FIFOPageReplace(int capacity){
        this->capacity = capacity;
    }

    void inputPages(){
        int num;
        cout<<"Enter number of pages : ";
        cin>>num;
        cout<<endl;
        for(int i=0; i<num; i++){
            int pageNo;
            cin>>pageNo;
            pages.push_back(pageNo);
        }
    }

    void replacePage(int pageNo){

        if(pageSet.size()<this->capacity){
            if(pageSet.find(pageNo)==pageSet.end()){
                pageSet.insert(pageNo);
                pageQueue.push(pageNo);
                miss++;
            }
            else{
                hit++;
            }
        }
        else{
            if(pageSet.find(pageNo)==pageSet.end()){
                miss++;
                
                int oldPage = pageQueue.front();
                pageQueue.pop();

                pageSet.erase(oldPage);

                pageSet.insert(pageNo);
                pageQueue.push(pageNo);
            
            }
            else{
                hit++;
            }
        }

        memoryStates.push_back(pageSet);

    }

    void process(){
        for(int i=0; i<pages.size(); i++){
            replacePage(pages[i]);
        }
    }
    
    void printMemoryStates(){
        for(int i=0; i<memoryStates.size(); i++){
            for(auto i: memoryStates[i]){
                cout<<i<<" ";
            }
            cout<<endl;
        }
    }

};

int main(){
    FIFOPageReplace fifo(3);
    fifo.inputPages();
    fifo.process();
    cout<<endl;
    fifo.printMemoryStates();
    cout<<endl;
    cout<<"Hit: "<<fifo.hit<<" Miss: "<<fifo.miss<<endl;
    return 0;
}


























// #include <iostream>
// #include <queue>
// #include <unordered_set>
// #include <vector>
// using namespace std;

// class FIFOPageReplacement {
// private:
//     queue<int> pageQueue; // To keep track of the order of pages in memory
//     unordered_set<int> pageSet; // To check if a page is in memory
//     vector<unordered_set<int>> memoryStates; // To store all memory states

// public:
//     void replacePage(int page, int capacity) {
//         if (pageSet.size() < capacity) {
//             if (pageSet.find(page) == pageSet.end()) {
//                 pageSet.insert(page);
//                 pageQueue.push(page);
//             }
//         } else {
//             int oldestPage = pageQueue.front();
//             pageQueue.pop();

//             // Remove the oldest page from the set
//             pageSet.erase(oldestPage);

//             // Add the new page to both the set and the queue
//             pageSet.insert(page);
//             pageQueue.push(page);
//         }

//         // Save the current memory state
//         memoryStates.push_back(pageSet);
//     }

//     void displayMemoryStates() {
//         cout << "All Memory States: " << endl;
//         for (const auto& state : memoryStates) {
//             for (int page : state) {
//                 cout << page << " ";
//             }
//             cout << endl;
//         }
//     }
// };

// int main() {
//     FIFOPageReplacement fifo;
//     int capacity = 3; // Capacity of the page frame

//     // Page reference sequence
//     int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

//     for (int i = 0; i < sizeof(pages) / sizeof(pages[0]); ++i) {
//         fifo.replacePage(pages[i], capacity);
//     }

//     fifo.displayMemoryStates();

//     return 0;
// }
