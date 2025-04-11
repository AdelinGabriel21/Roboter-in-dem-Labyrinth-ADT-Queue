#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>

using namespace std;

int main_queue() {

	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	return 0;
}