#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "movie_avl.h"
#include "hashTable.h"
#include "LL.h"
using namespace std;

string trim(string& str) {
    if (str.empty()) return "";
    
    string clean = "";
    for(char c : str) {
        if((unsigned char)c >= 32 && (unsigned char)c < 127) {
            clean += c;
        }
    }
    
    size_t first = clean.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    
    size_t last = clean.find_last_not_of(" \t\r\n");
    return clean.substr(first, (last - first + 1));
}

void splitGenres(string unSplitGenres, LinkedList<string> &list){
    stringstream ss(unSplitGenres);
    string genre;
    while(getline(ss, genre, '|')){
        string clean = trim(genre);
        if(!clean.empty())
            list.insert(clean);
    }
}

void fillGenres(string genreName, MovieNode* movie, HashTable<GenreNode*>& genreMovies){
    if(genreName.empty())   return;

    GenreNode* genre = genreMovies.search(genreName);
    if(genre==nullptr){
        genre = new GenreNode(genreName);
        genreMovies.insert(genreName, genre);
    }
    genre->addMovie(movie);
}

void fillActors(string name, MovieNode* movie, HashTable<ActorNode*>& actorMovies){
    if(name.empty())    return;

    ActorNode* actor = actorMovies.search(name);
    if(actor == nullptr){
        actor = new ActorNode(name);
        actorMovies.insert(name, actor);
    }
    actor->addMovie(movie);
}

void fillDirectors(string name, MovieNode* movie, HashTable<DirectorNode*>& directorMovies){
    if(name.empty())    return;

    DirectorNode* director = directorMovies.search(name);
    if(director == nullptr){
        director = new DirectorNode(name);
        directorMovies.insert(name, director);
    }
    director->addMovie(movie);
}

void read_parse(string filename, MovieAVL &tree, HashTable<ActorNode*> &actorTable,
                HashTable<GenreNode*> &genreTable, HashTable<DirectorNode*> &directorTable){
    ifstream file(filename);
    if(!file.is_open()){
        cout<<"CAould'nt open file!"<<endl;
        return;
    }
    string line;

    getline(file, line);
int count = 0;
    while (getline(file, line)){           
        string directors_name, actor_2_name, genres, actor_1_name, movie_title, actor_3_name, normalized_title;
        int title_year = 0;
        double imdb = 0.0;

        stringstream ss(line);

        for(int i=0; i<28; i++){
            string temp ;
            if(ss.peek() == '"'){
                ss.get();
                getline(ss, temp, '"');
                if(ss.peek() == ','){
                    ss.get();
                }
            }else{
                getline(ss, temp, ',');
            }
            if(i==1)
                directors_name = trim(temp);
            else if (i==6)
                actor_2_name = trim(temp);
            else if(i==9)
                genres = trim(temp);
            else if(i==10)
                actor_1_name = trim(temp);
            else if(i==11){
                movie_title = trim(temp);
                normalized_title = normalizeTitle(movie_title);
            }
            else if(i==14)
                actor_3_name = trim(temp);
            else if(i==23)
                try{
                    title_year = stoi(temp);
                }catch(...){
                    title_year = 0;
                }
            else if(i==25)
                try{
                    imdb = stod(temp);
                }catch(...){
                    imdb = 0.0;
                }
        }
        if(movie_title.empty()){
            continue;
        }

        if(tree.search(normalized_title) != nullptr){
            continue;
        }

        MovieNode* moviePtr = new MovieNode(movie_title, normalized_title, directors_name, title_year, imdb);
        if(!actor_1_name.empty()){
            moviePtr->actors.insert(actor_1_name);
        }
        if(!actor_2_name.empty()){
            moviePtr->actors.insert(actor_2_name);
        }
        if(!actor_3_name.empty()){
            moviePtr->actors.insert(actor_3_name);
        }
        splitGenres(genres, moviePtr->genres);
        tree.insert(moviePtr);
        MovieNode* ptr = tree.search(normalized_title);
        if(ptr!=nullptr){
            fillActors(actor_1_name, ptr, actorTable);
            fillActors(actor_2_name, ptr, actorTable);
            fillActors(actor_3_name, ptr, actorTable);

            actor_genre<string>* gNode = ptr->genres.getHead();
            while (gNode != nullptr){
                fillGenres(gNode->data, ptr, genreTable);
                gNode = gNode->next;
            }

            fillDirectors(directors_name, ptr, directorTable);
            count++;
        }
    }
    file.close();
}