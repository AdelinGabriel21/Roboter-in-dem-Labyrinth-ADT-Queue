#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
	//TODO - Implementation
	capacity = 10;
	size = 0;
	head = tail = -1;
	firstEmpty = -1;
	nodes = new DLLANode[capacity]();

}


void Queue::push(TElem elem) {
	//TODO - Implementation
}


TElem Queue::top() const {
	//TODO - Implementation
	return NULL_TELEM;
}

TElem Queue::pop() {
	//TODO - Implementation
	return NULL_TELEM;
}

bool Queue::isEmpty() const {
	//TODO - Implementation
	return false;
}


Queue::~Queue() {
	//TODO - Implementation
}

int Queue::allocate() {
}

void Queue::free(int position) {
}

void Queue::resize() {
}

