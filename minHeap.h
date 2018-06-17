//
// Created by 123yt on 12/06/2018.
//
#ifndef HW3_MINHEAP_H
#define HW3_MINHEAP_H

#include <iostream>
#include <cassert>

template <class T>
class minHeap{
public:
    int maxSize;
    int numofElements;
    T *heap;

    void siftDown(int my_father){
        int left = my_father*2 +1;
        int right = my_father*2 + 2;
        if(left >= this->numofElements) {
            return;
        }
        if(right >= this->numofElements)  {
            if(heap[left] < heap[my_father]) {
                swap(left, my_father);
            }
            return;

        }
        T leftSon, rightSon, father;
        leftSon = this->heap[left];
        rightSon = this->heap[right];
        father = this->heap[my_father];
        if(leftSon < father   || rightSon < father ) {
            if (leftSon < rightSon) {
                swap(my_father, left);
                my_father = left;
            } else{
                swap(my_father, right);
                my_father = right;
            }
            siftDown(my_father);
        }
        return;
    }
    void makeHeap(){
        for(int i = (numofElements)/2; i >= 0 ; i--){
            siftDown(i);
        }
    }
    void siftUp(int son){
        int father = (son-1)/2;
        while (son > 0 && (heap[son] < heap[father])){
            swap(son, father);
            son = father;
            father = (son-1)/2;
        }
    }
    void incSizeHeap(int size){
        T *tmptree = new T[size];
        for(int i = 0; i < this->numofElements; i++){
            tmptree[i] = heap[i];
        }
        delete[] heap;
        heap = tmptree;
        this->maxSize = size;
    }
    void swap(int i,int j) {
        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }
public:
    int getHeapSize(){
        return this->maxSize;
    }
    int getNumofElements() {
        return this->numofElements;
    }
    T* getActualHeap(){
        return this->heap;
    }
    T getMin(){
        return this->heap[0];
    }
    minHeap():maxSize(0), numofElements(0), heap(){}
    minHeap(T* array, int size) : maxSize(size*2), numofElements(size) {

        heap = new T[this->maxSize];
        for( int i = 0; i < this->numofElements ; i++ ){
            heap[i] = array[i];
        }
        makeHeap();
    }
    minHeap(int size):maxSize(size), numofElements(0){
        this->heap = new T[size];
    }
    void insert(T* element){
        heap[this->numofElements] = *element;
        this->siftUp(this->numofElements);
        this->numofElements++;
        if(this->numofElements == this->maxSize){
            incSizeHeap(this->maxSize*2);
        }
    }
    void remove(T* el_to_remove) {
        int index_to_remove = 0;
        for(int i = 0; i< this->numofElements; i++){
            if(heap[i] == *el_to_remove){
                index_to_remove = i;
            }
        }
        swap(0,index_to_remove);
        this->delMin();
    }

    void delMin(){
        swap(0, this->numofElements-1);
        this->numofElements--;
        siftDown(0);
        if(this->numofElements == this->maxSize/4){
            incSizeHeap(this->maxSize/2+1);
        }
    }
    ~minHeap(){
        delete[] heap;
    };
    //void decKey(int place, T key_value);

};

#endif //HW3_MINHEAP_H
