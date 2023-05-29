#include <iostream>
#include <filesystem>
#include "encdec.h"

using namespace std;

void getFileName(string& fname) {
	cout<<"File's name: ";
	cin>>fname;
}

int main() {
	int choice;
	EncDec encdec;
	while(true) {
		string fname;
		cout<<"--Menu--"<<endl;
		cout<<"1. Encrypt"<<endl;
		cout<<"2. Decrypt"<<endl;
		cout<<"0. Exit"<<endl;
		cout<<"Choose: ";
		cin>>choice;
		switch (choice) {
			case 1: {
						getFileName(fname);
						if(encdec.encode(fname)) {
							cout<<"Encrypted success!"<<endl;
						}
						break;
					}
			case 2: {
						getFileName(fname);
						if(encdec.decode(fname)) {
							cout<<"Decrypted success!"<<endl;
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
