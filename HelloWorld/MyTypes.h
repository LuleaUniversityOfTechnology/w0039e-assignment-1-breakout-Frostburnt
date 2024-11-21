#pragma once
class ArrayOfUints {								//Basically an array for unsigned intergers
public:
	ArrayOfUints();
	~ArrayOfUints();
	void sort_back(unsigned int value);
	unsigned int& operator[](unsigned int index) {
		if (index < size)
			return data[index];
		else {						//when an index contains data that should not be read will always return 0
			unsigned int x = 0;
			return x;
		}
	}
	int length();
	unsigned int* get_data();
private:

	int size = 0;
	int capacity = 5;
	unsigned int* data;

	void inline sort() {								//this function is used to sort the last item in an array
		unsigned int buffer;							//it is essentially the nested portion of the bubble sort algorythm
		for (int i = size - 1; i > 0; i--)				//it's only one item I need to find a place for, the rest of the data is already sorted,
			if (data[i] > data[i - 1]) {				// so it'll be O(n) instead of O(n^2) number of loops.
				buffer = data[i];
				data[i] = data[i - 1];
				data[i - 1] = buffer;
			}
			else										//if index is not bigger that the one above it, we are done
				break;

	}
};