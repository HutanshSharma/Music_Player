#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class SongHistoryStack{
    public:
    stack<string>s1;

    void push(string songname){
        s1.push(songname);
        string temp=songname.substr(9,songname.size());
        cout<<temp<<" has been added in the history"<<endl;
    }

    void pop(){
        if(s1.empty()){
            cout<<"No song has been played";
            return ;
        }
        string temp=s1.top();
        s1.pop();
    }

    void clearst(){
        while(!s1.empty()){
            s1.pop();
        }
    }

    void deletefromstack(string val){
        if(s1.empty()) return;
        if(s1.top()==val){
            s1.pop();
            return;
        }
        string temp=s1.top();
        s1.pop();
        deletefromstack(val);
        s1.push(temp);
    }

    int size(){
        return s1.size();
    }

    void showhistory(){
        if(s1.empty()) return;
        string temp=s1.top();
        string s=temp.substr(9,temp.size());
        cout<<s<<endl;
        s1.pop();
        showhistory();
        s1.push(temp);
    }

    bool isEmpty(){
        return s1.empty();
    }
};
