//Samina Khan - Assignment 5

// PROBLEM 1 =====================================================

size_t iterative_num_negatives(stack<int> int_stack){ // ITERATIVE

	size_t num = 0;

	while(!int_stack.empty()){
		if(int_stack.top() < 0){
			num++;
		}
		int_stack.pop();
	}
	return num;
}

size_t recursive_num_negatives(stack<int> int_stack){ // RECURSIVE

	size_t num = 0;

	if(!int_stack.empty()){
		if(int_stack.top() < 0){
			num = 1;
		}

		int_stack.pop();
		return recursive_num_negatives(int_stack) + num;
	}else{
		return 0;
	}
}

// PROBLEM 2 =====================================================

bool iterative_sub_vector(vector<int>& a, vector<int> b){ // ITERATIVE
	int i;
	if(a.size() > b.size()){	// Subset bigger than set, always false
		return false;
	}
	if(a.size() == 0){	// Empty set, always true
		return true;
	}
	for(i = 0; i < b.size(); i++){
		int j;
		int temp = i;
		while(j < a.size()){
			if(b[temp] == a[j]){
				j++;
				temp++;
			}else{
				break;
			}
			if(j == a.size()){
				return true;
			}
		}
	}
	return false;
}

bool recursive_sub_vector(vector<int>& a, vector<int> b, size_t k){
	if(a.size() > b.size()){	//Subset bigger than set, always false
		return false;
	}
	if(a.size() == 0){	// Empty set, always true
		return true;
	}
	if(k > b.size()-a.size()){
		cout << "FALSE" << endl;
		return false;
	}
	
	size_t i = 0;

	while(i < a.size()){
		if(a[i] != b[k+i]){
			return recursive_sub_vector(a, b, k+1);
		}
		else{
			i++;
		}
	}
	return true;
}

// PROBLEM 3 =====================================================

bool sum_to_target(vector<int> int_vec, int target, size_t i = 0){ // RECURSIVE SOLUTION

	// Create every possible combination of elements in vector, see if target - subset = 0

	if(target == 0){	// If any subset reaches 0, true
		
		return true;

	}else if(i == int_vec.size() && target != 0){	// No subset reached 0, false

		return false;
	}

	return sum_to_target(int_vec, target, i + 1) || sum_to_target(int_vec, target - int_vec[i], i + 1);
}