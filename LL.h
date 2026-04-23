#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct actor_genre {
    T data;
    actor_genre* next;

    actor_genre(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class LinkedList {
private:
    actor_genre<T>* head;
    actor_genre<T>* tail;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;

    }
    
    LinkedList(const LinkedList& other){
        head = nullptr;
        tail = nullptr;
        actor_genre<T>* temp = other.head;
        while (temp!=nullptr){
            insert(temp->data);
            temp = temp->next;
        }
        
    }

    LinkedList& operator=(const LinkedList& other){
        if (this != &other){
            actor_genre<T>* current = head;
            while (current != nullptr) {
                actor_genre<T>* temp = current;
                current = current->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr;

            actor_genre<T>* temp = other.head;
            while (temp != nullptr) {
                insert(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    ~LinkedList() {
        actor_genre<T>* current = head;
        while (current != nullptr) {
            actor_genre<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void insert(T value) {
        actor_genre<T>* newactor_genre = new actor_genre<T>(value);
        if (head == nullptr) {
            head = newactor_genre;
            tail = newactor_genre;
        } 
        else {
            tail->next = newactor_genre;
            tail = newactor_genre;
        }
    }

    void display() const 
    {
        actor_genre<T>* temp = head;
        while (temp != nullptr) 
        {
            cout << temp->data;
            if (temp->next != nullptr)
            { cout << ", "; }
            temp = temp->next;
        }
        cout << endl;
    }

    void remove (T value){
        if(head == nullptr) return;
        if(head->data == value){
            actor_genre<T>* temp = head;
            head = head->next;
            if(head==nullptr){
                tail = nullptr;
            }
            delete temp;
            return;
        }

        actor_genre<T>* curr = head;
        while(curr->next != nullptr){
            if(curr->next->data == value){
                actor_genre<T>* temp = curr->next;

                curr->next =  temp->next;
                if(temp==tail)
                    tail = curr;

                delete temp;
                return;
            }
            curr = curr->next;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    
    actor_genre<T>* getHead() const {
        return head;
    }
};

