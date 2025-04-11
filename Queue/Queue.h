#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111


// 35. Roboter in dem Labyrinth:
// In einem rechteckigen Labyrinth gibt es besetzte (X) und leere Zellen (*). Der Roboter
// kann sich in vier Richtungen bewegen: Nord, Süd, Ost, West.

/*
	X	*	*	X	X	X	*	*
	X	*	X	*	*	*	*	*
	X	*	*	*	*	*	X	*
	X	X	X	*	*	*	X	*
	*	X	*	*	R	X	X	*
	*	*	*	X	X	X	X	*
	*	*	*	*	*	*	*	X
	X	X	X	X	X	X	X	X
*/

// d) Bestimme ob es einen Pfad gibt, sodass der Roboter aus dem Labyrinth rauskommt
// (d.h. zu der ersten oder letzten Spalte oder zu der ersten oder letzten Zeile
// gelangen).
// e) Bestimme einen Pfad, falls es einen gibt.
// f) Bestimme einen Pfad mit minimaler Länge, falls es einen gibt.
// Ihr müsst in der Implementierung ADT Queue repräsentiert als DLLA benutzen.


class Queue
{
private:
	//TODO - Representation
	struct DLLANode {
		TElem info;
		int next;
		int prev;
	};

	int capacity;
	int size;
	int head;
	int tail;
	int firstEmpty;
	DLLANode* nodes;

	int allocate();
	void free(int position);
	void resize();

public:
	Queue();

	//pushes an element to the end of the queue
	void push(TElem e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem pop();

	//checks if the queue is empty
	bool isEmpty() const;

	// destructor
	~Queue();
};
