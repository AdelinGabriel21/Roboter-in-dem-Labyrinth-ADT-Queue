#include "Queue.h"
#include <exception>
#include <iostream>
#include <random>

using namespace std;


Queue::Queue() {
	//TODO - Implementation
	capacity = 10;
	size = 0;
	head = tail = -1;
	firstEmpty = 0;
	nodes = new DLLANode[capacity]();
	for (int i = 0; i < capacity - 1; i++) {
		nodes[i].next = i + 1;
		nodes[i].prev = -1;
	}
	nodes[capacity - 1].next = -1;
	nodes[capacity - 1].prev = -1;
}


void Queue::push(TElem elem) {
	//TODO - Implementation
	if (firstEmpty == -1) {
		resize();
	}
	int newPos = allocate();
	nodes[newPos].info = elem;
	nodes[newPos].next = -1;
	nodes[newPos].prev = tail;

	if (tail != -1) {
		nodes[tail].next = newPos;
	} else {
		head = newPos;  // if queue was empty
	}
	tail = newPos;
	size++;
}


TElem Queue::top() const {
	//TODO - Implementation
	if (isEmpty()) {
		throw std::exception();
	}
	return nodes[head].info;
}

TElem Queue::pop() {
	//TODO - Implementation
	if (isEmpty()) {
		throw std::exception();
	}

	int oldHead = head;
	TElem value = nodes[oldHead].info;

	head = nodes[oldHead].next;
	if (head != -1) {
		nodes[head].prev = -1;
	} else {
		tail = -1;  // queue is now empty
	}

	free(oldHead);
	size--;

	return value;
}

bool Queue::isEmpty() const {
	//TODO - Implementation
	return size == 0;
}

Queue::~Queue() {
	//TODO - Implementation
	delete[] nodes;
}

int Queue::allocate() { // returneaza indicele la care trebuie alocata noua valoare
	if (firstEmpty == -1)
		return -1;
	int newElem = firstEmpty;
	firstEmpty = nodes[firstEmpty].next;
	if (firstEmpty != -1)
		nodes[firstEmpty].prev = -1;
	return newElem;
}

void Queue::free(int position) { // adauga un nod in "lista de noduri libere"
	nodes[position].next = firstEmpty;
	nodes[position].prev = -1;
	if (firstEmpty != -1)
		nodes[firstEmpty].prev = position;
	firstEmpty = position;
}

void Queue::resize() { // dubleaza capacitatea si reface lista de noduri libere
	int newCapacity = capacity*2;
	DLLANode* newNodes = new DLLANode[newCapacity];
	for (int i = 0; i < capacity; i++)
		newNodes[i] = nodes[i];
	for (int i = capacity; i < newCapacity-1; i++) {
		newNodes[i].next = i + 1;
		newNodes[i].prev = -1;
	}
	newNodes[newCapacity-1].next = -1;
	newNodes[newCapacity-1].prev = -1;
	firstEmpty = capacity;

	delete[] nodes;
	nodes = newNodes;
	capacity = newCapacity;
}