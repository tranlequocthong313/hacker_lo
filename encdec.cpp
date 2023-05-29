#include <iostream>
#include <fstream>
#include "encdec.h"

using namespace std;

string EncDec::getExt(string fname) {
	auto i=fname.find('.');
	if(i==string::npos) {
		return "";
	}
	return fname.substr(i);
}

bool EncDec::encode(string fname) {
	ifstream istr(fname);
	if(!istr.is_open()) {
		cout<<"Error occured"<<endl;
		return false;
	}
	string outFile="encrypt"+getExt(fname);
	ofstream ostr(outFile);
	if(!ostr.is_open()) {
		cout<<"Error occured"<<endl;
		return false;
	}
	char ch;
	while(istr>>noskipws>>ch) {
		int tmp=ch+100;
		ostr<<(char)tmp;
	}
	ostr.close();
	istr.close();
	return true;
}

bool EncDec::decode(string fname) {
	ifstream istr(fname);
	if(!istr.is_open()) {
		cout<<"Error occured"<<endl;
		return false;
	}
	string outFile="decrypt"+getExt(fname);
	ofstream ostr(outFile);
	if(!ostr.is_open()) {
		cout<<"Error occured"<<endl;
		return false;
	}
	char ch;
	while(istr>>noskipws>>ch) {
		int tmp=ch-100;
		ostr<<(char)tmp;
	}
	ostr.close();
	istr.close();
	return true;
}
