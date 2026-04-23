#pragma once
#include <iostream>
#include "LL.h"
#include "movie_avl.h"
using namespace std;

struct ActorNode{
    string name;
    LinkedList<MovieNode*> movies;
    int visited;

    ActorNode(string n):name(n), visited(0){}
    void addMovie(MovieNode* movie){
        movies.insert(movie);
    }
    void display(){
        cout << "Actor: " << name << endl;
        cout << "Movies:\n";
        
        actor_genre<MovieNode*>* curr = movies.getHead();
        int count = 0;
        while(curr != nullptr){
            cout << "  " << ++count << ". " << curr->data->movieTitle 
                 << " (" << curr->data->title_year << ")" << endl;
            curr = curr->next;
        }
    }
};

struct DirectorNode{
    string name;
    LinkedList<MovieNode*> movies;
    int visited;

    DirectorNode(string n):name(n), visited(0){}
    void addMovie(MovieNode* movie){
        movies.insert(movie);
    }
    void display(){
        cout << "Director: " << name << endl;
        cout << "Movies:\n";
        
        actor_genre<MovieNode*>* curr = movies.getHead();
        int count = 0;
        while(curr != nullptr){
            cout << "  " << ++count << ". " << curr->data->movieTitle 
                 << " (" << curr->data->title_year << ")" << endl;
            curr = curr->next;
        }
    }
};

struct GenreNode{
    string name;
    LinkedList<MovieNode*> movies;
    int visited;

    GenreNode(string n):name(n), visited(0){}
    void addMovie(MovieNode* movie){
        movies.insert(movie);
    } 
    void display(){
        cout<<"Genre: "<<name<<endl;
        cout<<"Movies in this genre:\n";
        actor_genre<MovieNode*>* curr = movies.getHead();
         int count = 0;
        while(curr != nullptr){
            cout << "  " << ++count << ". " << curr->data->movieTitle 
                 << " (" << curr->data->title_year << ")" << endl;
            curr = curr->next;
        }
    }
};

template <typename T>
struct HashItem {
    string key;
    T value;
    HashItem():key(""), value(nullptr){}
    HashItem(string k, T v):key(k), value(v){}
};

template <typename T>
class HashTable {
private:
    LinkedList<HashItem<T>>* table;
    int cap;
    int size;
    //djb2  hash
    int getHash(string key){
        unsigned int hash = 5381;
        for (int i = 0; i < key.length(); i++) {
            hash = ((hash << 5) + hash) + key[i];
        }
        return hash % cap;
    }

public:
    HashTable(int c = 5000) {
        cap = c;
        size = 0;
        table = new LinkedList<HashItem<T>>[cap];
    }

    void insert(string key, T val) {
        int getKey = getHash(key);
        HashItem<T> item(key, val);
        table[getKey].insert(item);
        size++;
    }

    T search(string key) {
        int getKey = getHash(key);
        actor_genre<HashItem<T>>* curr = table[getKey].getHead();

        while (curr != nullptr) {
            if (curr->data.key == key) {
                return (curr->data.value);
            }
            curr = curr->next;
        }
        return nullptr;
    }
};