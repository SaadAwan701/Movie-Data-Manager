#pragma once
#include <iostream>
using namespace std;

template <typename T>
class QueueNode{
public:
    T data;
    QueueNode* next;
    QueueNode(T val):data(val), next(nullptr){}
};

template<typename T>
class Queue{
    QueueNode<T>* front;
    QueueNode<T>* rear;
public:
    Queue():front(nullptr), rear(nullptr){}
    ~Queue(){
        while(!isEmpty()){
            dequeue();
        }
    }

    bool isEmpty(){
        return front == nullptr;
    }

    void enqueue(T val){
        QueueNode<T>* newelement = new QueueNode<T>(val);
        if(rear==nullptr){
            front = rear = newelement;
            return;
        }
        rear->next = newelement;
        rear = newelement;
    }

    T dequeue(){
        if(front==nullptr){
            return nullptr;
        }
        QueueNode<T>* temp = front;
        T val = front->data;
        front = front->next;
        if(front==nullptr){
            rear = nullptr;
        }
        delete temp;
        return val;
    }
};