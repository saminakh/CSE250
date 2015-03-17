// report.cpp

#include <iostream>
#include <stack>
using namespace std;

size_t recursive_num_negatives(stack<int> int_stack);
size_t iterative_num_negatives(stack<int> int_stack);

int main(){

	stack<int> int_stack;
	int_stack.push(2);
	int_stack.push(5);
	int_stack.push(-2);
	int_stack.push(-5);
	int_stack.push(1);
	int_stack.push(0);
	int_stack.push(3);
	int_stack.push(-7);
	int_stack.push(1000004);
	int_stack.push(-235235);

	size_t num = recursive_num_negatives(int_stack);
	cout << " Recursive: " << num << endl;
	size_t num2 = iterative_num_negatives(int_stack);
	cout << "Iterative: " << num2 << endl;
	return 0;
}


// the iterative solution
size_t iterative_num_negatives(stack<int> int_stack){

	size_t num = 0;

	while(!int_stack.empty()){
		if(int_stack.top() < 0){
			num++;
		}
		int_stack.pop();
	}

	return num;

}

// the recursive solution, the initial call is 
size_t recursive_num_negatives(stack<int> int_stack){

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
