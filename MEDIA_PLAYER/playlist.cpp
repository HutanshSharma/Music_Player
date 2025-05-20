#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    string songname;
    node* next;
    node* prev;

    node(string a){
        songname=a;
        next=nullptr;
        prev=nullptr;
    }
};

class Playlist{
    public:
    node* head;
    node* curr;

    Playlist(){
        head=nullptr;
        curr=nullptr;
    }

    void addMedia_atlast(string songname){
        if(head==nullptr){
            node* newnode=new node(songname);
            head=newnode;
            newnode->next=newnode;
            newnode->prev=newnode;
            curr=newnode;
            return;
        }
        node *ptr=head->prev;
        node* newnode=new node(songname);
        ptr->next=newnode;
        newnode->next=head;
        newnode->prev=ptr;
        head->prev=newnode;
        return;
    }

    void nextTrack(){
        if(head==nullptr){
            cout<<"Empty Playlist"<<endl;
            return;
        }
        curr=curr->next;
    }

    void previousTrack(){
        if(head==nullptr){
            cout<<"Empty Playlist"<<endl;
            return;
        }
        curr=curr->prev;
    }

    void showPlaylist(){
        if(head==nullptr){
            cout<<"Empty Playlist";
            return;
        }
        node* ptr=head;
        do{
            if(ptr==curr) cout<<"The current song is ";
            string temp=ptr->songname.substr(9,ptr->songname.size());
            cout<<temp<<endl;
            ptr=ptr->next;
        }
        while(ptr!=head);
    }

    int number_of_songs(){
        if(head==nullptr) return 0;
        node*ptr=head;
        int count=0;
        do{
            count++;
            ptr=ptr->next;
        }
        while(ptr!=head);
        return count;
    }

    int deleteMedia(string songname) {
        if(head==nullptr){
            return 0;
        }
        node* ptr=head;
        node* toDelete=nullptr;
        do {
        if(ptr->songname==songname){
            toDelete=ptr;
            break;
        }
        ptr=ptr->next;
        }while(ptr!=head);

        if(toDelete==nullptr){
            return 1;
        }

        if(toDelete->next==toDelete){
            delete(toDelete);
            head=nullptr;
            curr=nullptr;
            return 2;
        }
        bool flag=false;
        if(toDelete==head)
            head=head->next;
        if(toDelete==curr){
            flag=true;
            curr=curr->next;
        }
        toDelete->prev->next=toDelete->next;
        toDelete->next->prev=toDelete->prev;
        delete(toDelete);
        if(flag) return 3;
        return 4;
    }

    void getCurrentSong(){
        if(curr==nullptr){
            cout<<"No song is playing";
            return;
        }
        string temp=curr->songname.substr(9,curr->songname.size());
        cout<<temp<<endl;
        return;
    }

    int getsize(){
        if(head==nullptr) return 0;
        int count=0;
        node* ptr=head;
        do{
            count++;
            ptr=ptr->next;
        }while(ptr!=head);
        return count;
    }

};
