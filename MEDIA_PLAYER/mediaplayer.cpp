#define SDL_MAIN_HANDLED

#include <iostream>
#include <bits/stdc++.h>
#include <SDL.h>          
#include <SDL_mixer.h>  
#include <filesystem>  
#include "playlist.cpp"
#include "SongHistory.cpp"
#include "Trackqueue.cpp"
using namespace std;
namespace fs=std::filesystem;

class mediaplayer;
extern mediaplayer* g_player;
void songendedcall();

class mediaplayer{
public:
    Playlist playlist;
    SongHistoryStack s1;
    TrackQueue q1;
    bool isPlaying;
    bool isPaused;
    Mix_Music* music=nullptr;

    mediaplayer(){
        isPlaying=false;
        isPaused=true;

        if(SDL_Init(SDL_INIT_AUDIO)<0) {
            cout<<"SDL could not initialize! SDL Error: "<<SDL_GetError()<<endl;
        }

        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0) {
            cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError()<<endl;
        }

        Mix_HookMusicFinished(songendedcall);
    }

    ~mediaplayer(){
        Mix_FreeMusic(music);   
        Mix_CloseAudio();
        SDL_Quit();
    }

    void onSongEnded(){
        isPlaying=false;
        isPaused=true;
        next();
    }

    bool is_song_present(string &song){
        string path="../songs/"+song;
        return fs::exists(path);
    }

    void addToQueue(string song) {
        if(!is_song_present(song)){
            cout<<"Song not found consider checking the spellings"<<endl;
            return;
        }

        string s="../songs/"+song;
        q1.enqueue(s);
        playlist.addMedia_atlast(s);
    }

    void next(){
        if(q1.isEmpty()){
            cout<<"Playlist is empty"<<endl;
            return;
        }
        bool check=isPaused;
        if(!check) pause();
        string temp=playlist.curr->songname;
        playlist.nextTrack();
        s1.push(temp);
        if(!q1.isEmpty())q1.dequeue();

        if(s1.size()==playlist.getsize()) {
            cout<<"End of playlist reached"<<endl;
            cout<<"Wanna replay? (y/n): ";
            char a;
            cin>>a;
            if (a=='y'||a=='Y') {
                q1.clearqu();
                s1.clearst();
                playlist.curr=playlist.head;
                node* ptr=playlist.head;
                do{
                    q1.enqueue(ptr->songname);
                    ptr=ptr->next;
                } while(ptr!=playlist.head);
            }else{
                cout<<"Stopping"<<endl;
                isPlaying=false;
                return;
            }
        }
        play();

    }

    void previous(){
        if(s1.isEmpty()){
            cout<<"No previous song in history"<<endl;
            return;
        }
        pause();
        string temp=playlist.curr->songname;
        q1.pushtofront(temp);
        playlist.previousTrack();
        s1.pop();

        play();
    }

    void play(){
        if(playlist.curr==nullptr) {
            cout<<"No song to play"<<endl;
            return;
        }
        string temp=playlist.curr->songname.substr(9,playlist.curr->songname.size());
        if(isPlaying && !isPaused){
            cout<<"Already playing: "<<temp<<endl;
            return;
        }

        if(music != nullptr) {
            Mix_FreeMusic(music);
            music=nullptr;
        }

        string filepath=playlist.curr->songname;
        music=Mix_LoadMUS(filepath.c_str());
        if(!music){
            cout<<"Failed to load music: "<<Mix_GetError()<<endl;
            return;
        }
        if(q1.front()==playlist.curr->songname) q1.dequeue();
        cout<<"Playing: "<<temp<<endl;
        Mix_PlayMusic(music, 1);

        isPlaying=true;
        isPaused=false;
    }

    void pause(){
        string temp=playlist.curr->songname.substr(9,playlist.curr->songname.size());
        if(isPlaying && !isPaused) {
            Mix_PauseMusic();
            cout<<"Paused: "<<temp<<endl;
            isPaused=true;
        }else{
            cout<<"Already paused"<<endl;
        }
    }

    void update(){
        if(isPlaying && !Mix_PlayingMusic()) {
            isPaused=true;
            isPlaying=false;
            next();
        }
    }

    void songscount(){
        cout<<"The total songs in the playlist are "<<playlist.number_of_songs();
    }

    void deletesong(string name){
        if(!is_song_present(name)){
            cout<<"Song not found consider checking the spellings"<<endl;
            return;
        }
        bool check=isPaused;
        if(!check) pause();
        int a=playlist.deleteMedia("../songs/"+name);
        if(a==0) {
            cout<<"Empty Playlist"<<endl;
            return;
        }
        else if(a==1) {
            cout<<"Song not in the Playlist"<<endl;
            return;
        }
        else if(a==2){
            s1.clearst();
            q1.clearqu();
            cout<<"Playlist has been emptied";
            return;
        }
        else if(a==3){
            q1.dequeue();
            cout<<"The current song was deleted"<<endl;
        }
        else if(a==4){
            s1.deletefromstack("../songs/"+name);
            q1.deletefromqueue("../songs/"+name);
            cout<<"The song has been deleted"<<endl;
        }
        if(!check) play();
    }
};

mediaplayer* g_player=nullptr;

void songendedcall(){
    if(g_player){
        g_player->onSongEnded();
    }
}

int main() {
    mediaplayer mp;
    g_player=&mp;
    int choice;
    string song;

    while (true) {
        mp.update();

        cout<<"\n----- Media Player Menu -----\n";
        cout<<"1. Add Song to Playlist\n";
        cout<<"2. Play\n";
        cout<<"3. Pause\n";
        cout<<"4. Next Track\n";
        cout<<"5. Previous Track\n";
        cout<<"6. Show Playlist\n";
        cout<<"7. Delete a song from the Playlist\n";
        cout<<"8. Show history\n";
        cout<<"9. Show queue\n";
        cout<<"10. Show Current Song\n";
        cout<<"11. Songs count\n";
        cout<<"12. Exit\n";
        cout<<endl;
        cout<<"Enter your choice: "<<endl;
        if (!(cin>>choice)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        switch (choice) {
        case 1:
            cout<<"Enter the song name (e.g., name.ogg or name.mp3): "<<endl;
            getline(cin, song);
            mp.addToQueue(song);
            break;
        case 2:
            mp.play();
            break;
        case 3:
            mp.pause();
            break;
        case 4:
            mp.next();
            break;
        case 5:
            mp.previous();
            break;
        case 6:
            mp.playlist.showPlaylist();
            break;
        case 7:
            cout<<"Enter the song name you want to delete (e.g., name.ogg or name.mp3)"<<endl;
            getline(cin,song);
            mp.deletesong(song);
            break;
        case 8:
            if(mp.s1.isEmpty()) cout<<"There is no history"<<endl;
            else mp.s1.showhistory();
            break;
        case 9:
            mp.q1.showqueue();
            break;
        case 10:
            mp.playlist.getCurrentSong();
            break;
        case 11:
            mp.songscount();
            break;
        case 12:
            cout << "Exiting media player...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        SDL_Delay(100);
    }
    return 0;
}