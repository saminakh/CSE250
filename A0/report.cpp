// report.cpp

#include <iostream>
using namespace std;

int main(){
	string my_name = "Samina Khan";
	string my_text_editor = "VI";
	string my_home_os = "Windows";
	bool i_worked = true;

	cout << "My name is " << my_name << endl;

	if (i_worked) {
		cout << "I was able to install and test g++ and "
		<< "the text editor " << my_text_editor << '\n'
		<< "in my home computer/laptop, which runs "
		<< my_home_os << endl;
	} else {
		cout << "I wasn't able to install and test g++ and/or a text "
		<< "editor because my dog ate my computer"
		<< endl;
	}
	
	return 0;
}
