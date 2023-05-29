#include <iostream>
#include <iterator>
#include <libudev.h>
#include <ostream>
#include <string>
#include <sys/select.h>
#include <utility>
#include "usb_detector.h"

void USB_Detector::printDeviceInfo() {
	if(!dev) return;
	const char* devNode=udev_device_get_devnode(dev);
	const char* sysPath=udev_device_get_syspath(dev);
	const char* subsystem=udev_device_get_subsystem(dev);
	const char* devType=udev_device_get_devtype(dev);
	std::cout<<"Device node: "<<*(devNode?devNode:"Unknown")<<std::endl;
	std::cout<<"Sys path: "<<*(sysPath?sysPath:"Unknown")<<std::endl;
	std::cout<<"Subsystem: "<<*(subsystem?subsystem:"Unknown")<<std::endl;
	std::cout<<"Device type: "<<*(devType?devType:"Unknown")<<std::endl;
	struct udev_list_entry *properties=udev_device_get_properties_list_entry(dev);
	struct udev_list_entry *entry;
	udev_list_entry_foreach(entry, properties) {
		const char *name=udev_list_entry_get_name(entry);
		const char *value=udev_list_entry_get_value(entry);
		std::cout<<name<<": "<<(value?value:"Unknown")<<std::endl;
	}
	std::cout<<std::endl;
}

void USB_Detector::teardown() {
	udev_monitor_unref(monitor);
	udev_unref(udev);
}

USB_Detector::USB_Detector() {
	udev=udev_new();
	if(!udev) {
		std::cerr<<"Failed to initialize libudev"<<std::endl;
		return;
	}
	monitor=udev_monitor_new_from_netlink(udev, "udev");
	if(!monitor) {
		std::cerr<<"Failed to create udev monitor"<<std::endl;
		udev_unref(udev);
		return;
	}
	udev_monitor_filter_add_match_subsystem_devtype(monitor, "usb", NULL);
	udev_monitor_enable_receiving(monitor);
	fd=udev_monitor_get_fd(monitor);
	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	std::cout<<"USB device monitoring started..."<<std::endl;
}

std::pair<int, udev_device*>USB_Detector::detect() {
	std::pair<int, udev_device*> ans={-1, nullptr};
	int ret=select(fd+1, &fds, NULL, NULL, NULL);
	if(ret>0&&FD_ISSET(fd, &fds)) {
		dev=udev_monitor_receive_device(monitor);
		if(!dev) return {-1, dev};
		const char *action=udev_device_get_action(dev);
		const char *devNode=udev_device_get_devnode(dev);
		if(devNode&&action) {
			if(std::string(action)=="add") {
				ans={1, dev};
			} else if(std::string(action)=="remove") {
				ans={0, dev};
			}
		}
	}
	return ans;
}

int main() {
	std::cout<<"STARTED"<<std::endl;
	USB_Detector usb_detector;
	while(true) {
		auto signal=usb_detector.detect();
		if(signal.first==1) {
			std::cout<<"--USB device connected--"<<std::endl;
			usb_detector.printDeviceInfo();
		} else if(signal.first==0) {
			std::cout<<"--USB device disconnected--"<<std::endl;
		}
		udev_device_unref(signal.second);
	}
	usb_detector.teardown();
	return 0;
}

