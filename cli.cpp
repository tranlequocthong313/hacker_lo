#include <iostream>
#include <filesystem>
#include <vector>
#include "encdec.h"
#include "helper.cpp"

using namespace std;

const int ID=301; // change this to your device's model id
void getFileName(string& fname) {
	cout<<"File's name: ";
	cin>>fname;
}
int main() {
	int choice;
	EncDec encdec;
	vector<string> paths;
	Helper helper;
	while(true) {
		string fname;
		cout<<"--Menu--"<<endl;
		cout<<"1. Encode"<<endl;
		cout<<"2. Decode"<<endl;
		cout<<"0. Exit"<<endl;
		cout<<"Choose: ";
		cin>>choice;
		switch (choice) {
			case 1: {
						getFileName(fname);
						paths=helper.getAbsPaths(fname);
						if(paths.empty()) {
							if(encdec.encode(fname, ID)) {
								cout<<"Encoded success!"<<endl;
							}
						} else {
							for(auto& path:paths) {
								if(encdec.encode(path, ID)) {
									cout<<"Encoded success!"<<endl;
								}
							}
						}
						break;
					}
			case 2: {
						getFileName(fname);
						paths=helper.getAbsPaths(fname);
						if(paths.empty()) {
							if(encdec.decode(fname, ID)) {
								cout<<"Decoded success!"<<endl;
							}
						} else {
							for(auto& path:paths) {
								if(encdec.decode(path, ID)) {
									cout<<"Decoded success!"<<endl;
								}
							}
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
