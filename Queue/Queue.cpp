#include "Queue.h"
#include <exception>
#include <iostream>
#include <random>

using namespace std;


/**
 * Constructor
 * Worst case: θ(n)
 * Average case: θ(n)
 * Best case: θ(n)
 * */
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


/**
 * Adds new element to the end of the queue
 * Worst case: θ(n) (when resizing is needed)
 * Average case => Amortized complexity: O(1)
 * Best case: θ(1)
 * */
void Queue::push(TElem elem) {
	//TODO - Implementation
	if (firstEmpty == -1) {
		resize_up();
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


/**
 * Returns the element from the front of the queue
 * Worst case: θ(1)
 * Average case: θ(1)
 * Best case: θ(1)
 * */
TElem Queue::top() const {
	//TODO - Implementation
	if (isEmpty()) {
		throw std::exception();
	}
	return nodes[head].info;
}


/**
 * Removes and returns the element from the front of the queue
 * Worst case: θ(n) (when resizing is needed)
 * Average case => Amortized complexity: O(1)
 * Best case: θ(1)
 * */
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

	if (size <= capacity / 4 && capacity >= 10) {
		resize_down();
	}

	return value;
}


/**
 * Checks if the queue is empty
 * Worst case: θ(1)
 * Average case: θ(1)
 * Best case: θ(1)
 * */
bool Queue::isEmpty() const {
	//TODO - Implementation
	return size == 0;
}


/**
 * Destructor
 * Worst case: θ(n)
 * Average case: θ(n)
 * Best case: θ(n)
 * */
Queue::~Queue() {
	//TODO - Implementation
	delete[] nodes;
}


/**
 * Allocates a new node in the queue
 * Worst case: θ(1)
 * Average case: θ(1)
 * Best case: θ(1)
 * */
int Queue::allocate() { // returneaza indicele la care trebuie alocata noua valoare
	if (firstEmpty == -1)
		return -1;
	int newElem = firstEmpty;
	firstEmpty = nodes[firstEmpty].next;
	if (firstEmpty != -1)
		nodes[firstEmpty].prev = -1;
	return newElem;
}


/**
 * Frees a node in the queue
 * Worst case: θ(1)
 * Average case: θ(1)
 * Best case: θ(1)
 * */
void Queue::free(int position) { // adauga un nod in "lista de noduri libere"
	// cand un nou element este "eliberat" practic valoarea sa ramane, dar se schimba indicii in asa fel incat sa nu mai fie luat in considerare
	// cand adaugam practic suprascriem valuoarea scrisa acolo
	nodes[position].next = firstEmpty;
	nodes[position].prev = -1;
	if (firstEmpty != -1)
		nodes[firstEmpty].prev = position;
	firstEmpty = position;
}


/**
 * Doubles the capacity of the queue and rebuilds the free node list
 * Worst case: θ(n)
 * Average case: θ(n)
 * Best case: θ(n)
 * */
void Queue::resize_up() {
	int newCapacity = capacity*2;
	DLLANode* newNodes = new DLLANode[newCapacity];
	// Copy the active elements to the new array
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


/**
 * Halves the capacity of the queue and rebuilds the free node list
 * Worst case: θ(n)
 * Average case: θ(n)
 * Best case: θ(n)
 * */
void Queue::resize_down() {
	int newCapacity = capacity / 2;
	DLLANode* newNodes = new DLLANode[newCapacity];

	int current = head;
	int index = 0;

	// Copy the active elements to the new array
	while (current != -1 && index < newCapacity) {
		newNodes[index] = nodes[current];
		if (index > 0) {
			newNodes[index].prev = index - 1;
		}
		if (index < newCapacity - 1) {
			newNodes[index].next = index + 1;
		}
		current = nodes[current].next;
		index++;
	}

	// Update head and tail
	head = 0;
	tail = index - 1;
	if (tail >= 0) {
		newNodes[tail].next = -1;
	}

	// Rebuild the free node list
	for (int i = index; i < newCapacity - 1; i++) {
		newNodes[i].next = i + 1;
		newNodes[i].prev = -1;
	}
	newNodes[newCapacity - 1].next = -1;
	newNodes[newCapacity - 1].prev = -1;
	firstEmpty = index;

	delete[] nodes;
	nodes = newNodes;
	capacity = newCapacity;
}