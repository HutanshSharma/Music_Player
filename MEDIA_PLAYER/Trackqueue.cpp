#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class TrackQueue{
    public:
    deque<string>q1;

    void enqueue(string songname){
        q1.push_back(songname);
        string s=songname.substr(9,songname.size());
        cout<<s<<" has been added to the playlist"<<endl;
    }

    void dequeue(){
        if(q1.empty()){
            return;
        }
        string temp=q1.front();
        q1.pop_front();
    }

    bool isEmpty(){
        return q1.empty();
    }

    void pushtofront(string songname){
        q1.push_front(songname);
        string temp=songname.substr(9,songname.size());
        cout<<temp<<" has been added back to the front of the queue"<<endl;  
    }

    string front(){
        if(!q1.empty()) return q1.front();
        return "The queue is empty";
    }

    void deletefromqueue(string name){
        queue<string>temp;
        while(!q1.empty()){
            if(q1.front()==name){
                q1.pop_front();
            }
            else{
                temp.push(q1.front());
                q1.pop_front();
            }
        }
        while(!temp.empty()){
            q1.push_back(temp.front());
            temp.pop();
        }
    }

    void showqueue(){
        if(q1.empty()) cout<<"queue is empty";
        queue<string>temp;
        while(!q1.empty()){
            string s=q1.front().substr(9,q1.front().size());
            cout<<s<<endl;
            temp.push(q1.front());
            q1.pop_front();
        }
        while(!temp.empty()){
            q1.push_back(temp.front());
            temp.pop();
        }
    }

    void clearqu(){
        q1.clear();
    }

    int size(){
        return q1.size();
    }
};
