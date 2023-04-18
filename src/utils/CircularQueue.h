/**
 * @file CircularQueue.h
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Circular Queue Class 
 */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <iostream>


class CircularQueue {
    private:
        int front, rear;
        int size;
        int *queue;

    public:
        CircularQueue(int size) : front(0), rear(-1), size(size) {
            queue = new int[size];
        }

        ~CircularQueue() {
            delete[] queue;
        }

        void enqueue(int value) {
            rear = (rear + 1) % size;
            queue[rear] = value;
            
            // If the queue is full, update the front to overwrite the oldest element.
            if ((rear + 1) % size == front) {
                front = (front + 1) % size;
            }
        }

        int dequeue() {
            if (front == (rear + 1) % size) {
                std::cout << "Queue is empty, cannot dequeue." << std::endl;
                return -1;
            }
            int value = queue[front];
            front = (front + 1) % size;
            return value;
        }

        void display() {
            if (front == (rear + 1) % size) {
                std::cout << "Queue is empty." << std::endl;
                return;
            }
            std::cout << "Elements in the Circular Queue are: ";
            int i = front;
            while (i != rear) {
                std::cout << queue[i] << " ";
                i = (i + 1) % size;
            }
            std::cout << queue[i] << std::endl; // Display the last element
        }

        int countQueue(int value) {
            int count = 0;
            if (front == (rear + 1) % size) {
                return count; // Queue is empty
            }
            int i = front;
            while (i != rear) {
                if (queue[i] == value) {
                    count++;
                }
                i = (i + 1) % size;
            }
            if (queue[i] == value) { // Check the last element
                count++;
            }
            return count;
        }
};

#endif
