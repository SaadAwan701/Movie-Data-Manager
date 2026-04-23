#include <iostream>
#include "parsing.h"
#include "movie_avl.h"
#include "hashTable.h"
#include "graph.h"
using namespace std;

void searchSystem(string query, MovieAVL& tree, 
                  HashTable<ActorNode*>& actors, 
                  HashTable<DirectorNode*>& directors, 
                  HashTable<GenreNode*>& genres){
    string trimmedQuery = trim(query); 
    bool foundAny = false;

    cout << "\n-------------------------------------------------------";
    cout << "\nSearching database for: \"" << trimmedQuery << "\"\n";
    cout << "-------------------------------------------------------\n";
    MovieNode* movie = tree.search(trimmedQuery);
    if (movie != nullptr) {
        cout << "\n[MATCH FOUND] Movie Title" << endl;
        movie->display();
        foundAny = true;
    }
    DirectorNode* director = directors.search(trimmedQuery);
    if (director != nullptr) {
        cout << "\n[MATCH FOUND] Director" << endl;
        director->display(); // directors list of movies he directed
        foundAny = true;
    }
    ActorNode* actor = actors.search(trimmedQuery);
    if (actor != nullptr) {
        cout << "\n[MATCH FOUND] Actor" << endl;
        actor->display(); // list of movies actor acted in
        foundAny = true;
    }

    // 4. CHECK GENRES (Hash Table)
    GenreNode* genre = genres.search(trimmedQuery);
    if (genre != nullptr) {
        cout << "\n[MATCH FOUND] Genre" << endl;
        genre->display(); // list of genres of movies (alot)
        foundAny = true;
    }

    if (!foundAny) {
        cout << "\n[!] No records found for \"" << trimmedQuery << "\"." << endl;
        cout << "Tips:\n";
        cout << " - Movie titles are case-insensitive.\n";
        cout << " - Actors, Directors, and Genres are Case-Sensitive (e.g., use 'Action', not 'action').\n";
    }
}

int main() {
    string fName = "movie_metadata.csv";
    MovieAVL tree;
    HashTable<ActorNode*> actors;
    HashTable<GenreNode*> genres;
    HashTable<DirectorNode*> directors;

    cout << "=============================================" << endl;
    cout << "      IMDb MOVIE SYSTEM INITIALIZATION       " << endl;
    cout << "=============================================" << endl;
    cout << "Loading dataset from '" << fName << "'..." << endl;
    
    read_parse(fName, tree, actors, genres, directors);
    
    if (tree.getSize() == 0) {
        cout << "No movies loaded! Check csv path." << endl;
        return -1;
    }
    cout << "Database loaded successfully! Total Movies: " << tree.getSize() << endl;

    graph myGraph(actors, directors, genres);

    string input;
    string choice;

    while (true) {
        cout << "\n\n";
        cout << "=============================================" << endl;
        cout << "               MAIN MENU                     " << endl;
        cout << "=============================================" << endl;
        cout << "1. Universal Search (Movie, Actor, Director, Genre)" << endl;
        cout << "2. Get Movie Recommendations" << endl;
        cout << "3. Find Shortest Path" << endl;
        cout << "4. Exit" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Enter your choice (1-4): ";
        
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter Search Term (Movie Title, Actor Name, etc.): ";
            getline(cin, input);
            searchSystem(input, tree, actors, directors, genres);
        }
        else if (choice == "2") {
            cout << "Enter a movie you liked: ";
            getline(cin, input);
            MovieNode* m = tree.search(input);
            
            if (m != nullptr) {
                myGraph.Recommendations(m); 
            } else {
                cout << "[!] Movie not found. Please check spelling." << endl;
            }
        }
        else if (choice == "3") {
            string startTitle, endTitle;
            
            cout << "Enter Start Movie: ";
            getline(cin, startTitle);
            
            cout << "Enter Target Movie: ";
            getline(cin, endTitle);
            MovieNode* startNode = tree.search(startTitle);
            MovieNode* endNode = tree.search(endTitle);

            if (startNode != nullptr && endNode != nullptr) {
                myGraph.shortestPathBetweenMovies(startNode, endNode);
            } else {
                cout << "[!] Error: One or both movies were not found in the database." << endl;
                if(startNode == nullptr) cout << "    - '" << startTitle << "' is missing." << endl;
                if(endNode == nullptr)   cout << "    - '" << endTitle << "' is missing." << endl;
            }
        }
        else if (choice == "4" || choice == "exit" || choice == "EXIT") {
            cout << "Exiting system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid selection. Please enter a number 1-4." << endl;
        }
    }
    return 0;
}