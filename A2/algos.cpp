// ============================================================================
// algos.cpp
// ~~~~~~~~~~~~~~~~
// author: Samina Khan
// - this is the ONLY file you can modify
// - feel free to include more headers if you need to
// ============================================================================

#include <stdexcept> // to throw exceptions if you need to
#include <iostream>
#include <cstring>
#include <sstream>

#include <fstream>   // to open & read from input file
#include <cstdlib>   // for atoi() if you want to use it

#include <set>       // for sba algorithm
#include <vector>    // for vba algorithm
#include <algorithm> // for vba algorithm

#include "Lexer.h"
#include "algos.h"
using namespace std; // BAD PRACTICE

int vba(string filename)
{
	ifstream ifs;
	string line;
	pair<int, int> p1;
	vector<pair<int, int> > pairVector;
	int a, b;
	vector<string> fields;

	//read file
	ifs.open(filename.c_str());
	if(ifs.fail()){
		cout << "Error: Failed to open file " << filename << endl;
		ifs.clear();
		return -1;
	} else {
		while(getline(ifs, line)){ //while there are still lines to read

			if(line[0] != '#'){
				
				istringstream iss(line);
				iss >> a;
				iss >> b;
				iss.clear();

				//make sure the pair that's added to vector has a<b for easier sorting/duplicate searching
				if(a <= b){
					p1 = make_pair(a, b);
				}
				else{
					p1 = make_pair(b, a);
				}
				
				pairVector.push_back(p1);
			}
		}

		sort(pairVector.begin(), pairVector.end());

		//remove duplicates
		vector<pair<int, int> >::iterator i = pairVector.begin();
		while(i != pairVector.end()){
			vector<pair<int, int> >::iterator j = i+1;
			if(j != pairVector.end() && *j == *i){
				i = pairVector.erase(i);
			} else{
				++i;
			}
		}

		ifs.close();

		vector<pair<int, int> >:: iterator z;
			
	}

	return pairVector.size();
}


int sba(string filename)
{
	ifstream ifs;
	string line;
	pair<int, int> p1;
	set<pair<int, int> > edgeSet;
	int a, b;
	vector<string> fields;

	//read file
	ifs.open(filename.c_str());
	if(ifs.fail()){
		cout << "Error: Failed to open file " << filename << endl;
		ifs.clear();
		return -1;
	} else{

		while(getline(ifs, line)){ //while there are still lines to read

			if(line[0] != '#'){
				
				istringstream iss(line);
				iss >> a;
				iss >> b;
				iss.clear();

				//make sure the pair that's added to vector has a<b for easier sorting/duplicate searching
				if(a <= b){
					p1 = make_pair(a, b);
				}
				else{
					p1 = make_pair(b, a);
				}
			edgeSet.insert(p1);	
			}
		}	
		return edgeSet.size();
	}
}
