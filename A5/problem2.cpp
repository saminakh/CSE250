// report.cpp

#include <iostream>
#include <vector>
using namespace std;

bool iterative_sub_vector(vector<int>& a, vector<int> b);
bool recursive_sub_vector(vector<int>& a, vector<int> b, size_t k);

int main(){

	vector<int> b(0);
	vector<int> a(0);

	b.push_back(10);
	b.push_back(3);
	b.push_back(2);
	b.push_back(1);

	a.push_back(3);
	a.push_back(2);
	
	//iterative_sub_vector(a, b);
	cout << "=============" << endl;
	recursive_sub_vector(a, b, 0);

}

// the iterative solution - IS "A" A SUBVECTOR OF "B"??
bool iterative_sub_vector(vector<int>& a, vector<int> b)
{
	int i;
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
				cout << "TRUE" << endl;
				return true;
			}
		}
	}
	cout << "FALSE" << endl;
	return false;

}

/** 
 * the recurive solution, you CAN NOT call erase NOR copy many elements of 
 * b into a separate vector. The function prototyp is already a hint
 * the initial call is recursive_sub_vector(a, b, 0)
 */
bool recursive_sub_vector(vector<int>& a, vector<int> b, size_t k){
	if(a.size() > b.size()){
		return false;
	}
	if(a.size() == 0){
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