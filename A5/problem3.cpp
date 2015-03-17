// report.cpp

#include <iostream>
#include <vector>
using namespace std;

bool sum_to_target(vector<int> int_vec, int target, size_t i);


int main(){

	vector<int> b(0);
	b.push_back(10);
	b.push_back(3);
	b.push_back(2);
	b.push_back(1);

	sum_to_target(b, 12, 0);

}

bool sum_to_target(vector<int> int_vec, int target, size_t i = 0){

	// Create every possible combination of elements in vector, see if target - subset = 0

	if(target == 0){	// If any subset reaches 0, true
		
		return true;

	}else if(i == int_vec.size() && target != 0){	// No subset reached 0, false

		return false;
	}

	return sum_to_target(int_vec, target, i + 1) || sum_to_target(int_vec, target - int_vec[i], i + 1);
}