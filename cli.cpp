#include <iostream>
#include <filesystem>
#include <vector>
#include "encdec.h"
#include "helper.cpp"

using namespace std;

const int ID=301; // change this to your device's model id
void getPathInput(string& pathName) {
	cout<<"Path: ";
	cin>>pathName;
}
int main() {
	int choice;
	EncDec encdec;
	vector<string> paths;
	Helper helper;
	while(true) {
		string pathName;
		cout<<"--Menu--"<<endl;
		cout<<"1. Encode"<<endl;
		cout<<"2. Decode"<<endl;
		cout<<"0. Exit"<<endl;
		cout<<"Choose: ";
		cin>>choice;
		switch (choice) {
			case 1: {
						getPathInput(pathName);
						paths=helper.getAbsPaths(pathName);
						if(paths.empty()) {
							if(!encdec.encode(pathName, ID)) break;
							cout<<"Encoded success!"<<endl;
						} else {
							encdec.encode(paths, ID);
						}
						break;
					}
			case 2: {
						getPathInput(pathName);
						paths=helper.getAbsPaths(pathName);
						if(paths.empty()) {
							if(encdec.decode(pathName, ID)) break;
							cout<<"Decoded success!"<<endl;
						} else {
							encdec.decode(paths, ID);
						}
						break;
					}
			case 0: {
						cout<<"Exited!"<<endl;
						exit(0);
						break;
					}

			default:
					break;

		}
	}
	return 0;
}
