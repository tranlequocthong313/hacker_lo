#include <ios>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "encdec.h"
#include <thread>

using namespace std;

string EncDec::getExt(string path) {
	auto i=path.find('.');
	if(i==string::npos) {
		return "";
	}
	return path.substr(i);
}

pair<bool, vector<char>> EncDec::read(string path) {
	ifstream istr(path, ios::binary);
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

bool EncDec::encode(string path, int key) {
	auto res=read(path);
	if(!res.first) return false;
	ofstream ostr(path);
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

bool EncDec::decode(string path, int key) {
	auto res=read(path);
	if(!res.first) return false;
	ofstream ostr(path);
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

const int NUMS_THREAD=10;

void EncDec::encode(vector<string>& paths, int id) {
	vector<thread> threads;
	for(auto i=0; i<NUMS_THREAD; i++) {
		threads.push_back(thread([&paths, i, this, id]() {
					for(auto j=i; j<paths.size(); j+=NUMS_THREAD) {
					encode(paths[j], id);
					}
					}));
	}
	for(auto& thread:threads) {
		thread.join();
	}
	cout<<"Encoded successfully"<<endl;
}

void EncDec::decode(vector<string>& paths, int id) {
	vector<thread> threads;
	for(auto i=0; i<NUMS_THREAD; i++) {
		threads.push_back(thread([&paths, i, this, id]() {
					for(auto j=i; j<paths.size(); j+=NUMS_THREAD) {
					decode(paths[j], id);
					}
					}));
	}
	for(auto& thread:threads) {
		thread.join();
	}
	cout<<"Decoded successfully"<<endl;
}
