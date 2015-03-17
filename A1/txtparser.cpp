#include <iostream>
#include <fstream>
using namespace std;

int main(){
	string input, line, fname, temp;
	ifstream ifs; //input file stream
	int i, j, max;
	int start, end;

	cout << "Enter one of the three commands: \n" 
		<< "numcols filename \n"
		<< "numrows filename \n"
		<< "exit \n" 
		<< " > ";
	while (getline(cin, input)){
		start = 0;
		end = 0;
		bool goodInput = true;

		while(goodInput){
			if(end == input.length() || input[end] == ' '){
				string currentWord = input.substr(start, end - start);

				//4 cases, exit, numcols, numrows, and a bad input!

				//case 1, exit
				if(currentWord.compare("exit") == 0){
					return 0;
				}

				//case 2, rows
				else if(currentWord.compare("numrows") == 0){
					if(currentWord.length() == input.length()){
						cout << "Please check that your input is in the corret format!" << endl;
						break;
					}
					else{
						end++;
						start = end;
						while(true){
							if(end == input.length()){
								string fname = input.substr(start, end - start);
								ifs.open(fname.c_str());

								if(ifs.fail()){
									cout << "Please check that your file name is correct!" << endl;
									ifs.clear();
									goodInput = false;
									break;
								}
								else{
									i = 0;
									while(getline(ifs, line)){
										i++;
									}
									cout << i << endl;
									ifs.close();
									goodInput = false;
									break;
								}
							}
							if(input[end] == ' '){
								cout << "Please check that your input is in the correct format!" << endl;
								goodInput = false;
								break;
							}
							end++;
						}

					}
				}

				//case 3, cols
				else if(currentWord.compare("numcols") == 0){
					if(currentWord.length() == input.length()){
						cout << "Please check that your input is in the corret format!" << endl;
						break;
					}
					else{
						end++;
						start = end;
						while(true){
							if(end == input.length()){
								string fname = input.substr(start, end - start);
								ifs.open(fname.c_str());

								if(ifs.fail()){
									cout << "Please check that your file name is correct!" << endl;
									ifs.clear();
									goodInput = false;
									break;
								}
								else{
									i = 0;
									max = 0;
									
									while(getline(ifs, line)){
										j = 0;
										end = 0; 
										start = 0;
										while(end <= line.length()){
											if(end == line.length() || line[end] == ' '){
									
												//account for multiple spaces and if line ends with a space
												while(line[end] == ' '){
													end++;
													if(end++ == line.length()){
														j--;
													}
												}
												j++;

											}
											end++;
											start = end;
											
										}
										if(j > max){
											max = j;
										}
									}
									cout << max << endl;
									ifs.close();
									goodInput = false;
									break;
								}
							}
							if(input[end] == ' '){
								cout << "Please check that your input is in the correct format!" << endl;
								goodInput = false;
								break;
							}
							end++;
						}

					}
				}

				//case 4, bad input
				else{
					cout << "Please check that your input is in the correct format!" << endl;
					break;
				}
			}
			end++;
		}
		cout << " > "; 
	} 
	return 0;
}