#include "MyTypes.h"

ArrayOfUints::ArrayOfUints() {
		data = new unsigned int[capacity];
	}
ArrayOfUints::~ArrayOfUints() {
		delete[] data;
	}
void ArrayOfUints::sort_back(unsigned int value) {	//sorted push_back essentially
		size++;
		if (size >= capacity) {
			capacity = capacity * 2;
			unsigned int* newData = new unsigned int[capacity];
			for (int i = 0; i < size - 1; i++) {
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		data[size - 1] = value;								// this will put data in the last index
		sort();
	}

	int ArrayOfUints::length() {
		return size;
	}
	unsigned int* ArrayOfUints::get_data() {
		return data;
	}