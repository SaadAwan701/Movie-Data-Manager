#pragma once
#include <iostream>
#include "Queue.h"
#include "hashtable.h"
#include "movie_avl.h"
using namespace std;

class graph{
    HashTable<ActorNode*>* actorTable;
    HashTable<DirectorNode*>* directorTable;
    HashTable<GenreNode*>* genreTable;
public:
    graph(HashTable<ActorNode*>& actors, HashTable<DirectorNode*>& directors,
          HashTable<GenreNode*>& genres){
            actorTable = &actors;
            directorTable = &directors;
            genreTable = &genres;
          }

    void Recommendations(MovieNode* start, int limit = 7){
        if(start == nullptr){
            return;
        }

        cout<<"Recommended movies just like "<<start->movieTitle<<endl;

        Queue<MovieNode*> movieQ;
        static int searchID = 0;
        searchID++;

        start->visited = searchID;
        movieQ.enqueue(start);
        int count = 0;

        while(!movieQ.isEmpty()){
            MovieNode* curr = movieQ.dequeue();

            if(curr!=start){
                count++;
                cout<<count<<". "<<curr->movieTitle<<" - "<<curr->title_year<<" IMDB score: "<<curr->imdb_score<<endl;
            }
            if (count>= limit){
                return;
            }
            // cheking for directors connections
            if(!curr->director.empty()){
                DirectorNode* director = directorTable->search(curr->director);

                if(director != nullptr && director->visited != searchID){
                    director->visited = searchID;

                    actor_genre<MovieNode*>* movies = director->movies.getHead();
                    while(movies != nullptr){
                        MovieNode* neighbor = movies->data;
                        if(neighbor->visited != searchID){
                            neighbor->visited = searchID;
                            movieQ.enqueue(neighbor);
                        }
                        movies = movies->next;
                    }
                }
            }
            //cheking for actors connections
            actor_genre<string>* MovieactorLL = curr->actors.getHead();
            while(MovieactorLL != nullptr){
                ActorNode* actor = actorTable->search(MovieactorLL->data);

                if(actor != nullptr && actor->visited!= searchID){
                    actor->visited = searchID;

                    actor_genre<MovieNode*>* movies = actor->movies.getHead();
                    while(movies != nullptr){
                        MovieNode* neighbour = movies->data;
                        if(neighbour->visited != searchID){
                            neighbour->visited = searchID;
                            movieQ.enqueue(neighbour);
                        }
                        movies = movies->next;
                    }
                }
                MovieactorLL = MovieactorLL->next;
            }

            //cheking for genres idk why dont make sense to me but pdf said
            //only if limit not reached
            if(count<limit){
                actor_genre<string>* MoviegenreLL = curr->genres.getHead();
                while(MoviegenreLL!=nullptr){
                    GenreNode* genre = genreTable->search(MoviegenreLL->data);

                    if(genre != nullptr && genre->visited!=searchID){
                        genre->visited = searchID;

                        actor_genre<MovieNode*>* movies = genre->movies.getHead();
                        while(movies!=nullptr){
                            MovieNode* neighbour = movies->data;
                            if(neighbour->visited  != searchID){
                                neighbour->visited = searchID;
                                movieQ.enqueue(neighbour);
                            }
                            movies = movies->next;
                        }
                    }
                    MoviegenreLL = MoviegenreLL->next;
                }
            }
        }
    }

    void shortestPathBetweenMovies(MovieNode* start, MovieNode* end){
        if(start == nullptr || end == nullptr){
            return;
        }
        cout << "Searching for path from '" << start->movieTitle << "' to '" << end->movieTitle << "'...\n";
        Queue<MovieNode*> movieQ;
        static int searchID = 0;
        searchID++;

        start->visited = searchID;
        start->parent = nullptr;
        movieQ.enqueue(start);

        bool found = false;

        while (!movieQ.isEmpty()){
            MovieNode* curr = movieQ.dequeue();

            if(curr == end){
                found = true;
                break;
            }

            if(!curr->director.empty()){
                DirectorNode* director = directorTable->search(curr->director);

                if(director != nullptr && director->visited != searchID){
                    director->visited = searchID;

                    actor_genre<MovieNode*>* movies = director->movies.getHead();
                    while(movies != nullptr){
                        MovieNode* neighbor = movies->data;
                        if(neighbor->visited != searchID){
                            neighbor->visited = searchID;
                            neighbor->parent = curr;
                            movieQ.enqueue(neighbor);
                        }
                        movies = movies->next;
                    }
                }
            }
            //cheking for actors connections
            actor_genre<string>* MovieactorLL = curr->actors.getHead();
            while(MovieactorLL != nullptr){
                ActorNode* actor = actorTable->search(MovieactorLL->data);

                if(actor != nullptr && actor->visited!= searchID){
                    actor->visited = searchID;

                    actor_genre<MovieNode*>* movies = actor->movies.getHead();
                    while(movies != nullptr){
                        MovieNode* neighbour = movies->data;
                        if(neighbour->visited != searchID){
                            neighbour->visited = searchID;
                            neighbour->parent = curr;
                            movieQ.enqueue(neighbour);
                        }
                        movies = movies->next;
                    }
                }
                MovieactorLL = MovieactorLL->next;
            }

            //cheking for genres idk why dont make sense to me but pdf said
            //only if limit not reached
            actor_genre<string>* MoviegenreLL = curr->genres.getHead();
            while(MoviegenreLL!=nullptr){
                GenreNode* genre = genreTable->search(MoviegenreLL->data);

                if(genre != nullptr && genre->visited!=searchID){
                    genre->visited = searchID;

                    actor_genre<MovieNode*>* movies = genre->movies.getHead();
                    while(movies!=nullptr){
                        MovieNode* neighbour = movies->data;
                        if(neighbour->visited  != searchID){
                            neighbour->visited = searchID;
                            neighbour->parent = curr;
                            movieQ.enqueue(neighbour);
                        }
                        movies = movies->next;
                    }
                }
                MoviegenreLL = MoviegenreLL->next;
            }            
        }
        if(found){
            cout << "Path found: ";
            printPath(end);
            cout << endl;
        } else {
            cout << "No connection found between these movies." << endl;
        }
    }

    void printPath(MovieNode* curr) {
        if (curr == nullptr) return;
        printPath(curr->parent); 
        if(curr->parent!=nullptr)
            cout << " -> ";
        cout<< curr->movieTitle;
    }
};