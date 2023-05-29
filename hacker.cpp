#include "usb_detector.h"
#include "encdec.h"
#include <iostream>
#include <vector>
#include "helper.cpp"

const int ID=301; // change this to your device's model id
const string dirPath="/mnt/nvme0n1p5/Workspace/du_an_hacker_lo/tests"; // change this to your dir's path

void handleConnceted(USB_Detector& usb_detector, EncDec& encdec, Helper& helper) {
	usb_detector.printDeviceInfo();
	int modelID=usb_detector.getModelID();
	vector<string> paths;
	if(modelID!=ID) return;
	paths=helper.getAbsPaths(dirPath);
	if(paths.empty()) {
		// TODO: file only
		return;
	}
	for(auto& path:paths) {
		bool res=encdec.decode(path, modelID);
		if(!res) continue;
		std::cout<<"Decoded successfully"<<std::endl;
	}
}

void handleDisconnected(EncDec& encdec, Helper& helper) {
	vector<string> paths;
	paths=helper.getAbsPaths(dirPath);
	if(paths.empty()) {
		// TODO: file only
		return;
	}
	for(auto& path:paths) {
		bool res=encdec.encode(path, ID);
		if(!res) continue;
		std::cout<<"Encoded successfully"<<std::endl;
	}
}

int main() {
	std::cout<<"STARTED"<<std::endl;
	USB_Detector usb_detector;
	EncDec encdec;
	Helper helper;
	while(true) {
		auto signal=usb_detector.detect();
		if(signal.first==1) {
			std::cout<<"--USB device connected--"<<std::endl;
			handleConnceted(usb_detector, encdec, helper);
		} else if(signal.first==0) {
			std::cout<<"--USB device disconnected--"<<std::endl;
			handleDisconnected(encdec, helper);
		}
		udev_device_unref(signal.second);
	}
	usb_detector.teardown();
	return 0;
}

