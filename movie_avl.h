#pragma once
#include <iostream>
#include "LL.h"
using namespace std;

int maximun(int h1, int h2){
   return (h1>h2)? h1:h2; 
}

string normalizeTitle(string title) {
    if (title.empty()) return "";
    string cleaned = "";
    for (char c : title) {
        if ((unsigned char)c >= 32 && (unsigned char)c < 127) {
            cleaned += c;
        }
    }    
    if (cleaned.empty())
        return "";

    size_t start = cleaned.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    size_t end = cleaned.find_last_not_of(" \t\r\n");
    string trimmed = cleaned.substr(start, end - start + 1);

    for (char& c : trimmed) {
        c = tolower(c);
    }    
    return trimmed;
}

// ===== Movie Class =====
class MovieNode
{
public:
    string movieTitle;      // movie title
    string movieTitleNormalized;    //without weird i mean letters or spaces
    string director;
    int visited;
    LinkedList<string>  actors;
    LinkedList<string>  genres;
    int title_year;
    double imdb_score;
    MovieNode* parent;

    MovieNode() : movieTitle(""), director(""), title_year(0), imdb_score(0.0), visited(0), parent(nullptr){}
    MovieNode(string mt, string d, int t, double imdb) : movieTitle(mt), director(d), title_year(t), imdb_score(imdb), visited(0), parent(nullptr){}
    MovieNode(string displayTitle, string normTitle, string d, int t, double imdb): movieTitle(displayTitle), movieTitleNormalized(normTitle),
          director(d), title_year(t), imdb_score(imdb), visited(0), parent(nullptr) {}

    void display(){
        cout<<movieTitle<<" | "<<director<<endl;
        cout<<"Actors: ";
        actors.display();
        cout<<"Genres: ";
        genres.display();
        cout<<"---------------------------------------------------------"<<endl;
    }
};

// ===== AVL Node Class =====
class AVLNode
{
public:
    MovieNode* movie;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(MovieNode* g) : movie(g), left(nullptr), right(nullptr), height(1) {}
};

// ===== AVL Class =====
class MovieAVL
{
private:
    AVLNode* root;
    int nodeCount;
    AVLNode* rightRotation(AVLNode* y){
        if (!y || !y->left) return y;
        AVLNode* x = y->left;
        AVLNode* rightSub = x->right;

        x->right = y;
        y->left = rightSub;

        int y_leftHeight = (y->left ? y->left->height : 0);
        int y_rightHeight = (y->right ? y->right->height : 0);
        
        int x_leftHeight = (x->left ? x->left->height : 0);
        int x_rightHeight = (x->right ? x->right->height : 0);

        y->height = 1 + maximun(y_leftHeight, y_rightHeight);
        x->height = 1 + maximun(x_leftHeight, x_rightHeight);

        return x;
    }

    AVLNode* leftRotation(AVLNode* y){
        if (!y || !y->right) return y;
        AVLNode* x = y->right;
        AVLNode* leftSub = x->left;

        x->left = y;
        y->right = leftSub;

        int y_leftHeight = (y->left ? y->left->height : 0);
        int y_rightHeight = (y->right ? y->right->height : 0);
        
        int x_leftHeight = (x->left ? x->left->height : 0);
        int x_rightHeight = (x->right ? x->right->height : 0);

        y->height = 1 + maximun(y_leftHeight, y_rightHeight);
        x->height = 1 + maximun(x_leftHeight, x_rightHeight);

        return x;
    }

    AVLNode* insert(AVLNode* node, MovieNode* m){
        if (node == nullptr) {
            AVLNode* newele = new AVLNode(m);
            nodeCount++;
            return newele;
        }
        if (node->movie->movieTitleNormalized < m->movieTitleNormalized) {
            node->right = insert(node->right, m);
        }
        else if (node->movie->movieTitleNormalized > m->movieTitleNormalized) {
            node->left = insert(node->left, m);
        }else{
            return node;
        }
        int NLheight = (node->left)? node->left->height:0;
        int NRheight = (node->right)? node->right->height:0;
        node->height = 1 + maximun(NLheight, NRheight);

        int balance = (NLheight - NRheight);

        if(balance>1){
            if(m->movieTitleNormalized < node->left->movie->movieTitleNormalized){
                //LL
                return rightRotation(node);
            }else if(m->movieTitleNormalized > node->left->movie->movieTitleNormalized){
                //RR
                node->left = leftRotation(node->left);
                //LL
                return rightRotation(node);
            }
        }else if(balance<-1){
            if(m->movieTitleNormalized > node->right->movie->movieTitleNormalized){
                //RR
                return leftRotation(node);
            }else if(m->movieTitleNormalized < node->right->movie->movieTitleNormalized){
                //LL
                node->right = rightRotation(node->right);
                //RR
                return leftRotation(node);
            }
        }
        return node;
    }

    void inorder(AVLNode* node)
    {
        if (!node)
            return;
        inorder(node->left);
        node->movie->display();
        inorder(node->right);
    }

    int balance(AVLNode* node){
        
        int NLheight = (node->left)? node->left->height:0;
        int NRheight = (node->right)? node->right->height:0;

        return (NLheight - NRheight);
    }

    AVLNode* deleteByName(AVLNode* node, string movie){
        if(node==nullptr){
            return nullptr;
        }
        if(movie < node->movie->movieTitle){
            node->left = deleteByName(node->left, movie);
        }else if(movie>node->movie->movieTitle){
            node->right = deleteByName(node->right, movie);
        }else{
            if(node->right==nullptr && node->left==nullptr){
                delete node;
                return nullptr;
            }else if(node->left == nullptr){
                AVLNode* temp = node->right;
                delete node;
                return temp;
            }else if(node->right == nullptr){
                AVLNode* temp = node->left;
                delete node;
                return temp;
            }else{
                AVLNode* sucessor = node->right;
                while(sucessor->left!=nullptr){
                    sucessor = sucessor->left;
                }
                node->movie = sucessor->movie;

                node->right = deleteByName(node->right, sucessor->movie->movieTitle);
            }
        }
        int NLheight = (node->left)? node->left->height:0;
        int NRheight = (node->right)? node->right->height:0;

        node->height = 1 + maximun(NLheight, NRheight);
        

        int bal = balance(node);

        if(bal>1){
            if((balance(node->left))>=0){
                //RR
                return rightRotation(node);
            }else if((balance(node->left)) < 0){
                //LR
                node->left = leftRotation(node->left);
                //RR
                return rightRotation(node);
            }
        }else if(bal<-1){
            if((balance(node->right)) <=0 ){
                //LR
                return leftRotation(node);
            }else if((balance(node->right)) > 0){
                //RR
                node->right = rightRotation(node->right);
                //LR
                return leftRotation(node);
            }
        }
        return node;
    }

    MovieNode* searchHelper(AVLNode* node, string title) {
        if (node == nullptr) return nullptr;

        if (node->movie->movieTitleNormalized == title)
            return node->movie;
    
        if (title < node->movie->movieTitleNormalized)
            return searchHelper(node->left, title);
        else
            return searchHelper(node->right, title);
}

    void deleteTree(AVLNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node->movie;   // free the movie object
        delete node;
    }
public:
    MovieAVL() : root(nullptr), nodeCount(0) {}
    ~MovieAVL(){    deleteTree(root); }
    void insert(MovieNode* g)
    {
        root = insert(root, g);
    }

    void displayMovies()
    {
        cout << "\n=== Movies (sorted by Title) ===\n";
        inorder(root);
    }

    void searchByName(string name) {        
        string normal = normalizeTitle(name);
        MovieNode* movie = searchHelper(root, normal); 
        if (movie)
            movie->display();
        else
            cout << "Movie not found" << endl;
    }

    MovieNode* search(string title) {
        string normal = normalizeTitle(title);
        return searchHelper(root, normal);
    }
    
    int getSize(){
        return nodeCount;
    }
};