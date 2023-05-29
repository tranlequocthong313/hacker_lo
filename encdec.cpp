#include <ios>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "encdec.h"

using namespace std;

string EncDec::getExt(string fname) {
	auto i=fname.find('.');
	if(i==string::npos) {
		return "";
	}
	return fname.substr(i);
}

pair<bool, vector<char>> EncDec::read(string fname) {
	ifstream istr(fname, ios::binary);
	if(!istr.is_open()) {
		cout<<"Error occured"<<endl;
		return {false, {}};
	}
	istr.seekg(0, ios::end);
	streampos fSize=istr.tellg();
	istr.seekg(0, ios::beg);
	vector<char> buffer(fSize);
	istr.read(buffer.data(), fSize);
	if(!istr) {
		cout<<"Error occured"<<endl;
		return {false, {}};
	}
	istr.close();
	return {true, buffer};
}

bool EncDec::encode(string fname, int key) {
	auto res=read(fname);
	if(!res.first) return false;
	ofstream ostr(fname);
	if(!ostr.is_open()) {
		cout<<"Error occured"<<endl;
		return false;
	}
	ostr.clear();
	for(auto c:res.second) {
		int tmp=c+key;
		ostr<<(char)tmp;
	}
	ostr.close();
	return true;
}

bool EncDec::decode(string fname, int key) {
	auto res=read(fname);
	if(!res.first) return false;
	ofstream ostr(fname);
	if(!ostr.is_open()) {
		cout<<"Error occured"<<endl;
		return false;
	}
	ostr.clear();
	for(auto c:res.second) {
		int tmp=c-key;
		ostr<<(char)tmp;
	}
	ostr.close();
	return true;
}
